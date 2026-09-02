#include "core/BackgroundQueue.h"

namespace Blade
{
namespace Core
{

BackgroundQueue::BackgroundQueue()
    : m_head( 0 ),
      m_tail( 0 ),
      m_count( 0 ),
      m_thread( NULL ),
      m_wakeEvent( NULL ),
      m_stopEvent( NULL ),
      m_running( 0 )
{
    ZeroMemory( m_items, sizeof( m_items ) );
    InitializeCriticalSection( &m_lock );
}

BackgroundQueue::~BackgroundQueue()
{
    Stop();
    DeleteCriticalSection( &m_lock );
}

HRESULT BackgroundQueue::Start()
{
    if( InterlockedCompareExchange( &m_running, 0, 0 ) != 0 )
        return S_FALSE;

    m_stopEvent = CreateEvent( NULL, TRUE, FALSE, NULL );
    m_wakeEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
    if( m_stopEvent == NULL || m_wakeEvent == NULL )
    {
        Stop();
        return E_FAIL;
    }

    InterlockedExchange( &m_running, 1 );
    m_thread = CreateThread( NULL, 64 * 1024, ThreadEntry, this, 0, NULL );
    if( m_thread == NULL )
    {
        InterlockedExchange( &m_running, 0 );
        Stop();
        return E_FAIL;
    }

    return S_OK;
}

void BackgroundQueue::Stop()
{
    InterlockedExchange( &m_running, 0 );

    if( m_stopEvent != NULL )
        SetEvent( m_stopEvent );
    if( m_thread != NULL )
    {
        WaitForSingleObject( m_thread, INFINITE );
        CloseHandle( m_thread );
        m_thread = NULL;
    }
    if( m_wakeEvent != NULL )
    {
        CloseHandle( m_wakeEvent );
        m_wakeEvent = NULL;
    }
    if( m_stopEvent != NULL )
    {
        CloseHandle( m_stopEvent );
        m_stopEvent = NULL;
    }

    EnterCriticalSection( &m_lock );
    ZeroMemory( m_items, sizeof( m_items ) );
    m_head = 0;
    m_tail = 0;
    m_count = 0;
    LeaveCriticalSection( &m_lock );
}

HRESULT BackgroundQueue::Enqueue( BackgroundCallback callback, void* context )
{
    if( callback == NULL )
        return E_POINTER;
    if( InterlockedCompareExchange( &m_running, 0, 0 ) == 0 )
        return E_FAIL;

    EnterCriticalSection( &m_lock );
    if( m_count >= MaximumItems )
    {
        LeaveCriticalSection( &m_lock );
        return E_OUTOFMEMORY;
    }

    m_items[ m_tail ].callback = callback;
    m_items[ m_tail ].context = context;
    m_tail = ( m_tail + 1 ) % MaximumItems;
    ++m_count;
    LeaveCriticalSection( &m_lock );

    SetEvent( m_wakeEvent );
    return S_OK;
}

DWORD WINAPI BackgroundQueue::ThreadEntry( void* context )
{
    BackgroundQueue* queue = static_cast< BackgroundQueue* >( context );
    return queue != NULL ? queue->WorkerMain() : ERROR_INVALID_PARAMETER;
}

DWORD BackgroundQueue::WorkerMain()
{
    HANDLE waitHandles[ 2 ] = { m_stopEvent, m_wakeEvent };
    for( ;; )
    {
        const DWORD waitResult = WaitForMultipleObjects( 2, waitHandles, FALSE, INFINITE );
        if( waitResult == WAIT_OBJECT_0 )
            break;
        if( waitResult != WAIT_OBJECT_0 + 1 )
            return waitResult;

        WorkItem item;
        while( TryDequeue( &item ) )
        {
            if( WaitForSingleObject( m_stopEvent, 0 ) == WAIT_OBJECT_0 )
                return ERROR_SUCCESS;
            item.callback( item.context );
        }
    }

    return ERROR_SUCCESS;
}

BOOL BackgroundQueue::TryDequeue( WorkItem* item )
{
    if( item == NULL )
        return FALSE;

    EnterCriticalSection( &m_lock );
    if( m_count == 0 )
    {
        LeaveCriticalSection( &m_lock );
        return FALSE;
    }

    *item = m_items[ m_head ];
    ZeroMemory( &m_items[ m_head ], sizeof( WorkItem ) );
    m_head = ( m_head + 1 ) % MaximumItems;
    --m_count;
    LeaveCriticalSection( &m_lock );
    return TRUE;
}

} // namespace Core
} // namespace Blade

#pragma once

#include <xtl.h>

#include "services/IRuntimeService.h"

namespace Blade
{
namespace Core
{

typedef void ( *BackgroundCallback )( void* context );

class BackgroundQueue : public Services::IRuntimeService
{
public:
    BackgroundQueue();
    virtual ~BackgroundQueue();

    virtual HRESULT Start();
    virtual void Stop();

    HRESULT Enqueue( BackgroundCallback callback, void* context );

private:
    struct WorkItem
    {
        BackgroundCallback callback;
        void* context;
    };

    static const DWORD MaximumItems = 16;

    static DWORD WINAPI ThreadEntry( void* context );
    DWORD WorkerMain();
    BOOL TryDequeue( WorkItem* item );

    CRITICAL_SECTION m_lock;
    WorkItem m_items[ MaximumItems ];
    DWORD m_head;
    DWORD m_tail;
    DWORD m_count;
    HANDLE m_thread;
    HANDLE m_wakeEvent;
    HANDLE m_stopEvent;
    volatile LONG m_running;
};

} // namespace Core
} // namespace Blade

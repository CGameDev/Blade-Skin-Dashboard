#include <xtl.h>

#include "app/BladeDashboardApp.h"
#include "diagnostics/DebugLog.h"

VOID __cdecl main()
{
    const HRESULT logResult = Blade::Diagnostics::Initialize();
    if( FAILED( logResult ) )
        Blade::Diagnostics::WriteFailure( "Persistent log initialization", logResult );

    Blade::Diagnostics::Write(
        "Starting Milestone 000 Phase G Revision 5 English text and list-binding checkpoint." );

    Blade::App::BladeDashboardApp app;
    const HRESULT initializeResult = app.Initialize();
    if( FAILED( initializeResult ) )
    {
        Blade::Diagnostics::WriteFailure( "Application initialization", initializeResult );
        app.Shutdown();
        Blade::Diagnostics::Shutdown();
        return;
    }

    const int runResult = app.RunUntilExit();

    char pendingImage[ MAX_PATH ];
    ZeroMemory( pendingImage, sizeof( pendingImage ) );
    const BOOL hasPendingLaunch =
        app.Launcher().CopyPendingPath( pendingImage, ARRAYSIZE( pendingImage ) ) == S_OK;

    app.Shutdown();

    if( runResult != 0 )
        Blade::Diagnostics::Write( "XUI run loop returned a nonzero result." );
    Blade::Diagnostics::Write(
        "Milestone 000 Phase G Revision 5 English text and list-binding checkpoint stopped." );

    if( hasPendingLaunch )
    {
        Blade::Diagnostics::Write( "Dispatching queued launch after clean shutdown." );
        Blade::Diagnostics::Shutdown();
        XLaunchNewImage( pendingImage, XLAUNCH_FLAG_CLEAR_LAUNCH_DATA );
    }

    Blade::Diagnostics::Shutdown();
}

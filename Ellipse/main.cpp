// 2016
// Автор: Гусев Илья
// Описание: Точка входа в приложение.

#include <OverlappedWindow.h>
#include <ShellScalingAPI.h>
#include <DPI.h>

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	// Задаём настройки dpi.
	HRESULT hr = E_FAIL;
	hr = SetProcessDpiAwareness( PROCESS_PER_MONITOR_DPI_AWARE );
	if( hr != S_OK ) {
		MessageBox( NULL, (LPCWSTR) L"SetProcessDpiAwareness Error", (LPCWSTR) L"Error", MB_OK );
	}

	POINT pt;
	pt.x = 1;
	pt.y = 1;
	UINT dpix = 0, dpiy = 0;
	HMONITOR hMonitor = MonitorFromPoint( pt, MONITOR_DEFAULTTONEAREST );
	hr = GetDpiForMonitor( hMonitor, MDT_EFFECTIVE_DPI, &dpix, &dpiy );
	if( hr != S_OK ) {
		MessageBox( NULL, (LPCWSTR) L"GetDpiForMonitor failed", (LPCWSTR) L"Notification", MB_OK );
		return FALSE;
	}
	CDPI dpi;
	dpi.SetScale( dpix );

	// Создаём окно.
	COverlappedWindow wnd( dpi );
	if ( !wnd.RegisterClass() )
		return -1;
	wnd.Create();
	wnd.Show( nCmdShow );

	MSG msg;
	HACCEL hAccel = LoadAccelerators( hInstance, MAKEINTRESOURCE( IDR_ACCELERATOR1 ) );
	while( GetMessage( &msg, NULL, 0, 0 ) ) {
		if (TranslateAccelerator( wnd.GetHandle(), hAccel, &msg ) == 0 ) { 
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
	}

	return (int)(msg.wParam);
}
// 2016
// Автор: Гусев Илья
// Описание: Точка входа в приложение.

#include <OverlappedWindow.h>

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
	COverlappedWindow wnd;
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
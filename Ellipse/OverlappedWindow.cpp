// 2016
// Автор: Гусев Илья

#include <OverlappedWindow.h>
#include <strsafe.h>
#include <cmath>

#define PI 3.14159265

#pragma comment(lib,"msimg32") 

bool COverlappedWindow::RegisterClass()
{
	HINSTANCE hInstance = ::GetModuleHandle(NULL);
	WNDCLASSEX wind;
	wind.cbSize = sizeof(WNDCLASSEX); 
	wind.style = CS_HREDRAW | CS_VREDRAW;
	wind.lpfnWndProc = windowProc;
	wind.cbClsExtra = 0;
	wind.cbWndExtra = 0;
	wind.hInstance = hInstance;
	wind.hIcon = LoadIcon( hInstance,IDI_APPLICATION );
	wind.hCursor = ::LoadCursor(NULL, IDC_ARROW);
	wind.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);;
	wind.lpszMenuName = NULL;
	wind.lpszClassName = L"COverlappedWindow";
	wind.hIconSm = LoadIcon( hInstance, IDI_APPLICATION );  

	if( static_cast<int>( RegisterClassEx( &wind ) ) == 0 ) {
		return false;
	}
	return true;
}

bool COverlappedWindow::Create()
{
	HINSTANCE hInstance = ::GetModuleHandle( NULL );
	handle = CreateWindowEx( WS_EX_LAYERED, L"COverlappedWindow", L"Ellipse", WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, hInstance, this );
	if( !handle ) { 
		MessageBox( NULL, L"Call to CreateWindow failed!", L"Ellipse", NULL ); 
		return false;
	} 
	SetWindowText( handle, L"Ellipse" );
	SetLayeredWindowAttributes( handle, 0, 255, LWA_ALPHA );
	bkBitmap = LoadBitmap( hInstance, MAKEINTRESOURCE(IDB_BITMAP1) );
	scaleBitmap = LoadBitmap( hInstance, MAKEINTRESOURCE(IDB_BITMAP2) );
	scale.SetBitmap( scaleBitmap );
	return true;
}

bool COverlappedWindow::Show( int cmdShow ) 
{
	ShowWindow( handle, cmdShow );
	return true;
}

void COverlappedWindow::SetScale( int scale )
{
	this->dpi.SetScale( scale );
}

// Оконная процедура с обработкой сообщений.
LRESULT CALLBACK COverlappedWindow::windowProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	if( msg == WM_NCCREATE ) {
		CREATESTRUCT* tmp = reinterpret_cast<CREATESTRUCT*>( lParam );
		COverlappedWindow* thisWnd = static_cast<COverlappedWindow*>( tmp->lpCreateParams );
		::SetWindowLongPtr( hwnd, GWL_USERDATA, reinterpret_cast<LONG_PTR>( thisWnd ) );
		thisWnd->handle = hwnd;
		return 1;
	}
	COverlappedWindow* ptr = (COverlappedWindow*)::GetWindowLongPtr( hwnd, GWL_USERDATA );
	HINSTANCE hInstance = ::GetModuleHandle( NULL );
	switch (msg) {
		case WM_PAINT: {
			PAINTSTRUCT ps; 
			HDC hdc = BeginPaint( hwnd, &ps );
			ptr->onPaint( hdc );
			EndPaint( hwnd, &ps ); 
			return 0;
		}

		case WM_SIZE:
			RECT rc;
			GetClientRect( hwnd, &rc );
			ptr->ellipse.MoveTo( rc.left, rc.top, rc.right, rc.bottom );
			InvalidateRect( hwnd, NULL, TRUE ); 
			return 0;

		case WM_DPICHANGED: {
			ptr->SetScale(LOWORD(wParam));
			InvalidateRect( hwnd, NULL, TRUE ); 
			break;
		}

		case WM_COMMAND: 
			switch ( LOWORD( wParam ) ) {
				case ID_ACCELERATOR40001:
					ptr->ellipse.Move( 20, 0 );
					InvalidateRect( hwnd, NULL, TRUE ); 
					break; 
				default: 
					break; 
			}
			return 0;

		case WM_ERASEBKGND:
			return (LRESULT)1;

		case WM_DESTROY: 
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc( hwnd, msg, wParam, lParam );
	}
	return 0;
}

// Обработка сообщения WM_PAINT.
void COverlappedWindow::onPaint( HDC hdc ) 
{
	RECT rect;
	GetClientRect( handle, &rect );

	// Создаём временный конекст с временной битмапкой.
	HDC hdcMem = CreateCompatibleDC( hdc );
	HBITMAP bitmap = CreateCompatibleBitmap( hdc, rect.right - rect.left, rect.bottom - rect.top );
	HBITMAP bitmapOld = static_cast<HBITMAP>( SelectObject( hdcMem, bitmap ) );

	// Рисуем всё на нём.
	drawBackground( hdcMem );
	ellipse.Draw( hdcMem );
	scale.Draw( hdcMem, dpi, 0, 0, false );
	scale.Draw( hdcMem, dpi, 0, 200, true );
	int angle = static_cast<int>( atan( static_cast<double>( rect.bottom-rect.top ) / 
		( rect.right-rect.left ) ) * 180 / PI * 10 );
	drawText( hdcMem, rect.left+30, rect.bottom-45, 40, angle );
	
	// Подставляем его вместо оригинального.
	BitBlt( hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, hdcMem, 0, 0, SRCCOPY );
	SelectObject( hdcMem, bitmapOld );
	DeleteObject( bitmap );
	DeleteDC( hdcMem );
}

// Отрисовка фона в данном контексте.
void COverlappedWindow::drawBackground( HDC hdc )
{
	RECT rect;
	GetClientRect( handle, &rect );

	BITMAP bitmap;
	GetObject( bkBitmap, sizeof(BITMAP), &bitmap );

	HDC hdcMem = CreateCompatibleDC( hdc );
	HBITMAP bkBmOld = static_cast<HBITMAP>( SelectObject( hdcMem, bkBitmap ) );
	StretchBlt( hdc, 0, 0, rect.right, rect.bottom, hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY );
	SelectObject( hdcMem, bkBmOld );
	DeleteDC( hdcMem );
}

// Отрисовка текста в данном контексте и с данными параметрами.
void COverlappedWindow::drawText( HDC hdc, int x, int y, int size, int angle )
{
	SetBkMode( hdc, TRANSPARENT );
	PLOGFONT plf = static_cast<PLOGFONT>( LocalAlloc( LPTR, sizeof( LOGFONT ) ) );
	plf->lfWeight = FW_NORMAL; 
	plf->lfHeight = size; 
	plf->lfEscapement = angle; 
	HFONT hfnt = CreateFontIndirect( plf ); 
	HFONT hfntPrev = static_cast<HFONT>( SelectObject( hdc, hfnt ) );
	WCHAR lpszRotate[22] = TEXT( "Friendship is magic." );
	TextOut( hdc, x, y, lpszRotate, 20 ); 
	SelectObject( hdc, hfntPrev ); 
	DeleteObject( hfnt ); 
}
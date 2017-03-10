// 2016
// Автор: Гусев Илья

#include <Scale.h>

void CScale::Draw( HDC hdc, CDPI dpi, int x, int y, bool dpiScalingEnabled )
{
	BITMAP bm;
	GetObject( bitmap, sizeof(BITMAP), &bm );

	HDC hdcMem = CreateCompatibleDC( hdc );
	HBITMAP bmOld = static_cast<HBITMAP>( SelectObject( hdcMem, bitmap ) );

	const float cmPerPixel = 0.026458;
	int width = static_cast<int>( 4.0 / cmPerPixel );
	if( dpiScalingEnabled ) {
		width = dpi.Scale( width );
	}
	StretchBlt( hdc, x, y, width, bm.bmHeight, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY );

	SelectObject( hdcMem, bmOld );
	DeleteDC( hdcMem );
}
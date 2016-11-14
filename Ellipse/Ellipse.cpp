#include <Ellipse.h>

void CEllipse::Draw( HDC hdc )
{
	HDC tempHdc = CreateCompatibleDC(hdc);
	BLENDFUNCTION blend = {AC_SRC_OVER, 0, 127, 0};

	HBITMAP hbitmap = CreateCompatibleBitmap(hdc, right - left, bottom - top);
	SelectObject(tempHdc, hbitmap);

	HBRUSH hBrush = CreateSolidBrush(brush);
	HBRUSH hOldBrush = static_cast<HBRUSH>( SelectObject(tempHdc, hBrush) );
	Ellipse( tempHdc, left, top, right, bottom );
	SelectObject( tempHdc, hOldBrush );
	DeleteObject( hBrush );

	AlphaBlend(hdc, 0, 0, right-left, bottom-top, tempHdc, 0, 0, right-left, bottom-top, blend); 
	DeleteObject( hbitmap );
	DeleteDC(tempHdc);
}

void CEllipse::MoveTo( int _left, int _top, int _right, int _bottom )
{
	left = _left;
	top = _top;
	right = _right;
	bottom = _bottom;
}
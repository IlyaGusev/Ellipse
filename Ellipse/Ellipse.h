#pragma once

#include <windows.h>

class CEllipse {
public:
	CEllipse( int _left, int _top, int _right, int _bottom, COLORREF _brush ) : 
		left(_left), top(_top), right(_right), bottom(_bottom), brush(_brush){}

	void Draw( HDC hdc );
	void MoveTo( int _left, int _top, int _right, int _bottom );
	void Move( int dx, int dy ) { left += dx; right += dx; top += dy; bottom += dy; }

private:
	int left;
	int top;
	int right;
	int bottom;
	COLORREF brush;
};
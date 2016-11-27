// 2016
// Автор: Гусев Илья
// Описание: Класс для хранения коородинат и отрисовки эллипса.

#pragma once

#include <windows.h>

// Класс для хранения коородинат и отрисовки эллипса.
class CEllipse {
public:
	CEllipse( int _left, int _top, int _right, int _bottom, COLORREF _brush ) : 
		left(_left), top(_top), right(_right), bottom(_bottom), brush(_brush){}
	
	// Отрисовка эллипса в данном контексте.
	void Draw( HDC hdc );
	// Передвижение эллипса на конкретную позицию.
	void MoveTo( int _left, int _top, int _right, int _bottom );
	// Передвижение эллипса на dx, dy.
	void Move( int dx, int dy ) { left += dx; right += dx; top += dy; bottom += dy; }

private:
	int left;
	int top;
	int right;
	int bottom;
	COLORREF brush;
};
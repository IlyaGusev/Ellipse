// 2016
// Автор: Гусев Илья
// Описание: Класс, осуществляющий отрисовку главного окна.

#pragma once

#include <windows.h>
#include <stdlib.h> 
#include <string>
#include <wchar.h>
#include <string.h> 
#include <tchar.h>  

#include <resource.h>
#include <Ellipse.h>


// Класс, осуществляющий отрисовку главного окна. Отрисовывает фон, эллипс и текст.
class COverlappedWindow {
public:
	COverlappedWindow() : ellipse( 0, 0, 100, 50, RGB(0, 255, 0) ) {};
	~COverlappedWindow() {};

	// Регистрация окна.
	static bool RegisterClass();
	// Создание окна.
	bool Create();
	// Показ окна.
	bool Show( int cmdShow );
	// Получение хэндла окна.
	HWND GetHandle() { return handle; }

private:
	void onPaint( HDC hdc );
	void drawBackground( HDC hdc );
	void drawText( HDC hdc, int x, int y, int size, int angle );
	static LRESULT __stdcall windowProc( HWND handle, UINT message, WPARAM wParam, LPARAM lParam );

	HWND handle;
	CEllipse ellipse;
	HBITMAP bkBitmap;
};
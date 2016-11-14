#pragma once

#include <windows.h>
#include <stdlib.h> 
#include <string>
#include <wchar.h>
#include <string.h> 
#include <tchar.h>  

#include <resource.h>
#include <Ellipse.h>

class COverlappedWindow {
public:
	COverlappedWindow() : ellipse( 0, 0, 100, 50, RGB(0, 255, 0) ) {};
	~COverlappedWindow() {};

	static bool RegisterClass();
	bool Create();
	bool Show(int cmdShow);
	HWND handle;

private:
	void onPaint( HDC hdc );
	void drawBackground( HDC hdc );
	void drawText( HDC hdc, int x, int y, int size, int angle );

	CEllipse ellipse;
	HBITMAP bkBitmap;
	static LRESULT __stdcall windowProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	
};
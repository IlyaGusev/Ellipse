// 2016
// Автор: Гусев Илья
// Описание: Масштабируемая линейка.

#pragma once

#include <windows.h>
#include <DPI.h>

// Класс для линейки.
class CScale {
public:
	CScale(){}

	// Отрисовка линейки с масштабирвоанием и без.
	void Draw( HDC hdc, CDPI dpi, int x, int y, bool dpiScalingEnabled );
	// Задание картинки линейки.
	void SetBitmap( HBITMAP bm ) { bitmap = bm; }
private:
	HBITMAP bitmap;
};
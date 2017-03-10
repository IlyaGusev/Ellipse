// 2016
// �����: ����� ����
// ��������: �������������� �������.

#pragma once

#include <windows.h>
#include <DPI.h>

// ����� ��� �������.
class CScale {
public:
	CScale(){}

	// ��������� ������� � ���������������� � ���.
	void Draw( HDC hdc, CDPI dpi, int x, int y, bool dpiScalingEnabled );
	// ������� �������� �������.
	void SetBitmap( HBITMAP bm ) { bitmap = bm; }
private:
	HBITMAP bitmap;
};
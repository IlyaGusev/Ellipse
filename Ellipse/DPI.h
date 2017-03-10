#pragma once
#include <ShellScalingAPI.h>

class CDPI {
public:
	CDPI() {
		m_nScaleFactor = 0;
		m_nScaleFactorSDA = 0;
		m_Awareness = PROCESS_DPI_UNAWARE;
	}

	int Scale( int x ) {
		return MulDiv(x, m_nScaleFactor, 100);
	}

	UINT GetScale() {
		return m_nScaleFactor;
	}

	void SetScale(__in UINT iDPI) {
		m_nScaleFactor = MulDiv(iDPI, 100, 96);
		if (m_nScaleFactorSDA == 0) {
			m_nScaleFactorSDA = m_nScaleFactor;  // Save the first scale factor, which is all that SDA apps know about
		}
		return;
	}

	// Scale rectangle from raw pixels to relative pixels.
	void ScaleRect(__inout RECT *pRect)
	{
		pRect->left = Scale(pRect->left);
		pRect->right = Scale(pRect->right);
		pRect->top = Scale(pRect->top);
		pRect->bottom = Scale(pRect->bottom);
	}

	// Scale Point from raw pixels to relative pixels.
	void ScalePoint(__inout POINT *pPoint)
	{
		pPoint->x = Scale(pPoint->x);
		pPoint->y = Scale(pPoint->y);
	}

private:
	UINT m_nScaleFactor;
	UINT m_nScaleFactorSDA;
	PROCESS_DPI_AWARENESS m_Awareness;
};
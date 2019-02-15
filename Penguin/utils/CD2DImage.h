extern HINSTANCE hAppInstance;

#include <D2D1.h>// header for Direct2D
#include <d2d1helper.h>  
#include <Dwrite.h>
#include <atlstr.h>
#include <wincodec.h>  
#include "CD2D.h"
#include "Arith.h"

#pragma once

class CD2DImage{
public:
	CD2DImage();
	~CD2DImage();
	
	BOOL LoadImageFromFile(LPCTSTR lpPath);
	
	BOOL LoadImageFromRes(HINSTANCE hInstance,long resId, LPCTSTR resourceType);

	ID2D1Bitmap *				GetBitMap();
	ID2D1BitmapBrush *			GetBitMapBrush();
	Shape<int>					GetShape();
private:

	IWICImagingFactory *		m_pImageFactory;
	ID2D1Bitmap *				m_pBitmap;
	ID2D1BitmapBrush *			m_pBitmapBrush;
	Shape<int>					m_shape;
};
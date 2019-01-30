extern HINSTANCE hAppInstance;

#include <D2D1.h>// header for Direct2D
#include <d2d1helper.h>  
#include <Dwrite.h>
#include <atlstr.h>
#include <wincodec.h>  
#include "Arith.h"
#define SAFE_RELEASE(P) if(P){P->Release() ; P = NULL ;}

#ifndef _CD2DIMAGE_H
#define _CD2DIMAGE_H

#pragma once

class CD2DImage{
public:
	CD2DImage();
	~CD2DImage();
	//从文件载入图像
	BOOL LoadImageFromFile(ID2D1HwndRenderTarget* pRenderTarget,LPCTSTR lpPath);
	//从资源载入图像
	BOOL LoadImageFromRes(ID2D1HwndRenderTarget* pRenderTarget, HINSTANCE hInstance,long resId, LPCTSTR resourceType);

	ID2D1Bitmap * pBitMap();
private:

	IWICImagingFactory *		m_pImageFactory;
	ID2D1Bitmap *				m_pBitmap;
};

#endif

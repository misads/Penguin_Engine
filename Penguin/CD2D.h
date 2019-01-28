#ifndef _SERVER_
#ifdef _D2DRender_


#include <D2D1.h>// header for Direct2D
#include <d2d1helper.h>  
#include <Dwrite.h>
#include <atlstr.h>
#include <wincodec.h>  
#include "Arith.h"
#include "CD2DImage.h"

#define SAFE_RELEASE(P) if(P){P->Release() ; P = NULL ;}

#ifndef _CD2D_H
#define _CD2D_H

#pragma once

#define AfxMessageBox(msg) MessageBox(0,msg,L"",0);

//extern void AfxMessageBox(LPCTSTR lpText);

extern DWORD D2DRGB(BYTE r, BYTE g, BYTE b);

class CD2D{
public:
	CD2D();
	~CD2D();

public:
	//初始化
	BOOL CreateD2DResource(HWND hWnd);
	//开始绘画
	void	BeginDraw();
	//结束绘画
	void	EndDraw();
	//清屏
	BOOL ClearScreen();
	BOOL ClearScreen(FLOAT r, FLOAT g, FLOAT b, FLOAT a = 1.0F);
	BOOL ClearScreen(D2D1::ColorF::Enum clearColor);
	//画文本
	BOOL DrawTextB(LPCTSTR sFontName, FLOAT fFontSize,
		FLOAT left, FLOAT top, FLOAT right, FLOAT bottom, CString sText, bool AlienToRight = false, bool bYellow = false, FLOAT _alpha=1.0F);
	BOOL DrawTextC(LPCTSTR sFontName, FLOAT fFontSize,
		FLOAT left, FLOAT top, FLOAT right, FLOAT bottom, CString sText, DWORD rgb = 0, FLOAT _Alpha = 1.0F, bool AlienToRight = false);
	//画矩形
	BOOL DrawRectangle(FLOAT left, FLOAT top, FLOAT right, FLOAT bottom,FLOAT _width=1.0F);
	//画图像
	BOOL DrawBmp(CD2DImage Image, FLOAT _x, FLOAT _y, FLOAT _width, FLOAT _height, 
		FLOAT alpha=1.0F, int nSrcX = 0, int nSrcY = 0, int nSrcWidth = 0, int nSrcHeight = 0);

	
	//清理
	void Cleanup(void);

	ID2D1HwndRenderTarget* pRenderTarget();
protected:

private:
	ID2D1Factory*				m_pD2DFactory;              // Direct2D factory
	ID2D1HwndRenderTarget*		m_pRenderTarget;   // Render target
	ID2D1SolidColorBrush*			m_pBlackBrush;      // A black brush, reflect the line color
	IDWriteFactory*				m_pDWriteFactory;     //Dwrite
	ID2D1SolidColorBrush*			m_pWhiteBrush;
	ID2D1SolidColorBrush*			m_pBlueBrush;
	ID2D1SolidColorBrush*			m_pYellowBrush;

	                              // Render area
	HWND m_hWnd;                             // Window handle
};

#endif
#endif

#endif
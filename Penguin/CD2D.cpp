#include"stdafx.h"

#ifndef _SERVER_

#ifdef _D2DRender_

#include "CD2D.h"

#pragma warning (disable: 4244) 

DWORD D2DRGB(BYTE r, BYTE g, BYTE b){
	return ((COLORREF)(((BYTE)(b) | ((WORD)((BYTE)(g)) << 8)) | (((DWORD)(BYTE)(r)) << 16)));
}

CD2D::CD2D()
{
	m_pD2DFactory = NULL;
	m_pRenderTarget = NULL;
	m_pBlackBrush = NULL;
	m_pWhiteBrush = NULL;
	m_pDWriteFactory = NULL;
	m_pBlueBrush = NULL; 
	m_pYellowBrush = NULL;
	 m_hWnd = NULL;
	//g_bitmap = NULL;
}

CD2D::~CD2D()
{
	if ( m_hWnd)
	{
		Cleanup();
	}
}

void	CD2D::BeginDraw(){
	m_pRenderTarget->BeginDraw();
}
void	CD2D::EndDraw(){
	m_pRenderTarget->EndDraw();
}
BOOL CD2D::ClearScreen(){
	m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	return TRUE;
}
BOOL CD2D::ClearScreen(FLOAT r,FLOAT g,FLOAT b,FLOAT a){
	m_pRenderTarget->Clear(D2D1::ColorF(r,g,b,a));
	return TRUE;
}
BOOL CD2D::ClearScreen(D2D1::ColorF::Enum clearColor){
	m_pRenderTarget->Clear(D2D1::ColorF(clearColor));
	return TRUE;
}

BOOL CD2D::CreateD2DResource(HWND m_hWnd)
{
	if (!m_pRenderTarget)
	{

		CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

		HRESULT hr;

		hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
		if (FAILED(hr))
		{
			AfxMessageBox(_T("创建factory失败！"));
			return (FALSE);
		}

		 this->m_hWnd =  m_hWnd;
		// Obtain the size of the drawing area
		RECT rc;
		GetClientRect( m_hWnd, &rc);

		D2D1_PRESENT_OPTIONS d2dOptions;

		if (Game.IsVerticalSync())d2dOptions = D2D1_PRESENT_OPTIONS_NONE;
		else d2dOptions = D2D1_PRESENT_OPTIONS_IMMEDIATELY;
		// Create a Direct2D render target
		hr = m_pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1:: HwndRenderTargetProperties(
			 m_hWnd,
			D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top),
			d2dOptions //垂直同步
			),
			&m_pRenderTarget
			);
		m_pRenderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
		if (FAILED(hr))
		{
			AfxMessageBox(_T("创建target失败！"));
			return (FALSE);
		}

		// Create a brush
		hr = m_pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Black),
			&m_pBlackBrush
			);
		hr = m_pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::White),
			&m_pWhiteBrush
			);
		hr = m_pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(0.0F,0.6F,0.8F),
			&m_pBlueBrush
			);
		hr = m_pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Yellow),
			&m_pYellowBrush
			);
		if (FAILED(hr))
		{
			AfxMessageBox(_T("创建brush失败！"));
			return (FALSE);
		}
		//

		// Create DirectWrite Factory
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&m_pDWriteFactory)
			);
		if (FAILED(hr))
		{
			AfxMessageBox(_T("创建DirectWrite失败！"));
			return (FALSE);
		}



		return (TRUE);

	}
	return (FALSE);

}

BOOL CD2D::DrawTextB(LPCTSTR sFontName, FLOAT fFontSize,
	FLOAT left, FLOAT top, FLOAT right, FLOAT bottom, CString sText, bool AlienToRight, bool bYellow,FLOAT _alpha){
	IDWriteTextFormat* g_pTextFormat = NULL;

	HRESULT hr;
	RECT rc;
	GetClientRect( m_hWnd, &rc);


	hr = m_pDWriteFactory->CreateTextFormat(
		sFontName,                   // Font family name
		NULL,                          // Font collection(NULL sets it to the system font collection)
		DWRITE_FONT_WEIGHT_REGULAR,    // Weight
		DWRITE_FONT_STYLE_NORMAL,      // Style
		DWRITE_FONT_STRETCH_NORMAL,    // Stretch
		fFontSize,                     // Size    
		L"en-us",                      // Local
		&g_pTextFormat                 // Pointer to recieve the created object
		);
	if (FAILED(hr))
	{
		AfxMessageBox(_T("创建DirectWrite失败！"));
		return(FALSE);
	}

	// Create text layout rect
	if (AlienToRight) g_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);


	D2D1_RECT_F textLayoutRect = D2D1::RectF(left, top, right, bottom);

	ID2D1SolidColorBrush *pBrush;

	if (bYellow)  pBrush = m_pYellowBrush;
	else pBrush = m_pWhiteBrush; 

	pBrush->SetOpacity(_alpha);
	// Draw text
	//m_pRenderTarget->BeginDraw();
	m_pRenderTarget->DrawText(
		sText,           // Text to render
		sText.GetLength(),       // Text length
		g_pTextFormat,     // Text format
		textLayoutRect,    // The region of the window where the text will be rendered
		pBrush     // The brush used to draw the text
		);
	//m_pRenderTarget->EndDraw();

	g_pTextFormat->Release();
	return (TRUE);
}

#define MAX_TEXT_WIDTH 400
#define MAX_TEXT_HEIGHT 200

BOOL CD2D::DrawTextC(LPCTSTR sFontName, FLOAT fFontSize,
	FLOAT left, FLOAT top, FLOAT right, FLOAT bottom, CString sText, DWORD rgb, FLOAT _Alpha, bool AlienToRight){
	IDWriteTextFormat* g_pTextFormat = NULL;

	HRESULT hr;

	if (!right)right = left + MAX_TEXT_WIDTH;
	if (!bottom)bottom = top + MAX_TEXT_HEIGHT;
	if (!left)left = right - MAX_TEXT_WIDTH;
	if (!top)top = bottom + MAX_TEXT_HEIGHT;

	
	hr = m_pDWriteFactory->CreateTextFormat(
		sFontName,                   // Font family name
		NULL,                          // Font collection(NULL sets it to the system font collection)
		DWRITE_FONT_WEIGHT_REGULAR,    // Weight
		DWRITE_FONT_STYLE_NORMAL,      // Style
		DWRITE_FONT_STRETCH_NORMAL,    // Stretch
		fFontSize,                     // Size    
		L"en-us",                      // Local
		&g_pTextFormat                 // Pointer to recieve the created object
		);
	if (FAILED(hr))
	{
		OutputDebugString(_T("创建DirectWrite失败！"));
		return(FALSE);
	}

	// Create text layout rect
	if (AlienToRight) g_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);


	D2D1_RECT_F textLayoutRect = D2D1::RectF(left, top, right, bottom);

	ID2D1SolidColorBrush *pBrush;

	m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(rgb, _Alpha), &pBrush);



	m_pRenderTarget->DrawText(
		sText,           // Text to render
		sText.GetLength(),       // Text length
		g_pTextFormat,     // Text format
		textLayoutRect,    // The region of the window where the text will be rendered
		pBrush     // The brush used to draw the text
		);


	g_pTextFormat->Release();
	pBrush->Release();
	return (TRUE);
}

BOOL CD2D::DrawRectangle(FLOAT left, FLOAT top, FLOAT right, FLOAT bottom,FLOAT _width)
{
	//m_pRenderTarget->BeginDraw();

	// Clear background color white


	// Draw Rectangle
	m_pRenderTarget->DrawRectangle(
		D2D1::RectF(left, top, right, bottom),
		m_pBlueBrush, _width
		);


	//HRESULT hr = m_pRenderTarget->EndDraw();

	//if (FAILED(hr))
	//{
	//	AfxMessageBox(_T("创建Direct失败！"));
	//	return (FALSE);
	//}
	return (TRUE);
}
BOOL CD2D::DrawBmp(CD2DImage Image, FLOAT _x, FLOAT _y, FLOAT _width, FLOAT _height, FLOAT alpha, int nSrcX, int nSrcY, int nSrcWidth, int nSrcHeight){

	//D2D1_SIZE_F size = m_pRenderTarget->GetSize();

	if (!nSrcWidth)nSrcWidth = (int)_width;
	if (!nSrcHeight)nSrcHeight = (int)_height;

	D2D1_RECT_F drawRect = { _x, _y, _x+_width, _y+_height };

	D2D1_RECT_F origRect = { nSrcX, nSrcY, nSrcX + nSrcWidth, nSrcY + nSrcHeight };

	m_pRenderTarget->DrawBitmap(Image.pBitMap(), drawRect, alpha, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, origRect);

	return TRUE;
}
void CD2D::Cleanup(void)
{
	SAFE_RELEASE(m_pRenderTarget);
	SAFE_RELEASE(m_pBlackBrush);
	SAFE_RELEASE(m_pWhiteBrush);
	SAFE_RELEASE(m_pBlueBrush);
	SAFE_RELEASE(m_pYellowBrush);
	SAFE_RELEASE(m_pD2DFactory);
	SAFE_RELEASE(m_pDWriteFactory);
	
}

ID2D1HwndRenderTarget* CD2D::pRenderTarget(){
	return m_pRenderTarget;
}
#endif

#endif

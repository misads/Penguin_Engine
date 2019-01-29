#include "stdafx.h"


#include "CD2DImage.h"



CD2DImage::CD2DImage(){
	m_pImageFactory=NULL;
	m_pBitmap=NULL;
}
CD2DImage::~CD2DImage(){
	
//	SAFE_RELEASE(m_pBitmap);
//	SAFE_RELEASE(m_pImageFactory);
}
//从文件载入图像
BOOL CD2DImage::LoadImageFromFile(ID2D1HwndRenderTarget* pRenderTarget, LPCTSTR lpPath){

	HRESULT hr;

	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, __uuidof(m_pImageFactory), (LPVOID*)&m_pImageFactory);

	if (FAILED(hr))
	{
		//AfxMessageBox(_T("创建WICImagingFactory失败！"));
		return (FALSE);
	}

	IWICBitmapDecoder *bitmapdecoder = NULL;
	m_pImageFactory->CreateDecoderFromFilename(lpPath, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &bitmapdecoder);//  


	IWICBitmapFrameDecode  *pframe = NULL;
	bitmapdecoder->GetFrame(0, &pframe);

	IWICFormatConverter * fmtcovter = NULL;
	m_pImageFactory->CreateFormatConverter(&fmtcovter);
	fmtcovter->Initialize(pframe, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0f, WICBitmapPaletteTypeCustom);



	hr=pRenderTarget->CreateBitmapFromWicBitmap(fmtcovter, NULL, &m_pBitmap);
	
	if (FAILED(hr))OutputDebugString(lpPath);

	fmtcovter->Release();
	pframe->Release();
	bitmapdecoder->Release();


	return TRUE;

}

BOOL CD2DImage::LoadImageFromRes(ID2D1HwndRenderTarget* pRenderTarget, HINSTANCE hInstance, long resId, LPCTSTR resourceType){
	
	HRSRC imageResHandle = NULL;
	HGLOBAL imageResDataHandle = NULL;
	IWICStream *pStream = NULL;
	void *pImageFile = NULL;
	DWORD imageFileSize = 0;
	IWICBitmapDecoder *pDecoder = NULL;
	IWICBitmapFrameDecode *pSource = NULL;



	imageResHandle = FindResource(hInstance, MAKEINTRESOURCE(resId), resourceType);

	imageResDataHandle = LoadResource(hInstance, imageResHandle);

	pImageFile = LockResource(imageResDataHandle);

	imageFileSize = SizeofResource(hInstance, imageResHandle);


	HRESULT hr;

	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, __uuidof(m_pImageFactory), (LPVOID*)&m_pImageFactory);

	if (FAILED(hr))
	{
		//AfxMessageBox(_T("创建WICImagingFactory失败！"));
		return (FALSE);
	}


	hr = m_pImageFactory->CreateStream(&pStream);

	pStream->InitializeFromMemory(
		reinterpret_cast<BYTE*>(pImageFile),
		imageFileSize
		);
	
	m_pImageFactory->CreateDecoderFromStream(
		pStream,
		NULL,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
		);

	pDecoder->GetFrame(0, &pSource);

	IWICFormatConverter * fmtcovter = NULL;
	m_pImageFactory->CreateFormatConverter(&fmtcovter);

	fmtcovter->Initialize(
		pSource,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.f,
		WICBitmapPaletteTypeMedianCut
		);

	pRenderTarget->CreateBitmapFromWicBitmap(
		fmtcovter,
		NULL,
		&m_pBitmap
		);


	SAFE_RELEASE(fmtcovter);
	SAFE_RELEASE(pDecoder);
	SAFE_RELEASE(pSource);
	SAFE_RELEASE(pStream);
	SAFE_RELEASE(fmtcovter);



	return TRUE;


}


ID2D1Bitmap * CD2DImage::pBitMap(){
	return m_pBitmap;
}



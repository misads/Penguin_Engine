#include "stdafx.h"

#include "Game.h"

#pragma warning (disable: 4996) 
#pragma warning (disable: 4244) 
#pragma warning (disable: 4258) 


//////////////////////////////////////////////////
//
//		äÖÈ¾º¯Êý
//
//////////////////////////////////////////////////
bool CGame::Render(float fTime){
	static float fLastTime = 0;

	if (fTime != 0){

		if (fTime - fLastTime < 1 / ((MAX_FPS)*1.0f)){
			return true;
		}
		else {
			fLastTime = fTime;
		}
	}



	switch (m_gameState){
	case GAME_MOTION:
		break;
		//äÖÈ¾ÔØÈëÖÐ
	case GAME_LOADING:
		break;
	case GAME_RUNNING:

		D2DC.BeginDraw();
		D2DC.ClearScreen(D2D1::ColorF::Black);
		//m_mD2DGif["ice"].Render(D2DC.pRenderTarget(), fTime, fPoint(0 , 0), fVector(400, 300));
		D2DC.DrawBmp(m_mD2DImage["c"], 0, 0, 400, 300, 1.0F, 0, 0, 100, 100);

		D2DC.DrawBmp(m_mD2DImage["c"], 400, 300, 100, 100, 1.0F, 0, 0, 100, 100);
		//D2DC.DrawTextC(L"Î¢ÈíÑÅºÚ", 35, 1, 1, 0, 0, L"²âÊÔµÄÎÄ×Ö", D2DRGB(0, 0, 0));
		//m_renderObjects["ice"].Render(D2DC.pRenderTarget(), fTime,400,300,400,300);
		//m_renderObjects["ice"].Render(D2DC.pRenderTarget(), fTime, 600, 300, 400, 300);
		//m_mD2DGif["ice"].Render(D2DC.pRenderTarget(), fTime, fPoint(0, 0), fVector(400, 300));
		//D2DC.DrawRectangle(10, 10, 150, 50, 2);
		m_element.Render(fTime);

		D2DC.EndDraw();

		break;



	}



	return true;
}
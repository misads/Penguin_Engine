#include "stdafx.h"
#include "Game.h"
#include "utils/Ini.h"
#include "utils/DSound.h"
#include "resource.h"


#pragma warning (disable: 4996) 
#pragma warning (disable: 4244) 
#pragma warning (disable: 4258) 

using namespace DSound;


HANDLE RenderMutex;//渲染的互斥体


CGame::CGame(){
	
	m_fTime = 0;
	m_vResolution = GetScreenResolution();

	RenderMutex = CreateSemaphore(NULL, 1, 1, NULL);

	m_gameState = GAME_LOADING;


	memset(m_KeyState, 0, sizeof(m_KeyState));//按键信息清零


}

CGame::~CGame(){
	CloseHandle(RenderMutex);
}
//游戏初始化
bool CGame::InitGame(HWND hWnd){

	m_ResolutionSetting.nResolutionNow = 0;
	m_ResolutionSetting.vResolution.push_back(Shape<int>(635, 485));
	m_ResolutionSetting.vResolution.push_back(Shape<int>(889, 679));
	m_ResolutionSetting.vResolution.push_back(Shape<int>(1005, 768));
	m_ResolutionSetting.vResolution.push_back(Shape<int>(1245, 951));
	m_ResolutionSetting.vResolution.push_back(Shape<int>(1414, 1080));
	m_ResolutionSetting.vResolution.push_back(Shape<int>(1700, 1331));
	
	Sleep(10);
	WaitForSingleObject(RenderMutex, INFINITE);
	
	if (!LoadRes())return false;
	ReleaseSemaphore(RenderMutex, 1, NULL);



////////////////////////////
//
//
////////////////////////////

///////////////////////////
//
//初始的游戏状态//////////////
#ifdef DEBUG_PLAY
	
#else
	Sleep(750);
#endif
	m_gameState = GAME_RUNNING;

	//m_gameState = GAME_STATE::GAME_CAPTION;
	//m_gameState = GAME_STATE::GAME_MAIN_MENU;

///////////////////////////
//
///////////////////////////



	return true;
}


#define LoadImg(alias,path)  	m_mD2DImage.insert(pair<string, CD2DImage>(alias, d2dImageBuf));m_mD2DImage[alias].LoadImageFromFile(TEXT(path));
//#define LoadBlock(alias,value) 	m_mBlock.insert(pair<string, char>(alias, (char)value));


//初始化英雄

#ifdef DEBUG_PLAY

#define LOADING_DELAY 0
#else
#define LOADING_DELAY 25

#endif
//////////////////////
//
//
// 加载资源 音效 动画 数据等等
//
//////////////////////
bool CGame::LoadRes(){


	CD2DImage d2dImageBuf;
	LoadImg("c", "test/c.png");
	LoadImg("ice1", "Images/Image 1336.png");
	LoadImg("ice2", "Images/Image 1337.png");
	LoadImg("ice3", "Images/Image 1338.png");
	LoadImg("ice4", "Images/Image 1339.png");
	LoadImg("ice5", "Images/Image 1340.png");
	LoadImg("ice6", "Images/Image 1341.png");
	LoadImg("ice7", "Images/Image 1342.png");
	LoadImg("ice8", "Images/Image 1343.png");
	LoadImg("ice9", "Images/Image 1344.png");
	LoadImg("ice10", "Images/Image 1345.png");
	LoadImg("ice11", "Images/Image 1346.png");
	LoadImg("ice12", "Images/Image 1347.png");
	LoadImg("ice13", "Images/Image 1348.png");
	

	m_renderObjects["ice"].AddImage(m_mD2DImage["ice1"], Shape<int>(800, 600));
	m_renderObjects["ice"].AddImage(m_mD2DImage["ice2"], Shape<int>(800, 600));
	m_renderObjects["ice"].AddImage(m_mD2DImage["ice3"], Shape<int>(800, 600));
	m_renderObjects["ice"].AddImage(m_mD2DImage["ice4"], Shape<int>(800, 600));
	m_renderObjects["ice"].AddImage(m_mD2DImage["ice5"], Shape<int>(800, 600));
	m_renderObjects["ice"].AddImage(m_mD2DImage["ice6"], Shape<int>(800, 600));
	m_renderObjects["ice"].AddImage(m_mD2DImage["ice7"], Shape<int>(800, 600));
	m_renderObjects["ice"].AddImage(m_mD2DImage["ice8"], Shape<int>(800, 600));
	m_renderObjects["ice"].AddImage(m_mD2DImage["ice9"], Shape<int>(800, 600));
	m_renderObjects["ice"].AddImage(m_mD2DImage["ice10"], Shape<int>(800, 600));
	m_renderObjects["ice"].AddImage(m_mD2DImage["ice11"], Shape<int>(800, 600));
	m_renderObjects["ice"].AddImage(m_mD2DImage["ice12"], Shape<int>(800, 600));
	m_renderObjects["ice"].AddImage(m_mD2DImage["ice13"], Shape<int>(800, 600));
	m_renderObjects["ice"].SetFps(50);
	m_renderObjects["ice"].SetCycles(-1);
	m_renderObjects["ice"].Reset();
	//m_element.SetObject(m_renderObjects["ice"]);
	
	//m_element.SetObject(L"微软雅黑", 35, L"测试的文字", D2DRGB(0, 0, 0));
	//m_element.SetShape(400, 300);
	//m_element.SetPos(.1, .1);
	//m_element.SetText(L"Enter...");
	//m_element.SetAlphaChange(ALPHA_DISAPPEAR_APPEAR, 1.0);
	//m_element.Show();
	m_element.SetRenderTarget(D2DC.GetRenderTarget()); //static 只需要设置一次
	m_element.SetObject(m_renderObjects["ice"]);
	//m_renderObjects["ice"].Reset();
	//m_element.SetObject(m_mD2DImage["ice1"]);
	m_element.SetShape(400, 300);
	m_element.SetPos(100, 100);
	//m_element.SetAlphaChange(ALPHA_DISAPPEAR_APPEAR, 1.0);
	m_element.Show();
	//m_element.MoveAlong((Direction)4, 100);
	m_element.AddTranform(new Translation(Down_Right, 200));
	m_element.AddTranform(new AlphaChange(ALPHA_DISAPPEAR, 3.0f));
	///////////////
	//	加载声音
	/////////////

	Sound.SetSoundFilePath(L"./wav/");
	Sound.LoadSound("miss", L"Sound 1041.wav");

	////////////////
	//
	////////////////

	ReleaseSemaphore(RenderMutex, 1, NULL);

	Sleep(LOADING_DELAY);
	WaitForSingleObject(RenderMutex, INFINITE);
	////////////////
	// 加载地图
	///////////////
	if (!LoadMap())return false;
	///////////////
	//
	///////////////
	ReleaseSemaphore(RenderMutex, 1, NULL);

	WaitForSingleObject(RenderMutex, INFINITE);

	return true;
}

/////////////////////////
//     加载地图
/////////////////////////
bool	CGame::LoadMap(){

	return true;
}


#define LoadImgM(alias,path)  	m_mD2DImage.insert(pair<string, CD2DImage>(alias, d2dImageBuf));m_mD2DImage[alias].LoadImageFromFile(D2DC.pRenderTarget(), path);

//读取游戏设置
bool	CGame::LoadConfig(){

	if (!Ini.isExist(L"./config.ini")) _ERROR(L"找不到配置文件", true);


	m_gameConfig.SCREEN_WIDTH = Ini.ReadInt(L"Resolution", L"Width", 1366, L"./config.ini");
	m_gameConfig.SCREEN_HEIGHT = Ini.ReadInt(TEXT("Resolution"), TEXT("Height"), 768, TEXT("./config.ini"));
	m_gameConfig.FULL_SCREEN = (Ini.ReadInt(TEXT("Resolution"), TEXT("FullScreen"), 0, TEXT("./config.ini"))!=0);
	m_gameConfig.HARDWARE_RENDER = (Ini.ReadInt(TEXT("Video"), TEXT("HardWareAcceleration"), 1, TEXT("./config.ini")) != 0);
	m_gameConfig.VERTICAL_SYNC = (Ini.ReadInt(TEXT("Video"), TEXT("VerticalSync"), 1, TEXT("./config.ini")) != 0);
	m_gameConfig.PERFORMANCE_PRIOR = (Ini.ReadInt(TEXT("Video"), TEXT("PerformancePrior"), 1, TEXT("./config.ini")) != 0);
	m_gameConfig.FPS = Ini.ReadInt(L"Video", L"Fps", 3, L"./config.ini");



	return true;
}

#define BuffToType(value, type) value = *(type*)(cBuff + nBuffLength); nBuffLength += sizeof(type);
#define BuffToInt(value) BuffToType(value,int)
#define BuffToByte(value) BuffToType(value,BYTE)

bool CGame::LoadGame(int _which){

	return true;
}

#define	AddToBuff(value,type) *(type*)(cBuff + nBuffLength) = value;nBuffLength += sizeof(type);
#define AddIntToBuff(value) AddToBuff(value,int)
#define AddByteToBuff(value) AddToBuff(value,BYTE)

bool CGame::SaveGame(int _which){

	
	int nBuff[] = {
	1
	};

	//Ini.WriteBinary(path, cBuff, nBuffLength);




	return true;
}




//全屏模式 调整分辨率
bool CGame::AlterResolution(){

	if (m_gameConfig.FULL_SCREEN){
		SetScreenResolution(m_gameConfig.SCREEN_WIDTH, m_gameConfig.SCREEN_HEIGHT);  //改分辨率
	}

	return true;
}


////////////////////////
//
//  消息处理函数
//
////////////////////////
LRESULT CALLBACK CGame::MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){

	CString cstring;
	///////////////////////////////
	//无论什么游戏状态都做的处理
	//////////////////////////////
	switch (uMsg){

	case WM_KEYDOWN:
		m_KeyState[wParam] = KEYDOWN;
		switch (wParam){
		case VK_F8:
			m_ResolutionSetting.nResolutionNow++;
			if (m_ResolutionSetting.nResolutionNow >= m_ResolutionSetting.vResolution.size())m_ResolutionSetting.nResolutionNow = 0;
			MoveWindow(hWnd, 0, 0, m_ResolutionSetting.vResolution[m_ResolutionSetting.nResolutionNow].width,
				m_ResolutionSetting.vResolution[m_ResolutionSetting.nResolutionNow].height, true);
			break;
		case VK_SPACE:
			if (!(m_element.IsVisible())) m_element.Show();
			break;
		}
		break;

	case WM_KEYUP:
		m_KeyState[wParam] = KEYUP;

		break;
	}

	/////////////////////////////
	//分不同游戏状态分别进行处理
	/////////////////////////////
	switch (m_gameState)
	{

	case GAME_MENU:

	
	case GAME_OVER:
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


//获取从游戏开始到现在经过的时间(s)
float CGame::fTime(){
	SYSTEMTIME		sTime;
	GetSystemTime(&sTime);
	static WORD		wLastSecond = sTime.wSecond;
	
	;//从游戏开始到现在经过的时间(ms)
	if (sTime.wSecond != wLastSecond){
		wLastSecond = sTime.wSecond;
		m_fTime = (int)m_fTime + sTime.wMilliseconds / 1000.0f;
		m_fTime++;

	}
	else{
		m_fTime = (int)m_fTime + sTime.wMilliseconds / 1000.0f;
	}
	return m_fTime;
}
Shape<int> CGame::GetScreenResolution(){
	DEVMODE NewDevMode;
	EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &NewDevMode);
	static Shape<int> _v;
	_v = Shape<int>((int)NewDevMode.dmPelsWidth, (int)NewDevMode.dmPelsHeight);
	return _v;
}

Shape<int> CGame::GetConfigResolution(){
	return Shape<int>(m_gameConfig.SCREEN_WIDTH, m_gameConfig.SCREEN_HEIGHT);

}


bool CGame::SetScreenResolution(Shape<int> _v){

	//return ChangeDisplaySettings(&NewDevMode, CDS_FULLSCREEN);

	DEVMODE dmScreenSettings;
	memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
	dmScreenSettings.dmSize = sizeof(dmScreenSettings);
	dmScreenSettings.dmBitsPerPel = 32;
	dmScreenSettings.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
	dmScreenSettings.dmPelsWidth = _v.width;
	dmScreenSettings.dmPelsHeight = _v.height;
	bool bRetn = (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN)!=0);
	if (bRetn) m_vResolution = Shape<int>(_v);
	return bRetn;

}


bool CGame::SetScreenResolution(int _x, int _y){
	return SetScreenResolution(Shape<int>(_x, _y));
}

GAME_CONFIG CGame::GetConfig(){
	return m_gameConfig;

}



//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
///////		一帧开始时的事件									//////
///////		每次都会处理游戏逻辑，每经过一段时间会渲染一次		//////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
bool CGame::OnFrameStart(HWND hWnd, float fTime){


	//渲染函数
	Render(fTime);


	return true;
}


////////////////////////////////////
//
//  游戏状态处理和SAVE LOAD
//
////////////////////////////////////



void CGame::SetInstance(HINSTANCE instance){
	m_Instance = instance;
}                                     
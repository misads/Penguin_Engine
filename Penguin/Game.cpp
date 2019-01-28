#include "stdafx.h"
#include "Game.h"
#include "Ini.h"
#include "DSound.h"
#include "resource.h"


#pragma warning (disable: 4996) 
#pragma warning (disable: 4244) 
#pragma warning (disable: 4258) 

using namespace DSound;
using namespace Arith;


HANDLE RenderMutex;//渲染的互斥体


CGame::CGame(){
	
	m_fTime = 0;
	m_vResolution = GetScreenResolution();
	m_fUnitScale = fVector(1.0f, 1.0f);
	RenderMutex = CreateSemaphore(NULL, 1, 1, NULL);

	m_gameState = GAME_LOADING;

#ifdef _D2DRender_

	//m_bEmployHardwareRender = true;
#else
	//m_bEmployHardwareRender = false;
#endif

	memset(m_KeyState, 0, sizeof(m_KeyState));//按键信息清零


}

CGame::~CGame(){
	CloseHandle(RenderMutex);
}
//游戏初始化
bool CGame::InitGame(HWND hWnd){

	m_ResolutionSetting.nResolutionNow = 0;
	m_ResolutionSetting.vResolution.push_back(Vector(635,485));
	m_ResolutionSetting.vResolution.push_back(Vector(889, 679));
	m_ResolutionSetting.vResolution.push_back(Vector(1005, 768));
	m_ResolutionSetting.vResolution.push_back(Vector(1245, 951));
	m_ResolutionSetting.vResolution.push_back(Vector(1414, 1080));
	m_ResolutionSetting.vResolution.push_back(Vector(1700, 1331));
	
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


#define LoadImg(alias,path)  	m_mD2DImage.insert(pair<string, CD2DImage>(alias, d2dImageBuf));m_mD2DImage[alias].LoadImageFromFile(D2DC.pRenderTarget(), TEXT(path));
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
	
	m_mD2DGif["ice"].AddImage(m_mD2DImage["ice1"], Vector(800, 600));
	m_mD2DGif["ice"].AddImage(m_mD2DImage["ice2"], Vector(800, 600));
	m_mD2DGif["ice"].AddImage(m_mD2DImage["ice3"], Vector(800, 600));
	m_mD2DGif["ice"].AddImage(m_mD2DImage["ice4"], Vector(800, 600));
	m_mD2DGif["ice"].AddImage(m_mD2DImage["ice5"], Vector(800, 600));
	m_mD2DGif["ice"].AddImage(m_mD2DImage["ice6"], Vector(800, 600));
	m_mD2DGif["ice"].AddImage(m_mD2DImage["ice7"], Vector(800, 600));
	m_mD2DGif["ice"].AddImage(m_mD2DImage["ice8"], Vector(800, 600));
	m_mD2DGif["ice"].AddImage(m_mD2DImage["ice9"], Vector(800, 600));
	m_mD2DGif["ice"].AddImage(m_mD2DImage["ice10"], Vector(800, 600));
	m_mD2DGif["ice"].AddImage(m_mD2DImage["ice11"], Vector(800, 600));
	m_mD2DGif["ice"].AddImage(m_mD2DImage["ice12"], Vector(800, 600));
	m_mD2DGif["ice"].AddImage(m_mD2DImage["ice13"], Vector(800, 600));
	m_mD2DGif["ice"].SetFPS(50);
	
	


	///////////////
	//	加载声音
	/////////////

	Sound.SetSoundFilePath(L"./wav/");
	Sound.LoadSound("miss", L"Sound 1041.wav");

	////////////////
	//
	////////////////

	ReleaseSemaphore(RenderMutex, 1, NULL);
	nLoadPercent = 98;
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
	nLoadPercent = 100;
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


	m_fUnitScale = fVector(m_gameConfig.SCREEN_WIDTH/(MAX_WIDTH_UNIT *1.0f),
		m_gameConfig.SCREEN_HEIGHT/(MAX_HEIGHT_UNIT*1.0f));//更新比例

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
		Game.SetScreenResolution(m_gameConfig.SCREEN_WIDTH, m_gameConfig.SCREEN_HEIGHT);  //改分辨率
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
			MoveWindow(hWnd, 0, 0, m_ResolutionSetting.vResolution[m_ResolutionSetting.nResolutionNow].x,
				m_ResolutionSetting.vResolution[m_ResolutionSetting.nResolutionNow].y, true);
			break;
		}

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
Vector CGame::GetScreenResolution(){
	DEVMODE NewDevMode;
	EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &NewDevMode);
	static Vector _v;
	_v = Vector(Point((int)NewDevMode.dmPelsWidth, (int)NewDevMode.dmPelsHeight));
	return _v;
}

Vector CGame::GetConfigResolution(){
	return Vector(m_gameConfig.SCREEN_WIDTH,m_gameConfig.SCREEN_HEIGHT);

}


bool CGame::SetScreenResolution(Vector _v){

	//return ChangeDisplaySettings(&NewDevMode, CDS_FULLSCREEN);

	DEVMODE dmScreenSettings;
	memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
	dmScreenSettings.dmSize = sizeof(dmScreenSettings);
	dmScreenSettings.dmBitsPerPel = 32;
	dmScreenSettings.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
	dmScreenSettings.dmPelsWidth = _v.x;
	dmScreenSettings.dmPelsHeight = _v.y;
	bool bRetn = (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN)!=0);
	if(bRetn) m_vResolution = Vector(_v);
	return bRetn;

}


bool CGame::SetScreenResolution(int _x, int _y){
	return SetScreenResolution(Vector(Point(_x, _y)));
}

int CGame::GetConfigFps(){
	return m_gameConfig.FPS;

}

BOOL CGame::IsVerticalSync(){
	return m_gameConfig.VERTICAL_SYNC;

}

BOOL CGame::IsPerformancePrior(){
	return m_gameConfig.PERFORMANCE_PRIOR;
}

fVector	CGame::GetUnitScale(){
	return m_fUnitScale;
}


//        /@^     .@@^           .@@`     =@@`          =@^       =@@.         ].  @@^          =@^     
//         ,@@`   /@^            =@^      @@`           =@^  =@@@@@@@@@@@@@`  =@/  @@^     .]]. =@^     
//      .@@@@@@@@@@@@@@^      =@@@@@@@@^ =@@@@@@@@^  ,]]/@\]`=@^ .       O@. ,@@[[[@@/[[[[. @@. =@^     
//      .@@          =@^      =@@    =@^=@/     =@^     =@^     /@/` ,@@`     ..   @@^      @@. =@^     
//      .@@          =@^      =@@    =@/\^ ]    =@^     =@^   /@@`     =@@`  [[[[[[@@/[[[[` @@. =@^     
//      .@@@@@@@@@@@@@@^      =@@@@@@@@^  =@\   =@^    ./@@@^ ,`        .`         @@^      @@. =@^     
//            ,@\     .`      =@@    =@^   =@\  =@^  =@@\@^   [[[[[@@[[[[[    =@/[[@@/[[@@^ @@. =@^     
//     =@^ @@. ,@@`   \@@`    =@@    =@^    [.  =@.     =@^        @@.        =@^  @@^  @@^.@@. =@^     
//    ,@/  @@.  .`  .` .\@\.  =@@]]]]/@^        @@.     =@^        @@.        =@^  @@^,]@@.     =@^     
//   .@@.  @@].    ,/@/       =@@    =@^   ,]]]/@@    ,]/@^ .@@@@@@@@@@@@@@^  ,[`  @@^.[`    .]]@@^   
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

BYTE CGame::GetPlotState(string _plot){
	return GetPlotState(m_mPlotState[_plot]);
}

BYTE CGame::GetPlotState(int _where){

	return m_byPlotState[_where];
}

void CGame::SetPlotState(string _plot, BYTE _plotstate){
	SetPlotState(m_mPlotState[_plot], _plotstate);
}

void CGame::SetPlotState(int _where, BYTE _plotstate){
	m_byPlotState[_where] = _plotstate;

}

//                   ]]/`                          .]]].                                                                          
//   ./@@\.          .@@\              ,@@@\`       @@/                .@@@@@@@@@@@@@@@@@@@@@@^       ]@\  .@@^ .@@^  =@@^        
//     ,\@@@`@@@@@@@@@@@@@@@@@@@@`        [@@` .]]]]@@\]]]]]`                          .]@@@@[`        =@@`.@@^./@/   @@/         
//       .[  O@@              =@@.   .@\`      .[[[[@@/[[[@@^                      ,/@@@/`           ,]]]]]]@@\]]/]]`=@@`         
//           @@@              =@@.    ,\@@@\       =@@.  .@@^              /]    .@@/`   ..          =@@@@@@@@@@@@@@^@@@@@@@@@@@O 
//  ,@@@].     .@@@@@@@@@@@@@@O          .`,@^    /@@`   .@@`  ,          .\@@\. .@@^  ,@@@\            ,@@/@@\/\.  =@@.    @@^   
//    ,\@@@`                            ./@@@`  ]@@@.    ,@@.  @@@.   =@@.   ,@/ .@@^,@@@`  .@@^     ,/@@/ .@@^,@@\=@@@^   .@@^   
//       ,    .@@@@@@@@@@@@@@@@^     .]@@@/ ,]@@@/.      .@@@@@@@`    =@@.       .@@^       .@@^     ,@`  ,/[[`  `,@@\@\   ,@@.   
//            .@@^          =@@^      ,@`    .[` ,@@^                 =@@.   ./@`.@@^/@@`   .@@^    ..   .@@/      [`.@@`  =@/    
//     ./@\`  .@@@@@@@@@@@@@@@@^    .]]]]]]]]]]]]]@@\]]]]]]]]]]]].    =@@../@@@` .@@^ ,@@@` .@@^    .@@@@@@@@@@@@@@   =@@..@@^    
//     =@@`   .@@^          =@@^    .[[[[[[[[[[@@@@@@@@[[[[[[[[[[.    =@@.\@`    .@@^   ,@@/.@@^        =@@.   =@@.    \@\@@/     
//    ,@@^    .@@\]]]]]]]]]]/@@^            ./@@/.@@^\@@\.            =@@.    .@@@@@`       .@@^       =@@@@@\/@@`     .\@@/      
//   .@@@.    .[[[[[[[[[[[[[[[[`          ]@@@/. .@@^ .\@@@\`         =@@.     ,[           .@@^            ,@@@@@@\  ./@@@@\.    
//  ,@@@`                           .]/@@@@/`    .@@^    ,\@@@@@@/    =@@@@@@@@@@@@@@@@@@@@@@@@^        ,]@@@[    ,./@@@` .\@@@`  
//   .\^    O@@@@@@@@@@@@@@@@@@@@@   ,@/[        ,@@^         ,[`                           .@@^    .[@@@/`      ,@@@[      .\@@` 

#define XOFFSET 230
#define YOFFSET 35
#define LOADANILEFT_INIT 100
#define LOADANILEFT_ADD 3

bool CGame::Render(float fTime){
	
	/*
	static bool bPace = false;//因为一共就两帧 所以需要一个节拍
	int i = 0;
	char cBuff[30];
	WCHAR wBuff[30];
	set<int>::iterator it;
	CString cstring;
*/

	static float fLastTime = 0;
	static float fLoadShow = 0;
	
	if (fTime != 0){

			if (fTime - fLastTime < 1/((MAX_FPS)*1.0f)){
				return true;
			}
			else {
				fLastTime = fTime;
			}
	}


	
	switch (m_gameState){
	case GAME_MOTION:
		break;
		//渲染载入中
	case GAME_LOADING:
		break;
	case GAME_RUNNING:

		D2DC.BeginDraw();
		D2DC.ClearScreen(D2D1::ColorF::Wheat);
		//m_mD2DGif["ice"].Render(D2DC.pRenderTarget(), fTime, fPoint(0 , 0), fVector(400, 300));
		D2DC.DrawBmp(m_mD2DImage["ice1"], 0, 0, 400, 300, 1.0F,0,0,800,600);
		D2DC.DrawTextC(L"微软雅黑", 35, 1, 1, 0, 0, L"测试的文字", D2DRGB(0, 0, 0));
		//m_mD2DGif["ice"].Render(D2DC.pRenderTarget(), fTime, fPoint(0, 0), fVector(400, 300));

		D2DC.EndDraw();

		break;



	}

	





	


	return true;
}

void CGame::SetInstance(HINSTANCE instance){
	m_Instance = instance;
}
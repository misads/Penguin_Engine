#pragma once

#include <windef.h>
#include "utils/CD2DGif.h"
#include "Macros.h"
#include "Constants.h"
#include "Types.h"


extern CD2D D2DC;

class CGame{
public:

	CGame(void);
	~CGame(void);

	bool InitGame(HWND hWnd);//初始化游戏

	bool LoadConfig();//读取设置

	bool LoadGame(int n);

	bool SaveGame(int n);

	bool AlterResolution(); //适配分辨率

	//////////////////////////////////////////////////////////
	//		一帧开始时的事件
	//		每次都会处理游戏逻辑，每经过一段时间会渲染一次
	//////////////////////////////////////////////////////////
	bool OnFrameStart(HWND hWnd, float fTime);

	//////////////////////////////////////////////////////////
	//		处理鼠标、键盘等消息
	//////////////////////////////////////////////////////////
	LRESULT CALLBACK MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



	//TODO 在这里添加行为↓↓↓----------------------------------------------------
	//TODO 在这里添加行为↓↓↓----------------------------------------------------
	//TODO 在这里添加行为↓↓↓----------------------------------------------------











	//TODO 在这里添加行为↑↑↑----------------------------------------------------
	//TODO 在这里添加行为↑↑↑----------------------------------------------------





	////////////////////////////////////////////////////////
	//
	//
	//		渲染画面
	//
	//////////////////////////////////////////////////
	bool			Render(float fTime);

	float			fTime();

	Vector			GetScreenResolution();//获取当前屏幕分辨率
	Vector			GetConfigResolution();//获取设置的屏幕分辨率
	bool			SetScreenResolution(Vector _v);//设置屏幕分辨率
	bool			SetScreenResolution(int _x, int _y);
	GAME_CONFIG		GetConfig();
	BOOL 			IsVerticalSync();
	BOOL			IsPerformancePrior();
	//渲染的函数

	void			SetInstance(HINSTANCE instance);


protected:

	HINSTANCE		m_Instance;

	bool			LoadRes();//加载资源 音效 动画 数据等等
	bool			LoadMap();

	float			m_fTime;//从游戏开始到现在经过的时间
	float			m_fTimeLeft;//还剩下的游戏时间，可以为无穷

	Vector			m_vResolution;//分辨率
	
	GAME_CONFIG		m_gameConfig;//游戏设置

	GAME_STATE		m_gameState;//游戏状态
	
	GAME_MODE		m_gameMode;//游戏模式(PVE PVP)

	BYTE			m_PlotState[MAX_PLOT_STATE];//剧情的状态位 每次使用一个字节 用于存储游戏和读取游戏以及剧情的判断


	bool			m_KeyState[MAX_VIRTUAL_KEYS];//按键的状态 KEYDOWN或者KEYUP
	
	bool			m_bFullScreenMode;//全屏模式

	ResolutionSetting	m_ResolutionSetting;
	
	map<string, CD2DImage>		m_mD2DImage;

	map<string, CD2DGif>		m_mD2DGif;


};

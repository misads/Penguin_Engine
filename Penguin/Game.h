#include <windef.h>
#include "CommonHead.h"
#include "CD2DGif.h"
#include "Macros.h"
#include "Constants.h"
#include "Types.h"

#pragma once

extern CD2D D2DC;


#define GAME_MAX_KEYS 256
#define KEYDOWN true
#define KEYUP false

////////////////////////
// 如果定义了这个 就是大地图
//
//////////////////////
#define MAP_LARGE

//////////////////////
// 如果定义了这个 就是在调试中玩耍
// 游戏节奏加快
///////////////////
#define DEBUG_PLAY




//剧情状态 存储用
#define MAX_PLOT_STATE 200

//////////////////////////////
//
//	定义一些设置
//
/////////////////////////////
//英雄初始设定
#define INIT_HP 100
#define INIT_ATTACK 10
#define INIT_DEFENSE 10

//游戏状态

class CGame{
public:

	CGame(void);
	~CGame(void);

	friend class CBehaviour;
	bool InitGame(HWND hWnd);//初始化游戏

	bool InitHero();//初始化英雄

	bool LoadConfig();//读取设置

	bool LoadGame(int _which);

	bool SaveGame(int _which);

	bool AlterResolution(); //更改分辨率

	//一帧开始时的处理
	bool OnFrameStart(HWND hWnd, float fTime);
	//消息处理
	LRESULT CALLBACK MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



	//TODO 在这里添加行为↓↓↓----------------------------------------------------
	//TODO 在这里添加行为↓↓↓----------------------------------------------------
	//TODO 在这里添加行为↓↓↓----------------------------------------------------











	//TODO 在这里添加行为↑↑↑----------------------------------------------------
	//TODO 在这里添加行为↑↑↑----------------------------------------------------




	//////////////////////////////////
	//
	// 游戏状态处理
	//
	/////////////////////////////////

	BYTE GetPlotState(string _plot);
	BYTE GetPlotState(int _where);
	void SetPlotState(string _plot,BYTE _plotstate);
	void SetPlotState(int _where ,BYTE _plotstate);

	////////////////////////////////////////////////////////
	//
	//
	//
	//
	//////////////////////////////////////////////////
	
	//渲染画面
	bool			Render(float fTime);

	float			fTime();

	Vector			GetScreenResolution();//获取当前屏幕分辨率
	Vector			GetConfigResolution();//获取设置的屏幕分辨率
	bool			SetScreenResolution(Vector _v);//设置屏幕分辨率
	bool			SetScreenResolution(int _x, int _y);
	int				GetConfigFps();
	BOOL 			IsVerticalSync();
	BOOL			IsPerformancePrior();
	//渲染的函数
	fVector			GetUnitScale();//渲染前要乘以的比例
	void			DisableAttackEffect();//重置特效 防止意外播放
	//一些判断
	bool			CanWalkOn(char _block);
	bool			CanTalkTo(char _block);

	int			nLoadPercent;
	void		SetInstance(HINSTANCE instance);


protected:

	HINSTANCE		m_Instance;

	bool			LoadRes();//加载资源 音效 动画 数据等等
	bool			LoadMap();
	bool			LoadMonster();

	float			m_fTime;//从游戏开始到现在经过的时间
	float			m_fTimeLeft;//还剩下的游戏时间，可以为无穷

	Vector			m_vResolution;//分辨率
	fVector			m_fUnitScale;//渲染前要乘以的比例

	
	GAME_CONFIG		m_gameConfig;//游戏设置

	GAME_STATE		m_gameState;//游戏状态
	
	GAME_MODE		m_gameMode;//游戏模式 此时游戏状态m_gameState为GAME_RUNNING

	BYTE			m_byPlotState[MAX_PLOT_STATE];//剧情的状态位 每次使用一个字节 用于存储游戏和读取游戏以及剧情的判断

	map<string, int>	m_mPlotState;//给剧情状态位起个名字


	bool			m_KeyState[GAME_MAX_KEYS];//按键的状态 KEYDOWN或者KEYUP
	
	bool			m_bFullScreenMode;//全屏模式

	ResolutionSetting	m_ResolutionSetting;
	
	map<string, CD2DImage>		m_mD2DImage;

	map<string, CD2DGif>		m_mD2DGif;


};

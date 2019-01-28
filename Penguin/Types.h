#pragma once

struct GAME_CONFIG{
	INT		SCREEN_WIDTH;
	INT		SCREEN_HEIGHT;
	INT		FPS;
	BOOL	FULL_SCREEN;
	BOOL	HARDWARE_RENDER;
	BOOL	VERTICAL_SYNC;
	BOOL	PERFORMANCE_PRIOR;
};

enum GAME_STATE{
	GAME_MOTION = 1,	//片头动画
	GAME_LOADING,		//载入中
	GAME_MAIN_MENU,		//主菜单
	GAME_RUNNING,		//游戏正在运行
	GAME_TALK,			//对话
	GAME_BATTLE,		//战斗
	GAME_PAUSE,			//游戏暂停
	GAME_MENU,			//菜单
	GAME_WIN,			//游戏胜利
	GAME_OVER			//游戏结束
};

//游戏模式
enum GAME_MODE{
	GM_STORY = 1,		//故事模式
	GM_PVP,				//PVP
	GM_PVE,				//PVE
	GM_ONLINE			//在线
	//.....
};

struct ResolutionSetting{
	vector<Vector>	vResolution;
	int				nResolutionNow;
};
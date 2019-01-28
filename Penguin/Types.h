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
	GAME_MOTION = 1,	//Ƭͷ����
	GAME_LOADING,		//������
	GAME_MAIN_MENU,		//���˵�
	GAME_RUNNING,		//��Ϸ��������
	GAME_TALK,			//�Ի�
	GAME_BATTLE,		//ս��
	GAME_PAUSE,			//��Ϸ��ͣ
	GAME_MENU,			//�˵�
	GAME_WIN,			//��Ϸʤ��
	GAME_OVER			//��Ϸ����
};

//��Ϸģʽ
enum GAME_MODE{
	GM_STORY = 1,		//����ģʽ
	GM_PVP,				//PVP
	GM_PVE,				//PVE
	GM_ONLINE			//����
	//.....
};

struct ResolutionSetting{
	vector<Vector>	vResolution;
	int				nResolutionNow;
};
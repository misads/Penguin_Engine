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
// ������������ ���Ǵ��ͼ
//
//////////////////////
#define MAP_LARGE

//////////////////////
// ������������ �����ڵ�������ˣ
// ��Ϸ����ӿ�
///////////////////
#define DEBUG_PLAY




//����״̬ �洢��
#define MAX_PLOT_STATE 200

//////////////////////////////
//
//	����һЩ����
//
/////////////////////////////
//Ӣ�۳�ʼ�趨
#define INIT_HP 100
#define INIT_ATTACK 10
#define INIT_DEFENSE 10

//��Ϸ״̬

class CGame{
public:

	CGame(void);
	~CGame(void);

	friend class CBehaviour;
	bool InitGame(HWND hWnd);//��ʼ����Ϸ

	bool InitHero();//��ʼ��Ӣ��

	bool LoadConfig();//��ȡ����

	bool LoadGame(int _which);

	bool SaveGame(int _which);

	bool AlterResolution(); //���ķֱ���

	//һ֡��ʼʱ�Ĵ���
	bool OnFrameStart(HWND hWnd, float fTime);
	//��Ϣ����
	LRESULT CALLBACK MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



	//TODO �����������Ϊ������----------------------------------------------------
	//TODO �����������Ϊ������----------------------------------------------------
	//TODO �����������Ϊ������----------------------------------------------------











	//TODO �����������Ϊ������----------------------------------------------------
	//TODO �����������Ϊ������----------------------------------------------------




	//////////////////////////////////
	//
	// ��Ϸ״̬����
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
	
	//��Ⱦ����
	bool			Render(float fTime);

	float			fTime();

	Vector			GetScreenResolution();//��ȡ��ǰ��Ļ�ֱ���
	Vector			GetConfigResolution();//��ȡ���õ���Ļ�ֱ���
	bool			SetScreenResolution(Vector _v);//������Ļ�ֱ���
	bool			SetScreenResolution(int _x, int _y);
	int				GetConfigFps();
	BOOL 			IsVerticalSync();
	BOOL			IsPerformancePrior();
	//��Ⱦ�ĺ���
	fVector			GetUnitScale();//��ȾǰҪ���Եı���
	void			DisableAttackEffect();//������Ч ��ֹ���ⲥ��
	//һЩ�ж�
	bool			CanWalkOn(char _block);
	bool			CanTalkTo(char _block);

	int			nLoadPercent;
	void		SetInstance(HINSTANCE instance);


protected:

	HINSTANCE		m_Instance;

	bool			LoadRes();//������Դ ��Ч ���� ���ݵȵ�
	bool			LoadMap();
	bool			LoadMonster();

	float			m_fTime;//����Ϸ��ʼ�����ھ�����ʱ��
	float			m_fTimeLeft;//��ʣ�µ���Ϸʱ�䣬����Ϊ����

	Vector			m_vResolution;//�ֱ���
	fVector			m_fUnitScale;//��ȾǰҪ���Եı���

	
	GAME_CONFIG		m_gameConfig;//��Ϸ����

	GAME_STATE		m_gameState;//��Ϸ״̬
	
	GAME_MODE		m_gameMode;//��Ϸģʽ ��ʱ��Ϸ״̬m_gameStateΪGAME_RUNNING

	BYTE			m_byPlotState[MAX_PLOT_STATE];//�����״̬λ ÿ��ʹ��һ���ֽ� ���ڴ洢��Ϸ�Ͷ�ȡ��Ϸ�Լ�������ж�

	map<string, int>	m_mPlotState;//������״̬λ�������


	bool			m_KeyState[GAME_MAX_KEYS];//������״̬ KEYDOWN����KEYUP
	
	bool			m_bFullScreenMode;//ȫ��ģʽ

	ResolutionSetting	m_ResolutionSetting;
	
	map<string, CD2DImage>		m_mD2DImage;

	map<string, CD2DGif>		m_mD2DGif;


};

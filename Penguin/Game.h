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

	bool InitGame(HWND hWnd);//��ʼ����Ϸ

	bool LoadConfig();//��ȡ����

	bool LoadGame(int n);

	bool SaveGame(int n);

	bool AlterResolution(); //����ֱ���

	//////////////////////////////////////////////////////////
	//		һ֡��ʼʱ���¼�
	//		ÿ�ζ��ᴦ����Ϸ�߼���ÿ����һ��ʱ�����Ⱦһ��
	//////////////////////////////////////////////////////////
	bool OnFrameStart(HWND hWnd, float fTime);

	//////////////////////////////////////////////////////////
	//		������ꡢ���̵���Ϣ
	//////////////////////////////////////////////////////////
	LRESULT CALLBACK MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



	//TODO �����������Ϊ������----------------------------------------------------
	//TODO �����������Ϊ������----------------------------------------------------
	//TODO �����������Ϊ������----------------------------------------------------











	//TODO �����������Ϊ������----------------------------------------------------
	//TODO �����������Ϊ������----------------------------------------------------





	////////////////////////////////////////////////////////
	//
	//
	//		��Ⱦ����
	//
	//////////////////////////////////////////////////
	bool			Render(float fTime);

	float			fTime();

	Vector			GetScreenResolution();//��ȡ��ǰ��Ļ�ֱ���
	Vector			GetConfigResolution();//��ȡ���õ���Ļ�ֱ���
	bool			SetScreenResolution(Vector _v);//������Ļ�ֱ���
	bool			SetScreenResolution(int _x, int _y);
	GAME_CONFIG		GetConfig();
	BOOL 			IsVerticalSync();
	BOOL			IsPerformancePrior();
	//��Ⱦ�ĺ���

	void			SetInstance(HINSTANCE instance);


protected:

	HINSTANCE		m_Instance;

	bool			LoadRes();//������Դ ��Ч ���� ���ݵȵ�
	bool			LoadMap();

	float			m_fTime;//����Ϸ��ʼ�����ھ�����ʱ��
	float			m_fTimeLeft;//��ʣ�µ���Ϸʱ�䣬����Ϊ����

	Vector			m_vResolution;//�ֱ���
	
	GAME_CONFIG		m_gameConfig;//��Ϸ����

	GAME_STATE		m_gameState;//��Ϸ״̬
	
	GAME_MODE		m_gameMode;//��Ϸģʽ(PVE PVP)

	BYTE			m_PlotState[MAX_PLOT_STATE];//�����״̬λ ÿ��ʹ��һ���ֽ� ���ڴ洢��Ϸ�Ͷ�ȡ��Ϸ�Լ�������ж�


	bool			m_KeyState[MAX_VIRTUAL_KEYS];//������״̬ KEYDOWN����KEYUP
	
	bool			m_bFullScreenMode;//ȫ��ģʽ

	ResolutionSetting	m_ResolutionSetting;
	
	map<string, CD2DImage>		m_mD2DImage;

	map<string, CD2DGif>		m_mD2DGif;


};

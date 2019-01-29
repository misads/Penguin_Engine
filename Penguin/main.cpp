// main.cpp : ���������ļ�����


#include "stdafx.h"
#include "resource.h"
#include "utils/Ini.h"

#include "utils/CD2D.h"
#include "utils/CD2DAnimation.h"
#include "utils/DSound.h"

#define MAX_LOADSTRING 100

#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dwrite.lib")


#include "utils/utils.h"
#include "Game.h"
#include "window.h"
#include "Types.h"

#define MAX_LOADSTRING 100

using namespace DSound;

// �˴���ģ���ȫ�ֱ���: 
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������



//ȫ�ֱ���
//CIni	Ini;
CD2D	D2DC;
//CApp	App;
CGame	Game;


HWND MainWindow;


// �˴���ģ���а����ĺ�����ǰ������: 
void InitFont();
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI GameInitThread(LPVOID IpParameter);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO:  �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PENGUIN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PENGUIN));

	// ��Ϸ��ѭ����PeekMessage��: 
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT){
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else{
			Game.OnFrameStart(MainWindow, Game.fTime());
			if (!Game.GetConfig().PERFORMANCE_PRIOR)
				Sleep(1);//��������������� �����ܵؽ�ʡCPUʱ��
		}
		
	}

	return (int) msg.wParam;
}

void InitFont(){

}


//
//  ����:  MyRegisterClass()
//
//  Ŀ��:  ע�ᴰ���ࡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PENGUIN));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_PENGUIN);		//�˵���
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����:  InitInstance(HINSTANCE, int)
//
//   Ŀ��:  ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   

	hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

	Game.SetInstance(hInstance);

	InitFont();

	_TRY(Game.LoadConfig(),"�޷�������Ϸ���ã���config.ini�ļ�",true);
   
	_TRY(Game.AlterResolution(), "�޷�ȫ����Ϸ����ʹ�ô���ģʽ", true);

	MainWindow = CreateWindow(szWindowClass, L"Penguin Demo", WS_OVERLAPPEDWINDOW,
	   0, 0, Game.GetConfigResolution().x, Game.GetConfigResolution().y, NULL, NULL, hInst, NULL);


   if (!MainWindow)
   {
	   _ERROR(L"��������ʧ��", true);
      return FALSE;
   }


	D2DC.CreateD2DResource(MainWindow);

	Sound.SetupLevel(MainWindow);

	ShowWindow(MainWindow, nCmdShow);
	UpdateWindow(MainWindow);




/////////////////////////////////
//
//      ��Ϸ��ʼ���߳�
//
/////////////////////////////////

   HANDLE gameInitThread = CreateThread(NULL, 0, GameInitThread, NULL, 0, NULL);

   if (!Game.InitGame(MainWindow)) _ERROR(TEXT("��Ϸ��ʼ��ʧ��"), true);

   return TRUE;
}

//
//  ����:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:

		break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��: 
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		break;
	case WM_QUIT:

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:

		return Game.MsgProc(hWnd,message, wParam,lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


DWORD WINAPI GameInitThread(LPVOID IpParameter){


	 _TRY(Game.InitGame(MainWindow), "��Ϸ��ʼ��ʧ��", true);

	return 0;


}

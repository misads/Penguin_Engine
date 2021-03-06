// main.cpp : 程序从这个文件启动


#include "stdafx.h"
#include "resource.h"
#include "utils/Ini.h"

#include "utils/CD2D.h"
//#include "utils/CD2DAnimation.h"
#include "utils/DSound.h"

#define MAX_LOADSTRING 100

#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dwrite.lib")


#include "utils/utils.h"
#include "Game.h"
#include "Types.h"

#define MAX_LOADSTRING 100

using namespace DSound;

// 此代码模块的全局变量: 
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名



//全局变量
//CIni	Ini;
CD2D	D2DC;
//CApp	App;
CGame	Game;


HWND MainWindow;


// 此代码模块中包含的函数的前向声明: 
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

 	// TODO:  在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_PENGUIN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PENGUIN));

	// 游戏主循环（PeekMessage）: 
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT){
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else{
			Game.OnFrameStart(MainWindow, Game.fTime());
			if (!Game.GetConfig().PERFORMANCE_PRIOR)
				Sleep(1);//如果不是性能优先 尽可能地节省CPU时间
		}
		
	}

	return (int) msg.wParam;
}

void InitFont(){

}


//
//  函数:  MyRegisterClass()
//
//  目的:  注册窗口类。
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
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_PENGUIN);		//菜单栏
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数:  InitInstance(HINSTANCE, int)
//
//   目的:  保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   

	hInst = hInstance; // 将实例句柄存储在全局变量中

	Game.SetInstance(hInstance);

	InitFont();

	_TRY(Game.LoadConfig(),"无法加载游戏设置，请config.ini文件",true);
   
	_TRY(Game.AlterResolution(), "无法全屏游戏，请使用窗口模式", true);

	MainWindow = CreateWindow(szWindowClass, L"Penguin Demo", WS_OVERLAPPEDWINDOW,
	   0, 0, Game.GetConfigResolution().width, Game.GetConfigResolution().height, NULL, NULL, hInst, NULL);


   if (!MainWindow)
   {
	   _ERROR(L"创建窗口失败", true);
      return FALSE;
   }


	D2DC.CreateD2DResource(MainWindow);

	Sound.SetupLevel(MainWindow);

	ShowWindow(MainWindow, nCmdShow);
	UpdateWindow(MainWindow);




/////////////////////////////////
//
//      游戏初始化线程
//
/////////////////////////////////

   HANDLE gameInitThread = CreateThread(NULL, 0, GameInitThread, NULL, 0, NULL);

   //if (!Game.InitGame(MainWindow)) _ERROR(TEXT("游戏初始化失败"), true);

   return TRUE;
}

//
//  函数:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
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
		// 分析菜单选择: 
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

// “关于”框的消息处理程序。
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


	 _TRY(Game.InitGame(MainWindow), "游戏初始化失败", true);

	return 0;


}

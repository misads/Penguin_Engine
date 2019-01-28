#include "stdafx.h"
#include "App.h"
#include "Penguin.h"

#ifndef _SERVER_




void _ERROR(LPTSTR lpText, bool bFatal){
	MessageBox(0, lpText, L"ERROR", 0);
	if (bFatal)exit(1);
}

void INFO(LPTSTR lpText, bool bFatal){
	MessageBox(0, lpText, L"INFO", 0);
	if (bFatal)exit(1);
}

CApp::CApp(){
	_tcscpy_s(Path, Ini.Path);
}

CApp::~CApp(){}



WCHAR CApp::Path[MAX_PATH] = { TEXT("\0") };

#endif
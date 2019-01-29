#include "stdafx.h"
#include "Debug.h"

#ifndef MAX_STRING_LENGTH
	#define MAX_STRING_LENGTH 260
#endif

void _DEBUGMSG(LPCTSTR lpText){
	MessageBox(0, lpText, L"DEBUG", 0);
}

void _DEBUGMSG(CString strText){
	//WCHAR wTemp[MAX_STRING_LENGTH] = { L"\0" };
	_DEBUGMSG((LPCTSTR)strText);
}

void _DEBUGMSG(int nText){
	WCHAR wText[MAX_STRING_LENGTH];
	_itot_s(nText, wText, 10);
	_DEBUGMSG(wText);

}

void _DEBUGMSG(float fText){
	WCHAR wText[MAX_STRING_LENGTH];
	_stprintf_s(wText, L"%f", fText);
	_DEBUGMSG(wText);
	
}

void _DEBUGMSG(LPSTR lpText){
	MessageBoxA(0, lpText, "DEBUG", 0);

}

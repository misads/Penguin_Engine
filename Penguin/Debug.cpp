#include "stdafx.h"
#include "Debug.h"

#ifndef _SERVER_

void DEBUG(LPCTSTR lpText){
	MessageBox(0, lpText, L"DEBUG", 0);
}

void DEBUG(CString strText){
	//WCHAR wTemp[MAX_STRING_LENGTH] = { L"\0" };
	DEBUG((LPCTSTR)strText);
}

void DEBUG(int nText){
	WCHAR wText[MAX_STRING_LENGTH];
	_itot_s(nText, wText, 10);
	DEBUG(wText);

}

void DEBUG(float fText){
	WCHAR wText[MAX_STRING_LENGTH];
	_stprintf_s(wText, L"%f", fText);
	DEBUG(wText);
	
}

void DEBUG(LPSTR lpText){
	MessageBoxA(0, lpText, "DEBUG", 0);

}

#endif

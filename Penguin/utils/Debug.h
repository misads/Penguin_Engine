#include <windows.h>
#include <atlstr.h>

#pragma once
//���DEBUG��Ϣ
void _DEBUGMSG(LPCTSTR lpText);

void _DEBUGMSG(CString strText);

void _DEBUGMSG(int nText);

void _DEBUGMSG(float fText);

void _DEBUGMSG(LPSTR lpText);



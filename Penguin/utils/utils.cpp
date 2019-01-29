#include "stdafx.h"
#include "utils.h"

void _ERROR(LPTSTR lpText, bool bFatal){
	MessageBox(0, lpText, L"ERROR", 0);
	if (bFatal)exit(1);
}

void _INFO(LPTSTR lpText, bool bFatal){
	MessageBox(0, lpText, L"INFO", 0);
	if (bFatal)exit(1);
}
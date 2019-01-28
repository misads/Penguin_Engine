#ifndef _SERVER_

#include <windows.h>
#include "CommonHead.h"
#include <atlstr.h>

#ifndef _H_DEBUG_H
#define _H_DEBUG_H
#pragma once
// ‰≥ˆDEBUG–≈œ¢
void DEBUG(LPCTSTR lpText);

void DEBUG(CString strText);

void DEBUG(int nText);

void DEBUG(float fText);

void DEBUG(LPSTR lpText);

#endif

#endif

#ifndef _SERVER_

#ifndef _H_APP_H
#define _H_APP_H
#pragma once

#define _TRY(operation,errorstring,fatal) if(!operation)_ERROR(TEXT(errorstring),(fatal));

void _ERROR(LPTSTR lpText,bool bFatal=false);

void INFO(LPTSTR lpText, bool bFatal = false);

class CApp{
public:
	CApp();
	~CApp();

	static WCHAR Path[MAX_PATH];
	

protected:
	WCHAR		m_SoundPath[MAX_PATH];
};

#endif
#endif
///////////////////////////
//								  //	
//		Sound 简易声音处理		  //
//		版本号:20180113			  //
//		CopyRight XY.2018			  //
//								  //
///////////////////////////


#include <map>
#include<windows.h>
#include <mmsystem.h>
#include <atlstr.h>

#pragma comment(lib,"winmm.lib")

#ifndef _H_SOUND_H
#define _H_SOUND_H
#pragma once


#define PLAY_INTERVAL 0.05f
#define MAX_SOUND_BUFF 100

class CSound{


public:
	CSound();
	~CSound();

	bool Play(CString _filename, float fTime);

	bool PlayAlias(string _alias, float fTime);

	void AddSound(string _alias, CString _filename);

	bool SetSoundFilePath(CString _path);
protected:
	int					GetAFreeSoundBuff();

	void					NextSoundBuff();

	map<CString, float>	m_mSoundTime;

	map<string, CString> m_mSoundAlias;

	CString				m_csSoundFilePath;

	int					m_nSoundBuffNow;
};





#endif
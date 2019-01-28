///////////////////////////
//								  //	
//		DirectSound wav混音处理	  //
//		版本号:20180214			  //
//		CopyRight XY.2018			  //
//								  //
///////////////////////////


#include <map>
#include <vector>
#include <windows.h>
#include <dsound.h>
#include <mmsystem.h>
#include <atlstr.h>
#include <string>

#pragma comment(lib,"winmm.lib")

#ifndef _H_SOUND_H
#define _H_SOUND_H
#pragma once

#define SAFE_RELEASE(P) if(P){P->Release() ; P = NULL ;}
#define SAFE_FREE(P) if(P){free(P); P = NULL ;}

#ifndef MAX_STRING_LENGTH
	#define MAX_STRING_LENGTH 260
#endif


#define MAX_SOUND_BUFF 40		//最大播放缓冲数

#define PLAY_INTERVAL 0.05f		//播放间隔 每秒最多播放的同一个wav为1/PLAY_INTERVAL 防止卡顿






namespace DSound{
	enum SOUND_STATE{
		SOUND_NULL = 0,
		SOUND_LOADED,     
		SOUND_PLAYING, //LOOP or ALON
		//SOUND_PLAYING_ALON, 
		SOUND_STOPPED,   
	};
	struct SOUND_LOADBUFF{//内存缓存 没有上限
		(UCHAR*)		Sound_Buffer = NULL;
		WAVEFORMATEX wfmtx;              //wav结构..
		DWORD		snd_size=0;


	};

	struct SOUND_PLAYBUFF{//声卡缓存 有上限
		LPDIRECTSOUNDBUFFER   Sound_Buffer = NULL;
		UINT					VEC_XS;
	};

	template <typename T>
	void _asm0(T& ddstruct);



}


class CDSound{


public:

	LPDIRECTSOUND         lpds;            //DirectSound音频指针..
	DSBUFFERDESC          dsbd;           //音频描述结构..
	//WAVEFORMATEX          wfmtx;              //wav结构..



	CDSound();
	~CDSound();

	void  SetupLevel(HWND);

	bool Play(CString _filename, float fTime);

	bool PlayAlias(string _alias, float fTime);

	void LoadSound(string _alias, CString _filename);

	void LoadSound(CString _filename);

	bool SetSoundFilePath(CString _path);

private:
	static MMCKINFO    parent, child;
	static HMMIO              hwav;
	static DWORD      audio_length_1,
		audio_length_2;

	static UCHAR       *snd_buffer,
		*audio_ptr_1,
		*audio_ptr_2;

	std::vector<LPDIRECTSOUNDBUFFER>      msVEC;

	void   Release();



protected:
	int										GetAFreeSoundBuff();

	DSound::SOUND_PLAYBUFF					m_playBuff[MAX_SOUND_BUFF+1];//播放时的环形缓存 0下标不用 只用1-MAX_SOUND_BUFF


	void										NextSoundBuff();

	std::map<CString, float>					m_mSoundTime;

	std::map<string, CString>					m_mSoundAlias;

	std::map<CString, DSound::SOUND_LOADBUFF>	m_mLoadBuff;//内存缓存 载入声音文件时使用


	CString									m_csSoundFilePath;

	int										m_nSoundBuffNow;
};


namespace DSound{
	extern CDSound Sound;
}


#endif
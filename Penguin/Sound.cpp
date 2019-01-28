#include "stdafx.h"

#include"Sound.h"


CSound::CSound(){
	m_nSoundBuffNow = 1;
}

CSound::~CSound(){

}

bool CSound::Play(CString _filename, float fTime){
	CString csBuff;
	//时间间隔太短
	if (fTime - m_mSoundTime[_filename] < PLAY_INTERVAL){
		return false;
	}
	//时间间隔允许播放
	m_mSoundTime[_filename] = fTime;
	int nBuff = GetAFreeSoundBuff();
	csBuff.Format(L"open \"./sounds/%s\" alias %d", _filename, nBuff);

	//OutputDebugString(csBuff);

	mciSendString(csBuff, 0, 0, NULL);

	csBuff.Format(L"play %d", nBuff);

	mciSendString(csBuff, NULL, 0, 0);
	
	return true;
}

bool CSound::PlayAlias(string _alias, float fTime){

	return Play(m_mSoundAlias[_alias], fTime);

}

void CSound::AddSound(string _alias, CString _filename){
	m_mSoundAlias[_alias] = _filename;
}

int CSound::GetAFreeSoundBuff(){
	CString csSendBuff;
	WCHAR wRecvBuff[MAX_STRING_LENGTH];
	int nNowSoundBuff = m_nSoundBuffNow;
	NextSoundBuff();

	csSendBuff.Format(L"status %d mode", m_nSoundBuffNow);
	mciSendString(csSendBuff, wRecvBuff, MAX_STRING_LENGTH, 0);

	while (m_nSoundBuffNow != nNowSoundBuff){
		if (!_tcscmp(wRecvBuff, L"stopped")){
			csSendBuff.Format(L"close %d ", m_nSoundBuffNow);
			mciSendString(csSendBuff, 0, 0, 0);
			return m_nSoundBuffNow;
		}
		else if (!_tcscmp(wRecvBuff, L"playing")){
			NextSoundBuff();
		}
		else{
			return m_nSoundBuffNow;
		}
	}
	

	return -1;

}

void	 CSound::NextSoundBuff(){
	m_nSoundBuffNow++;
	if (m_nSoundBuffNow > MAX_SEND_BUFF)m_nSoundBuffNow = 1;

}
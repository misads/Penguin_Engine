
#include"stdafx.h"
#include"DSound.h"

//using namespace std;

#pragma comment(lib,"dsound.lib")
#pragma comment(lib,"winmm.lib")


HMMIO        CDSound::hwav;
MMCKINFO  CDSound::parent;
MMCKINFO  CDSound::child;
DWORD      CDSound::audio_length_1;
DWORD      CDSound::audio_length_2;

UCHAR*     CDSound::snd_buffer = NULL;
UCHAR*      CDSound::audio_ptr_1 = NULL;
UCHAR*      CDSound::audio_ptr_2 = NULL;




namespace DSound{
	CDSound Sound;

	template <typename T>
	void _asm0(T& ddstruct)
	{
		T* _PTR_ = &ddstruct;
		register UINT num = sizeof(ddstruct) / 4;

		__asm PUSH ECX           __asm PUSH EDI
		__asm PUSH EAX           __asm CLD
		__asm MOV  EAX, 0         __asm MOV ECX, num
		__asm MOV  EDI, _PTR_     __asm REP STOSD
		__asm POP  EAX           __asm POP EDI   __asm POP ECX

		ddstruct.dwSize = sizeof(ddstruct);
	}
}
CDSound::CDSound(){
	m_nSoundBuffNow = 1;
	m_csSoundFilePath = L"";

	lpds = NULL;

	DSound::_asm0(this->dsbd);

	if (DirectSoundCreate(NULL, &lpds, NULL))
		MessageBox(NULL, L"DirectSoundCreate Failed", L"DirectSound", MB_ICONERROR);

	dsbd.dwFlags = DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE | DSBCAPS_GLOBALFOCUS;
	//dsbd.lpwfxFormat = &wfmtx;



		

}

CDSound::~CDSound(){

	Release();

	SAFE_RELEASE(lpds);
}

void  CDSound::SetupLevel(HWND hWnd){
	if (lpds->SetCooperativeLevel(hWnd, DSSCL_NORMAL))
		MessageBox(NULL, L"SetCooperativeLevel Error", L"DirectSound", MB_ICONERROR);
}
bool CDSound::Play(CString _filename, float fTime){
	CString csBuff;
	//时间间隔太短就不播放
	if (fTime - m_mSoundTime[_filename] < PLAY_INTERVAL){
		return false;
	}
	//时间间隔允许播放
	m_mSoundTime[_filename] = fTime;

	int afreebuf = GetAFreeSoundBuff();

	int size = m_mLoadBuff[_filename].snd_size;//wav声音数据多少字节

	
	SAFE_RELEASE(m_playBuff[afreebuf].Sound_Buffer);

	dsbd.lpwfxFormat = &(m_mLoadBuff[_filename].wfmtx);
	dsbd.dwBufferBytes = m_mLoadBuff[_filename].snd_size;

	lpds->CreateSoundBuffer(&dsbd, &(m_playBuff[afreebuf].Sound_Buffer), NULL);


	m_playBuff[afreebuf].Sound_Buffer->Lock(0, size, (void **)&audio_ptr_1, &audio_length_1, (void**)&audio_ptr_2, &audio_length_2, DSBLOCK_FROMWRITECURSOR);
	
	memcpy(audio_ptr_1, m_mLoadBuff[_filename].Sound_Buffer, audio_length_1);
	memcpy(audio_ptr_2, (m_mLoadBuff[_filename].Sound_Buffer + audio_length_1), audio_length_2);//将内存缓存填充到DirectSound环形缓存中

	m_playBuff[afreebuf].Sound_Buffer->Unlock(audio_ptr_1, audio_length_1, audio_ptr_2, audio_length_2);


	m_playBuff[afreebuf].Sound_Buffer->Play(0, 0, 0);//播放仅一次不循环


	return true;
}

bool CDSound::PlayAlias(string _alias, float fTime){


	return Play(m_mSoundAlias[_alias], fTime);

}

void CDSound::LoadSound(string _alias, CString _filename){
	
	LoadSound(_filename);
	m_mSoundAlias[_alias] = _filename;



}

void CDSound::LoadSound(CString _filename){
	DSound::SOUND_LOADBUFF snd_buff;
	m_mLoadBuff.insert(pair<CString, DSound::SOUND_LOADBUFF>(_filename, snd_buff));


	child = parent;

	WCHAR filename[MAX_PATH];

	_tcscpy_s(filename, m_csSoundFilePath);
	_tcscat_s(filename, _filename);


	hwav = mmioOpen(filename, NULL, MMIO_READ | MMIO_ALLOCBUF);


	parent.fccType = mmioFOURCC('W', 'A', 'V', 'E');

	mmioDescend(hwav, &parent, NULL, MMIO_FINDRIFF);


	child.ckid = mmioFOURCC('f', 'm', 't', ' ');

	mmioDescend(hwav, &child, &parent, 0);

	mmioRead(hwav, (char*)&(m_mLoadBuff[_filename].wfmtx), sizeof(WAVEFORMATEX));


	mmioAscend(hwav, &child, 0);

	child.ckid = mmioFOURCC('d', 'a', 't', 'a');

	mmioDescend(hwav, &child, &parent, MMIO_FINDCHUNK);

	snd_buffer = (UCHAR*)malloc(child.cksize);

	mmioRead(hwav, (char*)snd_buffer, child.cksize);
	mmioClose(hwav, 0);

	//dsbd.dwBufferBytes = child.cksize;


	m_mLoadBuff[_filename].Sound_Buffer = (UCHAR*)malloc(child.cksize);
	memcpy(m_mLoadBuff[_filename].Sound_Buffer, snd_buffer, child.cksize);
	m_mLoadBuff[_filename].snd_size = child.cksize;

}

bool CDSound::SetSoundFilePath(CString _path){
	m_csSoundFilePath = _path;
	return true;

}
int CDSound::GetAFreeSoundBuff(){


	int nNowSoundBuff = m_nSoundBuffNow;
	NextSoundBuff();

	if (m_playBuff[m_nSoundBuffNow].Sound_Buffer == NULL)return m_nSoundBuffNow;
	
	DWORD dwState;

	m_playBuff[m_nSoundBuffNow].Sound_Buffer->GetStatus(&dwState);

	while (m_nSoundBuffNow != nNowSoundBuff){
		if (dwState == 1){//正在播放
			NextSoundBuff();
		}
		else{
			return m_nSoundBuffNow;
		}

	}


	return -1;

}

void	 CDSound::NextSoundBuff(){
	m_nSoundBuffNow++;
	if (m_nSoundBuffNow > MAX_SOUND_BUFF)m_nSoundBuffNow = 1;

}


void CDSound::Release(){

	for (int i = 1; i <= MAX_SOUND_BUFF; i++){
		SAFE_RELEASE(m_playBuff[i].Sound_Buffer);
		
			
	}

	map<CString, DSound::SOUND_LOADBUFF>::iterator it;

	it = m_mLoadBuff.begin();

	while (it != m_mLoadBuff.end())
	{
		SAFE_FREE(it->second.Sound_Buffer);
		it++;
	}

}

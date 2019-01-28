#include "stdafx.h"
#include"Ini.h"

#pragma warning (disable: 4996) 

CIni::CIni(){
	//WCHAR Path[MAX_PATH] = {TEXT("\0")};

	//GetCurrentDirectory(MAX_PATH, Path);
	GetModuleFileName(NULL, Path, MAX_PATH);
	

	//_tcscpy_s(CIni::Path, Path);
	

}

CIni::~CIni(){}

WCHAR CIni::Path[MAX_PATH] = { TEXT("\0") };

LPTSTR CIni::ReadString(
	LPCTSTR lpAppName,
	LPCTSTR lpKeyName,
	LPCTSTR lpDefaut,
	LPCTSTR lpFileName){

	static WCHAR lpReturnedString[MAX_STRING_LENGTH];

	memset(lpReturnedString, 0, sizeof(lpReturnedString));
	GetPrivateProfileString(lpAppName, lpKeyName, lpDefaut, lpReturnedString, MAX_STRING_LENGTH, lpFileName);
	
	return lpReturnedString;
}

LPSTR CIni::ReadStringA(
	LPCSTR lpAppName,
	LPCSTR lpKeyName,
	LPCSTR lpDefaut,
	LPCSTR lpFileName){

	static char lpReturnedString[MAX_STRING_LENGTH];

	GetPrivateProfileStringA(lpAppName, lpKeyName, lpDefaut, lpReturnedString, MAX_STRING_LENGTH, lpFileName);
	return lpReturnedString;
}


UINT CIni::ReadInt(
	LPCTSTR lpAppName, // 指向包含 Section 名称的字符串地址
	LPCTSTR lpKeyName, // 指向包含 Key 名称的字符串地址
	INT nDefault, // 如果 Key 值没有找到，则返回缺省的值是多少
	LPCTSTR lpFileName){

	return GetPrivateProfileInt(lpAppName, lpKeyName, nDefault, lpFileName);
}

BOOL CIni::WriteString(
	LPCTSTR lpAppName,
	LPCTSTR lpKeyName,
	LPCTSTR  lpString,
	LPCTSTR  lpFileName){
	return WritePrivateProfileString(lpAppName,lpKeyName,lpString,lpFileName);
}

BOOL CIni::WriteInt(
	LPCTSTR lpAppName,
	LPCTSTR lpKeyName,
	INT  nValue,
	LPCTSTR  lpFileName){
	
	WCHAR wValue[20];
	_itot_s(nValue, wValue, 10);
	return WritePrivateProfileString(lpAppName, lpKeyName, wValue, lpFileName);
}


bool CIni::isExist(LPCTSTR lpFileName){

	if (!_tfopen(lpFileName, TEXT("r")))
		return false;
	else{
		fcloseall();
		return true;
	}

}

bool CIni::ReadBinary(LPCTSTR lpFileName, LPSTR lpBuffer, int _size, int _count, int _offset){
	FILE *fp;

	fp = _tfopen(lpFileName, L"rb+");
	if (_offset) fseek(fp, _offset, SEEK_CUR);
	fread(lpBuffer, _size, _count, fp);

	fclose(fp);

	return true;
}

bool CIni::WriteBinary(LPCTSTR lpFileName, LPSTR lpBuffer, int _size, int _count){

	FILE *fp;
	fp = _tfopen(lpFileName, L"wb+");
	fwrite(lpBuffer, _size, _count, fp);

	fclose(fp);
	return true;
}
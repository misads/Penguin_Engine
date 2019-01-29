///////////////////////////
//								  //	
//		Ini �����ļ�����			  //
//		�汾��:20180201			  //
//		CopyRight XY.2018			  //
//								  //
///////////////////////////

#include<windows.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#ifndef _H_FILE_H
#define _H_FILE_H
#pragma once




class CIni{
public:
	//���캯�����ʼ��Ӧ�ó����·��Path
	CIni(void);
	~CIni(void);


	static WCHAR Path[MAX_PATH];
	//����CIni::ReadString(L"config", L"title", L"default", L"./main.ini"), L"DEBUG", 0)
	static LPTSTR ReadString(
		LPCTSTR lpAppName,
		LPCTSTR lpKeyName,
		LPCTSTR lpDefaut,
		LPCTSTR lpFileName);
	//����CIni::ReadStringA("config", "title", "default", "./main.ini"), "DEBUG", 0)
	LPSTR CIni::ReadStringA(
		LPCSTR lpAppName,
		LPCSTR lpKeyName,
		LPCSTR lpDefaut,
		LPCSTR lpFileName);
	//����CIni::ReadInt(L"config", L"title", 123, L"./main.ini"), L"DEBUG", 0)
	static UINT ReadInt(
		LPCTSTR lpAppName, // ָ����� Section ���Ƶ��ַ�����ַ
		LPCTSTR lpKeyName, // ָ����� Key ���Ƶ��ַ�����ַ
		INT nDefault, // ��� Key ֵû���ҵ����򷵻�ȱʡ��ֵ�Ƕ���
		LPCTSTR lpFileName);
	//����CIni::WriteIni(L"config", L"title", L"ini_test2", L"./main.ini");
	static BOOL WriteString(
		LPCTSTR lpAppName,
		LPCTSTR lpKeyName,
		LPCTSTR  lpString,
		LPCTSTR  lpFileName);
	//����CIni::WriteIni(L"config", L"title", 123, L"./main.ini");
	static BOOL WriteInt(
		LPCTSTR lpAppName,
		LPCTSTR lpKeyName,
		INT  nValue,
		LPCTSTR  lpFileName);
	//����CIni::isExist(L"./main.ini");
	static bool isExist(LPCTSTR lpFileName);
		
	static bool ReadBinary(LPCTSTR lpFileName, LPSTR lpBuffer, int _size, int _count = 1,int _offset=0);

	static bool WriteBinary(LPCTSTR lpFileName, LPSTR lpBuffer, int _size, int _count = 1);

 
protected:




};







#endif
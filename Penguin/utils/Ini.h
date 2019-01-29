///////////////////////////
//								  //	
//		Ini 常用文件操作			  //
//		版本号:20180201			  //
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
	//构造函数会初始化应用程序的路径Path
	CIni(void);
	~CIni(void);


	static WCHAR Path[MAX_PATH];
	//范例CIni::ReadString(L"config", L"title", L"default", L"./main.ini"), L"DEBUG", 0)
	static LPTSTR ReadString(
		LPCTSTR lpAppName,
		LPCTSTR lpKeyName,
		LPCTSTR lpDefaut,
		LPCTSTR lpFileName);
	//范例CIni::ReadStringA("config", "title", "default", "./main.ini"), "DEBUG", 0)
	LPSTR CIni::ReadStringA(
		LPCSTR lpAppName,
		LPCSTR lpKeyName,
		LPCSTR lpDefaut,
		LPCSTR lpFileName);
	//范例CIni::ReadInt(L"config", L"title", 123, L"./main.ini"), L"DEBUG", 0)
	static UINT ReadInt(
		LPCTSTR lpAppName, // 指向包含 Section 名称的字符串地址
		LPCTSTR lpKeyName, // 指向包含 Key 名称的字符串地址
		INT nDefault, // 如果 Key 值没有找到，则返回缺省的值是多少
		LPCTSTR lpFileName);
	//范例CIni::WriteIni(L"config", L"title", L"ini_test2", L"./main.ini");
	static BOOL WriteString(
		LPCTSTR lpAppName,
		LPCTSTR lpKeyName,
		LPCTSTR  lpString,
		LPCTSTR  lpFileName);
	//范例CIni::WriteIni(L"config", L"title", 123, L"./main.ini");
	static BOOL WriteInt(
		LPCTSTR lpAppName,
		LPCTSTR lpKeyName,
		INT  nValue,
		LPCTSTR  lpFileName);
	//范例CIni::isExist(L"./main.ini");
	static bool isExist(LPCTSTR lpFileName);
		
	static bool ReadBinary(LPCTSTR lpFileName, LPSTR lpBuffer, int _size, int _count = 1,int _offset=0);

	static bool WriteBinary(LPCTSTR lpFileName, LPSTR lpBuffer, int _size, int _count = 1);

 
protected:




};







#endif
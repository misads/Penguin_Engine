#include <windows.h>
#include <assert.h>
#include <stdlib.h>
#include <malloc.h>
#include <tchar.h>

#ifndef __JONES__STRING__
#define __JONES__STRING__
struct CStringData
{
	long nRefs; //引用记数
	int nDataLength; //字符使用长度
	int nAllocLength; //分配长度
	TCHAR* data() { return (TCHAR*)(this + 1); } //存放字符串的地方 
	//this+1 相当与是CStringData[1];所以TCHAR* data()指的是CStringData[1]的地址
};
class CString
{
public:
	//构造函数
	CString();
	CString(const CString& stringSrc);
	CString(TCHAR ch, int nLength = 1);
	CString(LPCTSTR lpsz); // CString(LPCSTR lpsz); ANSI下版本
	//CString(LPCWSTR lpsz);UNICODE下版本
	CString(LPCTSTR lpch, int nLength); //CString(LPCSTR lpch, int nLength);ANSI下版本
	//CString(LPCWSTR lpch, int nLength);//UNICODE下版本
	CString(const unsigned char* psz);
	~CString();
	//CStringData的属性
	int GetLength() const; //得到字符长度
	int GetAllocLength() const; //得到分配的内存长度
	BOOL IsEmpty() const; //判断字符长度是否为0
	operator LPCTSTR() const; //类型转换
	void Empty(); //清空CStringData
	//操作符重载
	const CString& operator=(const CString& stringSrc);
	const CString& operator=(LPCTSTR lpsz);
	const CString& operator=(TCHAR ch);
	const CString& operator+=(const CString& string);
	const CString& operator+=(TCHAR ch);
	const CString& operator+=(LPCTSTR lpsz);
	TCHAR operator[](int nIndex) const;
	friend CString operator+(const CString& string1, const CString& string2);
	friend CString operator+(const CString& string, TCHAR ch);
	friend CString operator+(TCHAR ch, const CString& string);
	friend CString operator+(const CString& string, LPCTSTR lpsz);
	friend CString operator+(LPCTSTR lpsz, const CString& string);
	//操作,脱离共享数据块
	int Delete(int nIndex, int nCount = 1);//删除从nIndex开始长度为nCount的数据
	int Insert(int nIndex, TCHAR ch); //插入一个字符
	int Insert(int nIndex, LPCTSTR pstr); //插入一个字符串
	int Replace(LPCTSTR lpszOld, LPCTSTR lpszNew); //替换数据
	int Replace(TCHAR chOld, TCHAR chNew); //替换数据
	int Remove(TCHAR chRemove); //移除一个字符
	void TrimRight(LPCTSTR lpszTargetList);
	void TrimRight(TCHAR chTarget);//去掉右边chTarget
	void TrimRight(); //去掉右边空格
	void TrimLeft(LPCTSTR lpszTargets);
	void TrimLeft(TCHAR chTarget); //去掉左边chTarget
	void TrimLeft(); //去掉左边空格
	//取某段字符串
	void SetAt(int nIndex, TCHAR ch);
	TCHAR GetAt(int nIndex) const;
	CString Mid(int nFirst) const; //取某段字符串
	CString Mid(int nFirst, int nCount) const; //取某段字符串
	CString Right(int nCount) const; //取右边字符串
	CString Left(int nCount) const; //取左边字符串
	void CString::MakeUpper(); //大写
	void CString::MakeLower(); //小写
	void CString::MakeReverse(); //????不知道干什么的 strrev
	//查找
	int Find(TCHAR ch) const;
	int Find(TCHAR ch, int nStart) const;
	int ReverseFind(TCHAR ch) const;
	int Find(LPCTSTR lpszSub) const;
	int Find(LPCTSTR lpszSub, int nStart) const;
	int FindOneOf(LPCTSTR lpszCharSet) const;//得到第一个匹配lpszCharSet中其中一个字符的位置 调用_tcspbrk
	//高级操作
	LPTSTR GetBuffer(int nMinBufLength); //重新分配内存,在拷贝原来的数据
	void ReleaseBuffer(int nNewLength = -1); //在[nNewLength]='/0',对内存大小没有改变
	LPTSTR GetBufferSetLength(int nNewLength); //重新分配内存,在拷贝原来的数据
	void FreeExtra(); //深拷贝自己,然后--原来的引用记数器
	LPTSTR LockBuffer(); //引用计数器=-1,加锁
	void UnlockBuffer(); //解锁,引用计数器=1
	//比较
	int Compare(LPCTSTR lpsz) const; //区分大小写比较
	int CompareNoCase(LPCTSTR lpsz) const; //不区分大小写比较
	//比较速度没有Compare快
	int Collate(LPCTSTR lpsz) const; //区分大小写比较
	int CollateNoCase(LPCTSTR lpsz) const; //不区分大小写比较
	//格式化字符串
	void Format(LPCTSTR lpszFormat, ...);//CSting中最长的函数了,完全是自己分析的(牛啊)
private:
	void Init();
	CStringData* GetData() const; //通过m_pchData-1 得到CStringData
	void AllocBuffer(int nLen); //给CStringData分配内存,不带记数器
	void CopyBeforeWrite(); //带引用记数的复制自己深拷贝
	void AllocBeforeWrite(int nLen); //给CStringData分配内存,带记数器
	void AssignCopy(int nSrcLen, LPCTSTR lpszSrcData);//分配内存,并拷贝lpszSrcData内容
	//把nCopyIndex开始的nCopyLen长度的数据拷贝给dest,nExtraLen扩充的长度,次函数好像没下面用
	void AllocCopy(CString& dest, int nCopyLen, int nCopyIndex, int nExtraLen) const;
	void Release(); //--引用记数器并判断是否删除内存,如删除并初始化
	void FormatV(LPCTSTR lpszFormat, va_list argList);//格式化字符串
	void ConcatCopy(int nSrc1Len, LPCTSTR lpszSrc1Data,
		int nSrc2Len, LPCTSTR lpszSrc2Data);//连接数据lpszSrc1Data+lpszSrc2Data
	void ConcatInPlace(int nSrcLen, LPCTSTR lpszSrcData); //连接字符串
	static void  Release(CStringData* pData); //--引用记数器并判断是否删除内存
	static void FreeData(CStringData* pData); //释放内存
	static int SafeStrlen(LPCTSTR lpsz); //得到长度
	LPTSTR m_pchData; //指向CStringData的数据区
};
/*调用CString::Compare比较大小,如果比较中有CStirng的话用
调用operator LPCTSTR()转化类型为LPCTSTR
*/
bool operator==(const CString& s1, const CString& s2);
bool operator==(const CString& s1, LPCTSTR s2);
bool operator==(LPCTSTR s1, const CString& s2);
bool operator!=(const CString& s1, const CString& s2);
bool operator!=(const CString& s1, LPCTSTR s2);
bool operator!=(LPCTSTR s1, const CString& s2);
bool operator<(const CString& s1, const CString& s2);
bool operator<(const CString& s1, LPCTSTR s2);
bool operator<(LPCTSTR s1, const CString& s2);
bool operator>(const CString& s1, const CString& s2);
bool operator>(const CString& s1, LPCTSTR s2);
bool operator>(LPCTSTR s1, const CString& s2);
bool operator<=(const CString& s1, const CString& s2);
bool operator<=(const CString& s1, LPCTSTR s2);
bool operator<=(LPCTSTR s1, const CString& s2);
bool operator>=(const CString& s1, const CString& s2);
bool operator>=(const CString& s1, LPCTSTR s2);
bool operator>=(LPCTSTR s1, const CString& s2);
//////////////////////////////////////////////////////////////////////
//检测lpsz是否有效,调用了IsBadStringPtr
BOOL AfxIsValidString(LPCTSTR lpsz, int nLength = -1);
//检测lp是否能读写权限,调用了IsBadReadPtr,IsBadStringPtr
BOOL AfxIsValidAddress(const void* lp, UINT nBytes, BOOL bReadWrite = TRUE);
//CStirng数组操作
void ConstructElements(CString* pElements, int nCount); //初始化CStirng数组
void DestructElements(CString* pElements, int nCount); //删除CStirng数组
void CopyElements(CString* pDest, const CString* pSrc, int nCount); //CString数组拷贝
#endif
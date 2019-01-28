#include <windows.h>
#include <assert.h>
#include <stdlib.h>
#include <malloc.h>
#include <tchar.h>

#ifndef __JONES__STRING__
#define __JONES__STRING__
struct CStringData
{
	long nRefs; //���ü���
	int nDataLength; //�ַ�ʹ�ó���
	int nAllocLength; //���䳤��
	TCHAR* data() { return (TCHAR*)(this + 1); } //����ַ����ĵط� 
	//this+1 �൱����CStringData[1];����TCHAR* data()ָ����CStringData[1]�ĵ�ַ
};
class CString
{
public:
	//���캯��
	CString();
	CString(const CString& stringSrc);
	CString(TCHAR ch, int nLength = 1);
	CString(LPCTSTR lpsz); // CString(LPCSTR lpsz); ANSI�°汾
	//CString(LPCWSTR lpsz);UNICODE�°汾
	CString(LPCTSTR lpch, int nLength); //CString(LPCSTR lpch, int nLength);ANSI�°汾
	//CString(LPCWSTR lpch, int nLength);//UNICODE�°汾
	CString(const unsigned char* psz);
	~CString();
	//CStringData������
	int GetLength() const; //�õ��ַ�����
	int GetAllocLength() const; //�õ�������ڴ泤��
	BOOL IsEmpty() const; //�ж��ַ������Ƿ�Ϊ0
	operator LPCTSTR() const; //����ת��
	void Empty(); //���CStringData
	//����������
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
	//����,���빲�����ݿ�
	int Delete(int nIndex, int nCount = 1);//ɾ����nIndex��ʼ����ΪnCount������
	int Insert(int nIndex, TCHAR ch); //����һ���ַ�
	int Insert(int nIndex, LPCTSTR pstr); //����һ���ַ���
	int Replace(LPCTSTR lpszOld, LPCTSTR lpszNew); //�滻����
	int Replace(TCHAR chOld, TCHAR chNew); //�滻����
	int Remove(TCHAR chRemove); //�Ƴ�һ���ַ�
	void TrimRight(LPCTSTR lpszTargetList);
	void TrimRight(TCHAR chTarget);//ȥ���ұ�chTarget
	void TrimRight(); //ȥ���ұ߿ո�
	void TrimLeft(LPCTSTR lpszTargets);
	void TrimLeft(TCHAR chTarget); //ȥ�����chTarget
	void TrimLeft(); //ȥ����߿ո�
	//ȡĳ���ַ���
	void SetAt(int nIndex, TCHAR ch);
	TCHAR GetAt(int nIndex) const;
	CString Mid(int nFirst) const; //ȡĳ���ַ���
	CString Mid(int nFirst, int nCount) const; //ȡĳ���ַ���
	CString Right(int nCount) const; //ȡ�ұ��ַ���
	CString Left(int nCount) const; //ȡ����ַ���
	void CString::MakeUpper(); //��д
	void CString::MakeLower(); //Сд
	void CString::MakeReverse(); //????��֪����ʲô�� strrev
	//����
	int Find(TCHAR ch) const;
	int Find(TCHAR ch, int nStart) const;
	int ReverseFind(TCHAR ch) const;
	int Find(LPCTSTR lpszSub) const;
	int Find(LPCTSTR lpszSub, int nStart) const;
	int FindOneOf(LPCTSTR lpszCharSet) const;//�õ���һ��ƥ��lpszCharSet������һ���ַ���λ�� ����_tcspbrk
	//�߼�����
	LPTSTR GetBuffer(int nMinBufLength); //���·����ڴ�,�ڿ���ԭ��������
	void ReleaseBuffer(int nNewLength = -1); //��[nNewLength]='/0',���ڴ��Сû�иı�
	LPTSTR GetBufferSetLength(int nNewLength); //���·����ڴ�,�ڿ���ԭ��������
	void FreeExtra(); //����Լ�,Ȼ��--ԭ�������ü�����
	LPTSTR LockBuffer(); //���ü�����=-1,����
	void UnlockBuffer(); //����,���ü�����=1
	//�Ƚ�
	int Compare(LPCTSTR lpsz) const; //���ִ�Сд�Ƚ�
	int CompareNoCase(LPCTSTR lpsz) const; //�����ִ�Сд�Ƚ�
	//�Ƚ��ٶ�û��Compare��
	int Collate(LPCTSTR lpsz) const; //���ִ�Сд�Ƚ�
	int CollateNoCase(LPCTSTR lpsz) const; //�����ִ�Сд�Ƚ�
	//��ʽ���ַ���
	void Format(LPCTSTR lpszFormat, ...);//CSting����ĺ�����,��ȫ���Լ�������(ţ��)
private:
	void Init();
	CStringData* GetData() const; //ͨ��m_pchData-1 �õ�CStringData
	void AllocBuffer(int nLen); //��CStringData�����ڴ�,����������
	void CopyBeforeWrite(); //�����ü����ĸ����Լ����
	void AllocBeforeWrite(int nLen); //��CStringData�����ڴ�,��������
	void AssignCopy(int nSrcLen, LPCTSTR lpszSrcData);//�����ڴ�,������lpszSrcData����
	//��nCopyIndex��ʼ��nCopyLen���ȵ����ݿ�����dest,nExtraLen����ĳ���,�κ�������û������
	void AllocCopy(CString& dest, int nCopyLen, int nCopyIndex, int nExtraLen) const;
	void Release(); //--���ü��������ж��Ƿ�ɾ���ڴ�,��ɾ������ʼ��
	void FormatV(LPCTSTR lpszFormat, va_list argList);//��ʽ���ַ���
	void ConcatCopy(int nSrc1Len, LPCTSTR lpszSrc1Data,
		int nSrc2Len, LPCTSTR lpszSrc2Data);//��������lpszSrc1Data+lpszSrc2Data
	void ConcatInPlace(int nSrcLen, LPCTSTR lpszSrcData); //�����ַ���
	static void  Release(CStringData* pData); //--���ü��������ж��Ƿ�ɾ���ڴ�
	static void FreeData(CStringData* pData); //�ͷ��ڴ�
	static int SafeStrlen(LPCTSTR lpsz); //�õ�����
	LPTSTR m_pchData; //ָ��CStringData��������
};
/*����CString::Compare�Ƚϴ�С,����Ƚ�����CStirng�Ļ���
����operator LPCTSTR()ת������ΪLPCTSTR
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
//���lpsz�Ƿ���Ч,������IsBadStringPtr
BOOL AfxIsValidString(LPCTSTR lpsz, int nLength = -1);
//���lp�Ƿ��ܶ�дȨ��,������IsBadReadPtr,IsBadStringPtr
BOOL AfxIsValidAddress(const void* lp, UINT nBytes, BOOL bReadWrite = TRUE);
//CStirng�������
void ConstructElements(CString* pElements, int nCount); //��ʼ��CStirng����
void DestructElements(CString* pElements, int nCount); //ɾ��CStirng����
void CopyElements(CString* pDest, const CString* pSrc, int nCount); //CString���鿽��
#endif
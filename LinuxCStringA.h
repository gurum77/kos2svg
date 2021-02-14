#pragma once

/*
http://www.gnu.org/licenses/gpl-3.0.html

LinuxCStringA, LinuxCStringA.h
Copyright (C) 2015-11-24  greenfish @ gmail.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

And,
No Commercial only,
If you want to use it commercially, contact to author.
*/



#include <string>
#include <vector>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

class CStringA
{
public:
	CStringA(void) { };
	~CStringA(void) { };

public:
	CStringA(const CStringA& obj)		{m_str = obj.m_str;}
	CStringA(const char* psz)
	{
		if (psz == NULL)
			m_str = "";
		else
			m_str = psz;
	}

	char GetAt(int idx)
	{
		if (m_str.length() == 0)
			return '\0';

		return m_str.at(idx);
	}
	std::string GetBuffer()
	{
		return m_str;
	}
	// GetBuffer()와 동일(windows용 소스 대응용)
	std::string GetBuffer(int len)
	{
		return m_str;
	}
	void operator=(const CStringA& obj)	{m_str = obj.m_str;}
	void operator=(const char* p)			{if (NULL != p) m_str = p;}
	CStringA& operator+=(const char* p)	{if (NULL != p) m_str += p; return (*this);}
	friend CStringA operator+(const CStringA& str1, const char* psz2 )
	{
		CStringA r;
		if (psz2 == NULL)
			r.m_str = str1.m_str;
		else
			r.Format("%s%s", str1.m_str.c_str(), psz2);
		/*CStringA r;
		r.m_str=str1.m_str;
		if (NULL != psz2)
		{
			r.m_str = r.m_str + psz2;
		} */
		return r;
	}
	friend CStringA operator+(const CStringA& str1, const CStringA& str2)
	{
		CStringA r;
		r.Format("%s%s", str1.m_str.c_str(), str2.m_str.c_str());
		//r.m_str = str1.m_str + str2.m_str;

		return r;
	}

	friend CStringA operator+(const char* psz1, const CStringA& str2)
	{
		if (psz1 == NULL)
			return str2;

		CStringA r;
		r.m_str = psz1 + str2.m_str;
		return r;
	}
	bool operator==(const char* p)			{return (m_str.compare(p) == 0);}
	operator const char*()					{return m_str.c_str();}
	int GetLength(void)						{return m_str.length();}
	bool IsEmpty()							{return(GetLength()==0);}
	int Find(const char* pszSub, int iStart=0)	{if (NULL == pszSub) return -1; return m_str.find(pszSub, iStart);}
	int Find(const char ch, int iStart=0)	{return m_str.find(ch, iStart);}

	CStringA Mid(int iFirst, int nCount)
	{
		CStringA r;
		try
		{
			r.m_str = m_str.substr(iFirst, nCount);
		}
		catch(...)
		{
		}
		return r;
	}

	CStringA Mid(int iFirst)
	{
		CStringA r;
		try
		{
			r.m_str = m_str.substr(iFirst);
		}
		catch(...)
		{
		}
		return r;
	}

	int Delete(int iIndex, int nCount = 1)
	{
		try
		{
			m_str.erase(iIndex, nCount);
		}
		catch(...)
		{
		}
		return m_str.length();
	}

	int Insert(int iIndex, const char* psz)
	{
		try
		{
			if (NULL != psz) m_str.insert(iIndex, psz);
		}
		catch(...)
		{
			m_str += psz;
		}

		return m_str.length();
	}

	int Insert(int iIndex, char ch)
	{
		try
		{
			m_str.insert(iIndex, 1, ch);
		}
		catch(...)
		{
			m_str += ch;
		}
		return m_str.length();
	}

	CStringA& TrimRight(char chTarget)
	{
		size_t l = 0;
		l = m_str.length();

		for (;;)
		{
			if (0 == l) break;

			if (m_str[l-1] != chTarget)
			{
				break;
			}
			else
			{
				m_str.erase(l-1, 1);
				l--;
			}
		}

		return (*this);
	}

	CStringA& TrimRight(const char* pszTargets)
	{
		size_t l = 0;

		if (NULL == pszTargets) return (*this);

		l = m_str.length();

		for (;;)
		{
			if (0 == l) break;

			if (NULL == strchr(pszTargets, m_str[l-1]))
			{
				break;
			}
			else
			{
				m_str.erase(l-1, 1);
				l--;
			}
		}

		return (*this);
	}

	CStringA& TrimLeft(char chTarget)
	{
		for (;;)
		{
			if (m_str[0] != chTarget)
			{
				break;
			}
			else
			{
				m_str.erase(0, 1);
			}
		}

		return (*this);
	}

	CStringA& TrimLeft(const char* pszTargets)
	{
		if (NULL == pszTargets) return (*this);

		for (;;)
		{
			if (NULL == strchr(pszTargets, m_str[0]))
			{
				break;
			}
			else
			{
				m_str.erase(0, 1);
			}
		}

		return (*this);
	}

	int Replace(const char* pszOld, const char* pszNew)
	{
		int r = 0;
		size_t l = 0;
		std::string::size_type offset = 0;

		if ((NULL == pszOld) || (NULL == pszNew)) return 0;

		for (;;)
		{
			offset = m_str.find(pszOld, offset);

			if (std::string::npos == offset)
			{
				break;
			}
			else
			{
				if (0 == l)
				{
					l = strlen(pszOld);
					if (0 == l) return 0;
				}
				m_str.replace(offset, l, pszNew);
				offset += l;
				r++;
			}
		}
		return r;
	}

	void Format(const char* pszFormat, ...)
	{
		int		len	= 0;
		va_list	vl;

		va_start(vl, pszFormat);

		// 포맷의 길이를 구한다.
#if (_MSC_VER >= 1400)	// Visual studio 2005 이상
		len = _vscprintf(pszFormat, vl) + 1;
#else
		len = vsnprintf(NULL, 0, pszFormat, vl) + 1;
#endif

		// 버퍼의 크기를 조정한다.
		m_str.resize(len, '\0');

		// 포맷을 적용한다.
		va_start(vl, pszFormat);
#if (_MSC_VER >= 1400)	// Visual studio 2005 이상
		if (vsnprintf_s(&m_str[0], len, _TRUNCATE, pszFormat, vl) > len)
#else
		if (vsnprintf(&m_str[0], len, pszFormat, vl) > len)
#endif
		{
			// Error
		}
		va_end(vl);
	}

protected:
	std::string m_str;
};

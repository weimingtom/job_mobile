// This is supposed to be a collection of string class implementations for different purposes

#ifndef _TEMPLATE_STRING_HDR_
#define _TEMPLATE_STRING_HDR_

using namespace std;
#include "jc/platform.h"

#if !defined(LINUX)
#include <assert.h>
#endif


#include <string>
#include "string.h"
#include "jc/StlUtils.h"

namespace nMech
{
	namespace nJC
	{

		//[Timur] 
		//! Typedef for string to be used everywhere.
		typedef string String;

		// A basic string that can be used (with caution though) to pass a variable-length string
		// between boundaries of DLLs
		// (release/debug versions are binary compatible, as long as they're constructed, destructed
		// and modified withon one DLL
		// THe string contents may be safely modified, up to (excluding) the \0 character
		// THE \0 character cannot be touched AT ALL! because it can end up with an access violation
		class jcBasicString
		{
		public:
			static char* strdup (const char* szSource, size_t nLength)
			{
				if (szSource && nLength > 0)
				{
					char* pNewString = (char*)malloc(nLength+1);
					memcpy (pNewString, szSource, nLength);
					pNewString[nLength] = '\0';
					return pNewString;
				}
				else
					return NULL;
			}

			// for debug: to use the memory manager
			static char* strdup (const char* szSource)
			{
				if (szSource && szSource[0])
				{
					char* pNewString = (char*)malloc(strlen(szSource)+1);
					strcpy (pNewString, szSource);
					return pNewString;
				}
				else
					return NULL;
			}

			static char* strcat (const char* szLeft, const char*szRight)
			{
				if (szLeft[0] || szRight[0])
				{
					size_t sizeLeft = strlen(szLeft), sizeRight = strlen(szRight);
					char* pNewString = (char*) malloc (sizeLeft + sizeRight + 1);
					memcpy (pNewString, szLeft, sizeLeft);
					// copy together with the terminating null
					memcpy (pNewString+sizeLeft, szRight, sizeRight+1);
					return pNewString;
				}
				else
					return NULL;
			}

			jcBasicString (const char* szRight)
			{
				m_pString = strdup(szRight);
			}

			jcBasicString (const char* szBegin, const char* szEnd)
			{
				m_pString = strdup (szBegin, (unsigned int)(szEnd-szBegin));
			}

			jcBasicString (const char* szBegin, unsigned nLength)
			{
				m_pString = strdup (szBegin, nLength);
			}

			jcBasicString(const jcBasicString& rRight)
			{
				m_pString = strdup(rRight.c_str());
			}

			jcBasicString(const string& rRight)
			{
				m_pString = strdup(rRight.c_str(), rRight.length());
			}

			jcBasicString():
			m_pString(NULL)
			{
			}

			~jcBasicString()
			{
				free (m_pString);
			}

			jcBasicString& operator = (const char* szRight)
			{
				//assert (m_pString == m_pDuplicate);
				free (m_pString);
				m_pString = strdup (szRight);
#ifdef _DEBUG
				//m_pDuplicate = m_pString;
#endif
				return *this;
			}

			void assign (const char* szBegin, const char* szEnd)
			{
				free (m_pString);
				m_pString = strdup(szBegin, (unsigned int)(szEnd-szBegin));
			}

			void assign (const char* szBegin, unsigned nLength)
			{
				free (m_pString);
				m_pString = strdup (szBegin, nLength);
			}

			jcBasicString& operator = (const jcBasicString& rRight)
			{
				return (*this) = rRight.c_str();
			}

			jcBasicString& operator = (const string& rRight)
			{
				return (*this) = rRight.c_str();
			}

			operator const char*() const {return m_pString?m_pString:"";}

			//operator char*() {return m_pString;}
			const char* c_str() const
			{
				//assert (m_pString == m_pDuplicate);
				return m_pString?m_pString:"";
			}

			char operator[] (int nIndex)const
			{
				//assert (m_pString == m_pDuplicate);
				assert (nIndex >= 0 && nIndex < length());
				return m_pString[nIndex];
			}

			char& operator[] (int nIndex)
			{
				//assert (m_pString == m_pDuplicate);
				assert (nIndex >= 0 && nIndex < length());
				return m_pString[nIndex];
			}

			int length()const
			{
				//assert (m_pString == m_pDuplicate);
				return m_pString ? (int)strlen(m_pString):0;
			}
			int size()const {return length();}

			bool empty () const
			{
				//assert (m_pString == m_pDuplicate);
				return !m_pString || !m_pString[0];
			}

			bool operator < (const jcBasicString& strRight) const
			{
				return strcmp(c_str(), strRight.c_str()) < 0;
			}
			bool operator == (const jcBasicString& strRight) const
			{
				return strcmp(c_str(), strRight.c_str()) == 0;
			}
			bool operator > (const jcBasicString& strRight) const
			{
				return strcmp(c_str(), strRight.c_str()) > 0;
			}

			jcBasicString& operator += (const char*szRight)
			{
				char* pResult = strcat (c_str(), szRight);
				free (m_pString);
				m_pString = pResult;
				return (*this);
			}

			jcBasicString& operator += (const jcBasicString& rRight)
			{
				return (*this)+= rRight.c_str();
			}

			void swap (jcBasicString& right)
			{
				char* pTmp = m_pString;
				m_pString = right.m_pString;
				right.m_pString = pTmp;
			}

			friend jcBasicString operator + (const char* szLeft, const jcBasicString& rRight);
			friend jcBasicString operator + (const jcBasicString& rLeft, const char* szRight);
			friend jcBasicString operator + (const jcBasicString& rLeft, const jcBasicString& rRight);
		protected:
			void attach (char* szString)
			{
				if (m_pString != szString)
				{
					free (m_pString);
					m_pString = szString;
				}
			}
		protected:
			// NULL if the string is empty
			char* m_pString;
#ifdef _DEBUG
			// this is to check against memory corruption - but it breaks ABI and can only be used when
			// everything is debug
			//char* m_pDuplicate;
#endif
		};

		inline jcBasicString operator + (const char* szLeft, const jcBasicString& rRight)
		{
			jcBasicString strResult;
			strResult.attach(jcBasicString::strcat (szLeft, rRight.c_str()));
			return strResult;
		}

		inline jcBasicString operator + (const jcBasicString& rLeft, const char* szRight)
		{
			jcBasicString strResult;
			strResult.attach(jcBasicString::strcat (rLeft.c_str(), szRight));
			return strResult;
		}

		inline jcBasicString operator + (const jcBasicString& rLeft, const jcBasicString& rRight)
		{
			jcBasicString strResult;
			strResult.attach (jcBasicString::strcat (rLeft.c_str(), rRight.c_str()));
			return strResult;
		}

		namespace stl
		{
			//! Specialization of jcBasicString to const char cast.
			template <>
				inline const char* constchar_cast( const jcBasicString &type )
			{
				return type.c_str();
			}
		}

	}//nJC
}//nMech


#endif
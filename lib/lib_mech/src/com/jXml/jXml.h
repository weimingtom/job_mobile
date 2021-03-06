/* file : jXml.h
Coder : by icandoit (mech12@nate.com)
Date : 2005-06-08 00:08:28
title : 
desc : 

어떤 이가 석가모니를 찾아와 호소했다.
"저는 하는 일마다 제대로 되는 일이 없으니 이 무슨 이유입니까?"
"그것은 너가 남에게 베풀지 않았기 때문이니라."
"저는 아무것도 가진 게 없는 빈털터리입니다."
"그렇지 않느니라. 재산이 없더라도 남에게 줄 수 있는 일곱 가지는 누가에게나 있는 법이다. 

첫째는 화안시 즉 얼굴에 화색을 띠고 부드럽게 정다운 얼굴로 남을 대하는것이요. 
둘째는 언시로서 말로 얼마든지 베풀수 있으니 사랑의 말, 칭찬의 말, 위로의 말, 격려의 말, 양보의 말, 부드러운 말등을 전하는 것이다. 
셋째는 심시로서 마음의 문을 열고 따뜻한 마음을 주는것이고 
넷째는 안시 즉 호의를 담은 눈으로 사람을 보는 것처럼 눈으로 베푸는 것이다. 
다섯째는 신시, 곧 몸으로 행하는 것으로서 남의 짐을 들어 준다거나 일을 돕는 것이요. 
여섯째는 좌시로 때와 장소에 맞게 자리를 내주어 양보하는것이고 
일곱째는 찰시로 굳이 묻지 않고 상대의 마음을 헤아려 알아서 도와 주는 것이다. 

네가 이 일곱가지를 행하여 습관이 붙으면 너에게 행운이 따를 것이니라.

*/

#ifndef __jXml_header__
#define __jXml_header__
#pragma once


#ifdef JXML_EXPORTS
#define JXML_API __declspec(dllexport)
#else
#define JXML_API __declspec(dllimport)
#endif

#include "interface/xml/jIXml.h"
#include "header\\m_Manager.h"
#include "jxDocument.h"
#include "interface/xml/jIXmlCallBackManager.h"
#include <boost/any.hpp>
namespace nMech
{
	namespace nXML
	{
		class jXmlCallBackManager : public jIXmlCallBackManager
		{
		private:
			jLIST_TYPEDEF_map(std::tstring, jXml_Callback_ft, m_jXml_Callback);
		public:
			virtual void SetCallback(cstr, jXml_Callback_ft);
			virtual void RunCallBack(cstr sz , boost::any a);
		};


		//----------------------------------------------------------------
		class  jXml : public jIXml
			//----------------------------------------------------------------
		{
			jINTERFACE_HEADER(jIXml);

			jIXml_Param m_Param;
		public:
			jLIST_TYPEDEF_map(std::tstring, jxD, m_DocList);

			int m_iFlag;
			jFLAG_ENUM(eUSE_TINY_XML);


			jXml() : m_iFlag(0)
			{
			}

			~jXml();

			jxD* Insert(tcstr key); // 해당이름으로 오브젝트를 등록하고 주소를 리턴.

			void SetAutoLoad(bool is);
			bool GetAutoLoad();
			void jTestUnit_xmllid();
			void Release();
		};

		extern jXml* g_pXml;

	}
}

#endif // __jXml_header__

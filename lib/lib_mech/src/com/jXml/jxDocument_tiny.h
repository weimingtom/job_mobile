/*
 *	

 � �̰� ������ϸ� ã�ƿ� ȣ���ߴ�.
 "���� �ϴ� �ϸ��� ����� �Ǵ� ���� ������ �� ���� �����Դϱ�?"
 "�װ��� �ʰ� ������ ��Ǯ�� �ʾұ� �����̴϶�."
 "���� �ƹ��͵� ���� �� ���� �����͸��Դϴ�."
 "�׷��� �ʴ��϶�. ����� ������ ������ �� �� �ִ� �ϰ� ������ �������Գ� �ִ� ���̴�. 

 ù°�� ȭ�Ƚ� �� �󱼿� ȭ���� ��� �ε巴�� ���ٿ� �󱼷� ���� ���ϴ°��̿�. 
 ��°�� ��÷μ� ���� �󸶵��� ��Ǯ�� ������ ����� ��, Ī���� ��, ������ ��, �ݷ��� ��, �纸�� ��, �ε巯�� ������ ���ϴ� ���̴�. 
 ��°�� �ɽ÷μ� ������ ���� ���� ������ ������ �ִ°��̰� 
 ��°�� �Ƚ� �� ȣ�Ǹ� ���� ������ ����� ���� ��ó�� ������ ��Ǫ�� ���̴�. 
 �ټ�°�� �Ž�, �� ������ ���ϴ� �����μ� ���� ���� ��� �شٰų� ���� ���� ���̿�. 
 ����°�� �½÷� ���� ��ҿ� �°� �ڸ��� ���־� �纸�ϴ°��̰� 
 �ϰ�°�� ���÷� ���� ���� �ʰ� ����� ������ ��Ʒ� �˾Ƽ� ���� �ִ� ���̴�. 

 �װ� �� �ϰ������� ���Ͽ� ������ ������ �ʿ��� ����� ���� ���̴϶�.

 */
#pragma once
#include "jxDocument.h"

#pragma once

class TiXmlNode;
class TiXmlElement;
namespace nMech
{
	namespace nXML
	{

		//****************************************************************
		class jxElement_tiny : public jxElement
			//****************************************************************
		{
		public:
			void Load(TiXmlNode* pElmt);
			void LoadAtt(TiXmlElement*  node);
		};

		//****************************************************************
		class jxDocument_tiny   :public jxElement_tiny
			//****************************************************************
		{
		public:
			void Load(cstr szURL);
			void LoadFromBuffer(tcstr szBuffer);
		};

	}
}
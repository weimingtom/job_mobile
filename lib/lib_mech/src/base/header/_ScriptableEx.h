#ifndef _j_asdflwf3d98sdSCRIPTABLE_H_
#define _j_asdflwf3d98sdSCRIPTABLE_H_

#include <vector>
#include <string>
//#define _NO_HASHMAP
//#define NO_USERDATA_FOR_PROPERTIES
#ifndef _NO_HASHMAP
#include <map>
#else
#if defined(LINUX)
#include <ext/hash_map>
#else
#include <hash_map>
#endif
#endif
#include "interface\\jILua.h"

namespace nMech
{

	namespace nLUA
	{

		struct _ScriptableBinder
		{
			virtual void InitializeTemplate(jILua*)=0;
			virtual void ReleaseTemplate()=0;
			virtual cstr GetName()=0;
		};

		template<class T>
		class _ScriptableEx
		{
		public:
			_ScriptableEx()
			{
				//m_nFuncNum=0;
				m_pScriptThis=NULL;
				m_nBase=NULL;

			}
			virtual ~_ScriptableEx()
			{
				if(m_pScriptThis)
				{
					m_pScriptThis->SetNativeData(NULL);
					m_pScriptThis->AddSetGetHandlers(NULL,NULL);
					m_pScriptThis->Release();
				}



			}

			typedef int(T::*MemberFunc)(IFunctionHandler *pH);

			typedef std::vector<MemberFunc> FunctionsVec;
			typedef typename FunctionsVec::iterator FunctionsVecItor;

			enum PropertyType
			{
				PROPERTY_TYPE_BOOL,
				PROPERTY_TYPE_INT,
				PROPERTY_TYPE_CHAR,
				PROPERTY_TYPE_FLOAT,
				PROPERTY_TYPE_STRING,
				PROPERTY_TYPE_OBJECT
			};
			struct Property
			{
				Property()
				{
					val=0;
				}
				Property(const Property &p)
				{
					nType=p.nType;
					val=p.val;
				}
				PropertyType nType;
				/*union Value
				{
				int *nVal;
				bool *bVal;
				float *fVal;
				char *sVal;
				string *strVal;
				IScriptObject *oVal;
				}v;*/
				unsigned int val;
			};   

			UINT_PTR m_nBase;


			typedef std::vector<Property *> PropertiesVec;
			typedef typename PropertiesVec::iterator PropertiesVecItor;

			void Init(jILua *,T* pParent){
				assert(nInterface::g_pjILua);
				_ScriptableEx<T>::m_pFunctionHandler=nInterface::g_pjILua->GetFunctionHandler();
				if(!_ScriptableEx<T>::m_pFunctionHandler)
					if(nInterface::g_pjILog)nInterface::g_pjILog->Error(TEXT("Scriptable EX:FUNCTION HANDLER NULL"));			
				m_pScriptThis=pScriptSystem->CreateObject();
				m_pScriptThis->SetNativeData(pParent);
				m_pScriptThis->Delegate(_ScriptableEx<T>::m_pTemplateTable);

				if(m_pScriptThis->GetNativeData()!=pParent)
					if(nInterface::g_pjILog)nInterface::g_pjILog->Error(TEXT("Scriptable EX:Properties map"));			
			}
			void InitGlobal(jILua *pScriptSystem,const char *sName,T* pParent){
				_ScriptableEx<T>::m_pFunctionHandler=nInterface::g_pjILua->GetFunctionHandler();
				if(!_ScriptableEx<T>::m_pFunctionHandler)
					if(nInterface::g_pjILog)nInterface::g_pjILog->Error(TEXT("Scriptable EX:FUNCTION HANDLER NULL"));			
				m_pScriptThis=pScriptSystem->CreateGlobalObject(sName);
				m_pScriptThis->SetNativeData(pParent);
				if(_ScriptableEx<T>::m_pTemplateTable)
					m_pScriptThis->Clone(_ScriptableEx<T>::m_pTemplateTable);

				if(m_pScriptThis->GetNativeData()!=pParent)
					if(nInterface::g_pjILog)nInterface::g_pjILog->Error(TEXT("Scriptable EX:Init Global"));			
			}
			static void InitializeTemplate(jILua *pSS)
			{
			}
			static void ReleaseTemplate()
			{
				if(m_pTemplateTable!=NULL)
				{
					m_pTemplateTable->Release();
					m_pTemplateTable=NULL;
				}
				if(m_pvPropertiesVector)
				{
					PropertiesVecItor itor;
					itor=m_pvPropertiesVector->begin();
					while(itor!=m_pvPropertiesVector->end())
					{
						delete (*itor);
						itor++;
					}
					delete m_pvPropertiesVector;
				}
				m_pvPropertiesVector=NULL;
				if(m_pPropertiesTable)
					m_pPropertiesTable->Release();
				m_pPropertiesTable=NULL;
			}
			static void RegisterFunction(jILua *pSS,const char *sName,MemberFunc mfunc){
				if(m_pTemplateTable==NULL)
				{

					m_pTemplateTable=pSS->CreateObject();
				}

				int nIdx = (int)m_vFuncs.size();
				m_vFuncs.push_back(mfunc);
				m_pTemplateTable->AddFunction(sName,_ScriptableEx<T>::FuncThunk,nIdx);
				//		m_nFuncNum++;
			}
			bool EnablePropertiesMapping(void *pBase)
			{
				assert(pBase);

				m_nBase=(UINT_PTR)pBase;
				/*#ifndef NO_USERDATA_FOR_PROPERTIES
				m_pProperties=nInterface::g_pjILua->CreateObject();
				m_pvPropertiesVector=new PropertiesVec;
				#endif*/
				return m_pScriptThis->AddSetGetHandlers(_ScriptableEx<T>::SetThunk,_ScriptableEx<T>::GetThunk);
			}
			static void AllowPropertiesMapping(jILua *pSS)
			{ 
				if(m_pPropertiesTable==NULL)
				{
					m_pPropertiesTable=pSS->CreateObject();
					m_pvPropertiesVector=new PropertiesVec;
				}
			}
			static void InsertProperty(const char *sName,Property &prop)
			{

				USER_DATA ud;
				Property *p=new Property;
				m_pvPropertiesVector->push_back(p);
				*p=prop;
				ud=nInterface::g_pjILua->CreateUserData((INT_PTR)p,-1);
				m_pPropertiesTable->SetValue(sName,ud);
				//test
				int nTemp;
				ULONG_PTR nP;
				if(!m_pPropertiesTable->GetUDValue(sName,nP,nTemp))
					if(nInterface::g_pjILog)nInterface::g_pjILog->Error(TEXT("Scriptable EX:Insert Property (GetUDValue)"));			
				p=(Property *)nP;
				if(p->nType!=prop.nType)
					if(nInterface::g_pjILog)nInterface::g_pjILog->Error(TEXT("Scriptable EX:Insert Property"));						
			}

			static void RegisterProperty(const char *sName,PropertyType t, unsigned int offset)
			{
				Property prop;
				prop.nType=t;
				prop.val=offset;
				InsertProperty(sName,prop);
			}
			/*static void RegisterProperty(const char *sName,int *nVal)
			{
			Property prop;
			prop.nType=PROPERTY_TYPE_INT;
			prop.val=((void *)nVal)-m_pBase;
			InsertProperty(sName,prop);
			}
			static void RegisterProperty(const char *sName,char *sVal)
			{
			Property prop;
			prop.nType=PROPERTY_TYPE_CHAR;
			prop.val=((void *)sVal)-m_pBase;
			InsertProperty(sName,prop);
			}
			static void RegisterProperty(const char *sName,float *fVal)
			{
			Property prop;
			prop.nType=PROPERTY_TYPE_FLOAT;
			prop.val=((void *)fVal)-m_pBase;
			InsertProperty(sName,prop);
			}
			static void RegisterProperty(const char *sName,string  *strVal)
			{
			Property prop;
			prop.nType=PROPERTY_TYPE_STRING;
			prop.val=((void *)strVal)-m_pBase;
			InsertProperty(sName,prop);
			}
			static void RegisterProperty(const char *sName,IScriptObject  *oVal)
			{
			Property prop;
			prop.nType=PROPERTY_TYPE_OBJECT;
			prop.val=((void *)oVal)-m_pBase;
			InsertProperty(sName,prop);
			}*/
			IScriptObject *GetScriptObject(){
				return m_pScriptThis;
			}
			IScriptObject *operator ->(){
				return m_pScriptThis;
			}
			/////////////////////////////////////////
		protected:
			static int FuncThunk(HSCRIPT h) {
				m_pFunctionHandler->__Attach(h);
				T *pThis=(T*)(m_pFunctionHandler->GetThis());
				if(!pThis)
				{
					nInterface::g_pjILua->RaiseError("Null Self");
					::OutputDebugStringA("Null Self\n");
					return 0;
				}
				//int i=m_pFunctionHandler->GetFunctionID();
				return (pThis->*(pThis->m_vFuncs[m_pFunctionHandler->GetFunctionID()]))(m_pFunctionHandler);
			}
			static int SetThunk(HSCRIPT h) {
				m_pFunctionHandler->__Attach(h);
				T *pThis=(T *)m_pFunctionHandler->GetThis();
				const char *sIndex;
				if(pThis && m_pFunctionHandler->GetParam(1,sIndex))
				{
					int nCookie;
					USER_DATA nP;
					if(_ScriptableEx<T>::m_pPropertiesTable->GetUDValue(sIndex,nP,nCookie)/*pThis->m_pProperties->GetUDValue(sIndex,nP,nCookie)*/)
					{
						Property *prop=((Property*)nP);
						if(nCookie!=-1)
							if(nInterface::g_pjILog)nInterface::g_pjILog->Error(TEXT("Scriptable EX:Set Thunk"));								
						assert(pThis->m_nBase);
						void *val=(void *)(pThis->m_nBase+prop->val);
						switch(prop->nType)
						{
						case PROPERTY_TYPE_INT:
							m_pFunctionHandler->GetParam(2,(*((int *)val)));
							return 0;
							break;
						case PROPERTY_TYPE_FLOAT:
							m_pFunctionHandler->GetParam(2,(*((float *)val)));
							return 0;
							break;
						case PROPERTY_TYPE_CHAR:
							{
								const char *sTemp=NULL;
								m_pFunctionHandler->GetParam(2,sTemp);
								if(!sTemp)
									return -1;
								strcpy(((char *)val),sTemp);
							}
							return 0;
							break;
						case PROPERTY_TYPE_STRING:
							{
								const char *sTemp=NULL;
								m_pFunctionHandler->GetParam(2,sTemp);
								if(!sTemp)
									return -1;
								(*((string *)val))=sTemp;
							}
							return 0;
							break;
						case PROPERTY_TYPE_BOOL:
							m_pFunctionHandler->GetParam(2,(*((bool *)val)));
							return 0;
							break;
						case PROPERTY_TYPE_OBJECT:
							m_pFunctionHandler->GetParam(2,((IScriptObject *)val));
							return 0;
							break;
						default:
							return -1;
							break;
						}

					}
				}
				//returning -1 mean that the script engine must manage this property himself
				return -1;
			}

			static int GetThunk(HSCRIPT h) {
				static char cTemp[200];
				m_pFunctionHandler->__Attach(h);
				T *pThis=(T *)m_pFunctionHandler->GetThis();
				const char *sIndex;
				if(pThis && m_pFunctionHandler->GetParam(1,sIndex))
				{

					int nCookie;
					USER_DATA nP;
					if(_ScriptableEx<T>::m_pPropertiesTable->GetUDValue(sIndex,nP,nCookie))
					{
						Property *prop=((Property*)nP);
						if(nCookie!=-1)
							if(nInterface::g_pjILog)nInterface::g_pjILog->Error(TEXT("Scriptable EX:GetParam:GetUdValue"));			
						assert(pThis->m_nBase);
						void *val=(void *)(pThis->m_nBase+prop->val);
						switch(prop->nType)
						{
						case PROPERTY_TYPE_INT:
							return m_pFunctionHandler->EndFunction((*((int *)val)));
							break;
						case PROPERTY_TYPE_FLOAT:
							return m_pFunctionHandler->EndFunction((*((float *)val)));
							break;
						case PROPERTY_TYPE_CHAR:
							return m_pFunctionHandler->EndFunction((const char *)val);
							break;
						case PROPERTY_TYPE_STRING:{
							return m_pFunctionHandler->EndFunction((*((string *)val)).c_str());
																			}
																			break;
						case PROPERTY_TYPE_BOOL:
							return m_pFunctionHandler->EndFunction((*((bool *)val)));
							break;
						case PROPERTY_TYPE_OBJECT:
							return m_pFunctionHandler->EndFunction((((IScriptObject *)val)));
							break;
						default:
							return -1;
							break;
						}

					}
				}
				//returning -1 mean that the script engine must manage this property himself
				return -1;
			}


			//PropertiesVec *m_pvPropertiesVector;
			//IScriptObject *m_pProperties;

			//unsigned long m_nFuncNum;
			IScriptObject *m_pScriptThis;

			static FunctionsVec m_vFuncs;
			static IScriptObject *m_pTemplateTable;
			static IScriptObject *m_pPropertiesTable;
			static PropertiesVec *m_pvPropertiesVector;
			static IFunctionHandler *m_pFunctionHandler;
		};
		/* *_* by icandoit : 2005-06-22 15:37:00

		/////////////////////////////////////////////////////////////////////////////
		#if defined(LINUX)
		#define _DECLARE_SCRIPTABLEEX(_class) template<> IFunctionHandler * _ScriptableEx<_class>::m_pFunctionHandler=NULL; \
		template<> _ScriptableEx<_class>::FunctionsVec _ScriptableEx<_class>::m_vFuncs = _ScriptableEx<_class>::FunctionsVec(); \
		template<> IScriptObject *_ScriptableEx<_class>::m_pTemplateTable=NULL; \
		template<> IScriptObject *_ScriptableEx<_class>::m_pPropertiesTable=NULL; \
		template<> _ScriptableEx<_class>::PropertiesVec *_ScriptableEx<_class>::m_pvPropertiesVector=NULL;\
		assert(0);

		#else
		*/ //*_* by icandoit : 2005-06-22 15:37:03

#define _DECLARE_SCRIPTABLEEX(_class) IFunctionHandler * _ScriptableEx<_class>::m_pFunctionHandler=NULL; \
	_ScriptableEx<_class>::FunctionsVec _ScriptableEx<_class>::m_vFuncs; \
	IScriptObject *_ScriptableEx<_class>::m_pTemplateTable=NULL; \
	IScriptObject *_ScriptableEx<_class>::m_pPropertiesTable=NULL; \
	_ScriptableEx<_class>::PropertiesVec *_ScriptableEx<_class>::m_pvPropertiesVector=NULL;\
		struct __jScriptbinder##_class : public _ScriptableBinder	{	_class* m_pObj;tcstr m_szName;\
		__jScriptbinder##_class():m_szName(_T(#_class)){ jLuaObjList::push_back(this);	}\
		virtual void InitializeTemplate(jILua* pLua){ _class::InitializeTemplate(pLua);m_pObj = new _class; m_pObj->Init(pLua);}\
		virtual void ReleaseTemplate(){_class::ReleaseTemplate(); delete m_pObj;}\
		virtual cstr GetName(){ return m_szName;}\
		};__jScriptbinder##_class s___jScriptbinder##_class;\
		_class *jGET_LUAOBJ##_class(){ return s___jScriptbinder##_class.m_pObj;}

#define _DECLARE_SCRIPTABLEEX_MULTI_INSTANCE(_class) IFunctionHandler * _ScriptableEx<_class>::m_pFunctionHandler=NULL; \
	_ScriptableEx<_class>::FunctionsVec _ScriptableEx<_class>::m_vFuncs; \
	IScriptObject *_ScriptableEx<_class>::m_pTemplateTable=NULL; \
	IScriptObject *_ScriptableEx<_class>::m_pPropertiesTable=NULL; \
	_ScriptableEx<_class>::PropertiesVec *_ScriptableEx<_class>::m_pvPropertiesVector=NULL;\
		struct __jScriptbinder##_class : public _ScriptableBinder	{	tcstr m_szName;\
		__jScriptbinder##_class():m_szName(_T(#_class)){ jLuaObjList::push_back(this); }\
		virtual void InitializeTemplate(jILua* pLua){ _class::InitializeTemplate(pLua);}\
		virtual void ReleaseTemplate(){_class::ReleaseTemplate();}\
		virtual cstr GetName(){ return m_szName;}\
		};__jScriptbinder##_class s___jScriptbinder##_class;

		//#endif	//LINUX


#define CHECK_PARAMETERS_SS(_pSS,_n) \
	if (pH->GetParamCount() != _n) \
		{  \
		_pSS->RaiseError("%s: %d arguments passed, " #_n " expected)", __FUNCTION__, pH->GetParamCount()); \
		return pH->EndFunctionNull(); \
		} 

		// NOTE
		// The following RegExp replace macro was used to change to the new check_parameters
		// Find: CHECK_PARAMETERS(:Wh)*\([^,]+,(:Wh)*{[0-9]+}\)
		// Repl: CHECK_PARAMETERS(\1)

#ifndef __INTEL_COMPILER
#define CHECK_PARAMETERS(_n) CHECK_PARAMETERS_SS(nInterface::g_pjILua,_n)
#else
		// For Intel Compiler.
#define CHECK_PARAMETERS(_n) \
	if (pH->GetParamCount() != _n) \
		{  \
		nInterface::g_pjILua->RaiseError( ": %d arguments passed, " #_n " expected)", pH->GetParamCount()); \
		return pH->EndFunctionNull(); \
		} 
#endif

#define REG_FUNC(_class,_func) _class::RegisterFunction(nInterface::g_pjILua,#_func,&_class::_func);
#define REG_DERIVED_FUNC(_class,_func) RegisterFunction(nInterface::g_pjILua,#_func,&_class::_func);
#define SCRIPT_REG_CONST_SS(_pSS, _const) _pSS->SetGlobalValue(#_const, _const);
#define SCRIPT_REG_CONST(_const) SCRIPT_REG_CONST_SS(nInterface::g_pjILua,_const)
	}

}

/////////////////////////////////////////////////////////////////////////////
#endif //_j_asdflwf3d98sdSCRIPTABLE_H_

#ifndef DBCacheServer___DC_SERVERINFO_ACK__ 
#define DBCacheServer___DC_SERVERINFO_ACK__

#ifndef DBCacheServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_DBCacheServer(DBCacheServer);
jxDECL_DBCacheServer(DC_SERVERINFO_ACK);
#endif //DBCacheServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nDBCacheServer
{
	/*[[ SS2DC_ONLINE을 받았을때 보낸쪽의 sid=0일때	
다시 요청하여 받음.	
왜냐면 sid=0이라는예기는 아직 central이나 command로&#x0A;부터 sid를 발급받는중이기때문이다. ]]*/
	const int pk_DC_SERVERINFO_ACK = /*nMech::nNET::EProtocal_jINet_OGS_END+*/6000+6;
	/* jServerInfo si;*/
	
	struct S_DC_SERVERINFO_ACK;
	bool READ_DC_SERVERINFO_ACK(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_DC_SERVERINFO_ACK &param);
	struct S_DC_SERVERINFO_ACK
	{
		jServerInfo si;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_DBCacheServer


		#ifndef jNOT_USE_DebugPrint_DBCacheServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< DC_SERVERINFO_ACK > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("si"),si);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_DC_SERVERINFO_ACK(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_DBCacheServer
	
	inline bool READ_DC_SERVERINFO_ACK(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_DC_SERVERINFO_ACK &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.si);
		
		#ifndef jNOT_USE_DebugPrint_DBCacheServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("DC_SERVERINFO_ACK : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_DBCacheServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_DBCacheServer
	inline jPacket_Base WRITE_DC_SERVERINFO_ACK(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_DC_SERVERINFO_ACK &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.si);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_DC_SERVERINFO_ACK;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DC_SERVERINFO_ACK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DC_SERVERINFO_ACK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_DC_SERVERINFO_ACK(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const jServerInfo &_si)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_si);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_DC_SERVERINFO_ACK;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" DC_SERVERINFO_ACK :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" DC_SERVERINFO_ACK :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_DBCacheServer

}/*nDBCacheServer */ }/* nNET*/ } //nMech
#endif //DBCacheServer___DC_SERVERINFO_ACK__
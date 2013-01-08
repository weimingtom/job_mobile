
#ifndef ChannelServer___CH2X_GOTO_TOWN_MAP__ 
#define ChannelServer___CH2X_GOTO_TOWN_MAP__

#ifndef ChannelServer_jNOTUSE_PACKET_JXDEFINE
jxDECL_ChannelServer(ChannelServer);
jxDECL_ChannelServer(CH2X_GOTO_TOWN_MAP);
#endif //ChannelServer_jNOTUSE_PACKET_JXDEFINE

namespace nMech { namespace nNET { namespace nChannelServer
{
	const int pk_CH2X_GOTO_TOWN_MAP = /*nMech::nNET::EProtocal_jINet_OGS_END+*/2500+22;
	/* uint8 channelNo;*/
	
	struct S_CH2X_GOTO_TOWN_MAP;
	bool READ_CH2X_GOTO_TOWN_MAP(jIPacketSocket_IOCP* pS,uint16 data_size,BYTE *buffer, S_CH2X_GOTO_TOWN_MAP &param);
	struct S_CH2X_GOTO_TOWN_MAP
	{
		uint8 channelNo;
		#ifndef jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer
		#endif //jNOT_USE_PACKET_SET_GET_FUNC_ChannelServer


		#ifndef jNOT_USE_DebugPrint_ChannelServer
		void DebugPrint(bool isPrintAll)
		{
			using namespace nMech::nInterface;
			jLOG(_T("< CH2X_GOTO_TOWN_MAP > ="));
			if(!isPrintAll)return;
			jDebugPrint(_T("channelNo"),channelNo);
		}
		#endif //jNOT_USE_DebugPrint_
		void ReadPacket(jIPacketSocket_IOCP* pS,jPacket_Base* pk)
		{
			READ_CH2X_GOTO_TOWN_MAP(pS,pk->GetLen(),pk->buf,*this);
		}
	};
	#ifndef jNOT_USE_PACKET_READ_FUNC_ChannelServer
	
	inline bool READ_CH2X_GOTO_TOWN_MAP(jIPacketSocket_IOCP* pS,uint16 data_size , BYTE *buffer, S_CH2X_GOTO_TOWN_MAP &param)
	{
		try{
		nMech::nNET::nStream::jNetStreamRead st(buffer,data_size);

		nStream::Read(st,param.channelNo);
		
		#ifndef jNOT_USE_DebugPrint_ChannelServer
			if(pS)pS->DebugPrint();
			param.DebugPrint(true);
		#endif
		if(st.GetCurrPos()>data_size) throw _T("st.GetCurrPos()>data_size");
		}catch(tcstr sz){jWARN_T("CH2X_GOTO_TOWN_MAP : %s (data_size=%u " , sz,data_size); return false;}
		return true;
	}
	#endif //jNOT_USE_PACKET_READ_FUNC_ChannelServer

	#ifndef jNOT_USE_PACKET_WRITE_FUNC_ChannelServer
	inline jPacket_Base WRITE_CH2X_GOTO_TOWN_MAP(nNET::nStream::_jNetStreamWriteBufferBase &buffer, S_CH2X_GOTO_TOWN_MAP &param)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,param.channelNo);
			if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
			
			jPacket_Base pk; pk.num = pk_CH2X_GOTO_TOWN_MAP;
			pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" CH2X_GOTO_TOWN_MAP :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" CH2X_GOTO_TOWN_MAP :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};
	
	inline jPacket_Base WRITE_CH2X_GOTO_TOWN_MAP(nNET::nStream::_jNetStreamWriteBufferBase &buffer , const uint8 &_channelNo)
	{
		try{
			nMech::nNET::nStream::jNetStreamWrite st(buffer);
			nStream::Write(st,_channelNo);
		if(st.size()>st.capacity() ) throw _T("st.size()>st.capacity");
		
		jPacket_Base pk; pk.num = pk_CH2X_GOTO_TOWN_MAP;
		pk.buf=st.GetBuffer();	 pk.len=(jPacketNum_t)st.size();	return pk;
		}catch(tcstr sz){ jERROR(_T(" CH2X_GOTO_TOWN_MAP :data overflow: %s"),sz); }
		catch(nStream::jNetStreamWrite_error i){ jERROR(_T(" CH2X_GOTO_TOWN_MAP :overflow: (curr=%d,capa=%d,size=%d)"),i.currLen,i.capa , i.isize); }
		jPacket_Base pk;pk.buf=0;pk.len=0;pk.num=0;return pk;
	};

	#endif //jNOT_USE_PACKET_WRITE_FUNC_ChannelServer

}/*nChannelServer */ }/* nNET*/ } //nMech
#endif //ChannelServer___CH2X_GOTO_TOWN_MAP__
//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

// Option: light framework (CF/Silverlight) enabled
    
using nProtoGLrps;
   
// Generated from: PT_UserGateServer.proto
// Note: requires additional types generated from: gameLogic.proto
namespace nProtoUGrps
{
  [global::ProtoBuf.ProtoContract(Name=@"s_x2ug_echo")]
  public partial class s_x2ug_echo : global::ProtoBuf.IExtensible
  {
    public s_x2ug_echo() {}
    

    private int _type = default(int);
    [global::ProtoBuf.ProtoMember(1, IsRequired = false, Name=@"type", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int type
    {
      get { return _type; }
      set { _type = value; }
    }

    private string _msg = "";
    [global::ProtoBuf.ProtoMember(2, IsRequired = false, Name=@"msg", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue("")]
    public string msg
    {
      get { return _msg; }
      set { _msg = value; }
    }

    private int _client_time_msec = default(int);
    [global::ProtoBuf.ProtoMember(3, IsRequired = false, Name=@"client_time_msec", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int client_time_msec
    {
      get { return _client_time_msec; }
      set { _client_time_msec = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::ProtoBuf.ProtoContract(Name=@"s_ug2x_echo")]
  public partial class s_ug2x_echo : global::ProtoBuf.IExtensible
  {
    public s_ug2x_echo() {}
    

    private int _type = default(int);
    [global::ProtoBuf.ProtoMember(1, IsRequired = false, Name=@"type", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int type
    {
      get { return _type; }
      set { _type = value; }
    }

    private string _msg = "";
    [global::ProtoBuf.ProtoMember(2, IsRequired = false, Name=@"msg", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue("")]
    public string msg
    {
      get { return _msg; }
      set { _msg = value; }
    }

    private int _client_time_msec = default(int);
    [global::ProtoBuf.ProtoMember(3, IsRequired = false, Name=@"client_time_msec", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int client_time_msec
    {
      get { return _client_time_msec; }
      set { _client_time_msec = value; }
    }

    private long _ug_time_msec = default(long);
    [global::ProtoBuf.ProtoMember(4, IsRequired = false, Name=@"ug_time_msec", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(long))]
    public long ug_time_msec
    {
      get { return _ug_time_msec; }
      set { _ug_time_msec = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::ProtoBuf.ProtoContract(Name=@"UserGateServer_Client")]
  public partial class UserGateServer_Client : global::ProtoBuf.IExtensible
  {
    public UserGateServer_Client() {}
    
    private UserGateServer_Client.Type _type;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"type", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public UserGateServer_Client.Type type
    {
      get { return _type; }
      set { _type = value; }
    }

    private s_ug2x_echo _m_ug2x_echo = null;
    [global::ProtoBuf.ProtoMember(2, IsRequired = false, Name=@"m_ug2x_echo", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue(null)]
    public s_ug2x_echo m_ug2x_echo
    {
      get { return _m_ug2x_echo; }
      set { _m_ug2x_echo = value; }
    }
    [global::ProtoBuf.ProtoContract(Name=@"Type")]
    public enum Type
    {
            
      [global::ProtoBuf.ProtoEnum(Name=@"NONE", Value=1)]
      NONE = 1,
            
      [global::ProtoBuf.ProtoEnum(Name=@"ug2x_echo", Value=2)]
      ug2x_echo = 2
    }
  
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::ProtoBuf.ProtoContract(Name=@"Client_UserGateServer")]
  public partial class Client_UserGateServer : global::ProtoBuf.IExtensible
  {
    public Client_UserGateServer() {}
    
    private Client_UserGateServer.Type _type;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"type", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public Client_UserGateServer.Type type
    {
      get { return _type; }
      set { _type = value; }
    }

    private s_x2ug_echo _m_x2ug_echo = null;
    [global::ProtoBuf.ProtoMember(2, IsRequired = false, Name=@"m_x2ug_echo", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue(null)]
    public s_x2ug_echo m_x2ug_echo
    {
      get { return _m_x2ug_echo; }
      set { _m_x2ug_echo = value; }
    }
    [global::ProtoBuf.ProtoContract(Name=@"Type")]
    public enum Type
    {
            
      [global::ProtoBuf.ProtoEnum(Name=@"NONE", Value=1)]
      NONE = 1,
            
      [global::ProtoBuf.ProtoEnum(Name=@"x2ug_echo", Value=2)]
      x2ug_echo = 2
    }
  
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
}
//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

// Option: light framework (CF/Silverlight) enabled
    
// Generated from: gameLogic.proto
namespace nProtoGLrps
{
  [global::ProtoBuf.ProtoContract(Name=@"GameUserInfo")]
  public partial class GameUserInfo : global::ProtoBuf.IExtensible
  {
    public GameUserInfo() {}
    
    private GameInfo _game_info;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"game_info", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public GameInfo game_info
    {
      get { return _game_info; }
      set { _game_info = value; }
    }
    private byte[] _member_info;
    [global::ProtoBuf.ProtoMember(2, IsRequired = true, Name=@"member_info", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public byte[] member_info
    {
      get { return _member_info; }
      set { _member_info = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::ProtoBuf.ProtoContract(Name=@"GameInfo")]
  public partial class GameInfo : global::ProtoBuf.IExtensible
  {
    public GameInfo() {}
    
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::ProtoBuf.ProtoContract(Name=@"GameRoomInfo")]
  public partial class GameRoomInfo : global::ProtoBuf.IExtensible
  {
    public GameRoomInfo() {}
    
    private int _room_id;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"room_id", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public int room_id
    {
      get { return _room_id; }
      set { _room_id = value; }
    }

    private long _m_attack_user = default(long);
    [global::ProtoBuf.ProtoMember(3, IsRequired = false, Name=@"m_attack_user", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(long))]
    public long m_attack_user
    {
      get { return _m_attack_user; }
      set { _m_attack_user = value; }
    }

    private int _m_round_count = default(int);
    [global::ProtoBuf.ProtoMember(4, IsRequired = false, Name=@"m_round_count", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    [global::System.ComponentModel.DefaultValue(default(int))]
    public int m_round_count
    {
      get { return _m_round_count; }
      set { _m_round_count = value; }
    }

    private bool _m_is_auto_play = default(bool);
    [global::ProtoBuf.ProtoMember(7, IsRequired = false, Name=@"m_is_auto_play", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue(default(bool))]
    public bool m_is_auto_play
    {
      get { return _m_is_auto_play; }
      set { _m_is_auto_play = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::ProtoBuf.ProtoContract(Name=@"GLReqGameProtocol")]
  public partial class GLReqGameProtocol : global::ProtoBuf.IExtensible
  {
    public GLReqGameProtocol() {}
    
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::ProtoBuf.ProtoContract(Name=@"GLAnsGameProtocol")]
  public partial class GLAnsGameProtocol : global::ProtoBuf.IExtensible
  {
    public GLAnsGameProtocol() {}
    
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
}
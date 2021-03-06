/** ------------------------------------------------------------------------------ */
/**  <auto-generated> */
/**      This code was generated by a tool. */
/**  */
/**      Changes to this file may cause incorrect behavior and will be lost if */
/**      the code is regenerated. */
/**  </auto-generated> */
/** ------------------------------------------------------------------------------ */

/**  Option: light framework (CF/Silverlight) enabled */
    
/**  Generated from: db.proto */
namespace MSG.Protocol
{
  [global::ProtoBuf.ProtoContract(Name=@"DBIn")]
  public partial class DBIn : global::ProtoBuf.IExtensible
  {
    public DBIn() {}
    
    private DBIn.Type _type;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"type", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public DBIn.Type type
    {
      get { return _type; }
      set { _type = value; }
    }
    private string _val;
    [global::ProtoBuf.ProtoMember(2, IsRequired = true, Name=@"val", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public string val
    {
      get { return _val; }
      set { _val = value; }
    }
    [global::ProtoBuf.ProtoContract(Name=@"Type")]
    public enum Type
    {
            
      [global::ProtoBuf.ProtoEnum(Name=@"INT", Value=1)]
      INT = 1,
            
      [global::ProtoBuf.ProtoEnum(Name=@"INT64", Value=2)]
      INT64 = 2,
            
      [global::ProtoBuf.ProtoEnum(Name=@"STR", Value=3)]
      STR = 3
    }
  
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::ProtoBuf.ProtoContract(Name=@"ReqDB")]
  public partial class ReqDB : global::ProtoBuf.IExtensible
  {
    public ReqDB() {}
    
    private int _seq;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"seq", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public int seq
    {
      get { return _seq; }
      set { _seq = value; }
    }
    private string _query;
    [global::ProtoBuf.ProtoMember(2, IsRequired = true, Name=@"query", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public string query
    {
      get { return _query; }
      set { _query = value; }
    }
    private readonly global::System.Collections.Generic.List<DBIn> _params = new global::System.Collections.Generic.List<DBIn>();
    [global::ProtoBuf.ProtoMember(3, Name=@"params", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public global::System.Collections.Generic.List<DBIn> @params
    {
      get { return _params; }
    }
  

    private byte[] _options = null;
    [global::ProtoBuf.ProtoMember(4, IsRequired = false, Name=@"options", DataFormat = global::ProtoBuf.DataFormat.Default)]
    [global::System.ComponentModel.DefaultValue(null)]
    public byte[] options
    {
      get { return _options; }
      set { _options = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
  [global::ProtoBuf.ProtoContract(Name=@"AnsDB")]
  public partial class AnsDB : global::ProtoBuf.IExtensible
  {
    public AnsDB() {}
    
    private int _seq;
    [global::ProtoBuf.ProtoMember(1, IsRequired = true, Name=@"seq", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public int seq
    {
      get { return _seq; }
      set { _seq = value; }
    }
    private string _query;
    [global::ProtoBuf.ProtoMember(2, IsRequired = true, Name=@"query", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public string query
    {
      get { return _query; }
      set { _query = value; }
    }
    private int _retCode;
    [global::ProtoBuf.ProtoMember(3, IsRequired = true, Name=@"retCode", DataFormat = global::ProtoBuf.DataFormat.TwosComplement)]
    public int retCode
    {
      get { return _retCode; }
      set { _retCode = value; }
    }
    private byte[] _result;
    [global::ProtoBuf.ProtoMember(4, IsRequired = true, Name=@"result", DataFormat = global::ProtoBuf.DataFormat.Default)]
    public byte[] result
    {
      get { return _result; }
      set { _result = value; }
    }
    private global::ProtoBuf.IExtension extensionObject;
    global::ProtoBuf.IExtension global::ProtoBuf.IExtensible.GetExtensionObject(bool createIfMissing)
      { return global::ProtoBuf.Extensible.GetExtensionObject(ref extensionObject, createIfMissing); }
  }
  
}
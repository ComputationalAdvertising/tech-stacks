// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: instance.proto

package org.openmit.entry;

/**
 * Protobuf type {@code openmit.pb.Feature}
 */
public  final class Feature extends
    com.google.protobuf.GeneratedMessageV3 implements
    // @@protoc_insertion_point(message_implements:openmit.pb.Feature)
    FeatureOrBuilder {
private static final long serialVersionUID = 0L;
  // Use Feature.newBuilder() to construct.
  private Feature(com.google.protobuf.GeneratedMessageV3.Builder<?> builder) {
    super(builder);
  }
  private Feature() {
    tag_ = 0L;
    id_ = 0L;
    val_ = 0F;
    weight_ = 0F;
    type_ = "";
  }

  @java.lang.Override
  public final com.google.protobuf.UnknownFieldSet
  getUnknownFields() {
    return this.unknownFields;
  }
  private Feature(
      com.google.protobuf.CodedInputStream input,
      com.google.protobuf.ExtensionRegistryLite extensionRegistry)
      throws com.google.protobuf.InvalidProtocolBufferException {
    this();
    if (extensionRegistry == null) {
      throw new java.lang.NullPointerException();
    }
    int mutable_bitField0_ = 0;
    com.google.protobuf.UnknownFieldSet.Builder unknownFields =
        com.google.protobuf.UnknownFieldSet.newBuilder();
    try {
      boolean done = false;
      while (!done) {
        int tag = input.readTag();
        switch (tag) {
          case 0:
            done = true;
            break;
          default: {
            if (!parseUnknownFieldProto3(
                input, unknownFields, extensionRegistry, tag)) {
              done = true;
            }
            break;
          }
          case 8: {

            tag_ = input.readUInt64();
            break;
          }
          case 16: {

            id_ = input.readUInt64();
            break;
          }
          case 29: {

            val_ = input.readFloat();
            break;
          }
          case 37: {

            weight_ = input.readFloat();
            break;
          }
          case 42: {
            java.lang.String s = input.readStringRequireUtf8();

            type_ = s;
            break;
          }
        }
      }
    } catch (com.google.protobuf.InvalidProtocolBufferException e) {
      throw e.setUnfinishedMessage(this);
    } catch (java.io.IOException e) {
      throw new com.google.protobuf.InvalidProtocolBufferException(
          e).setUnfinishedMessage(this);
    } finally {
      this.unknownFields = unknownFields.build();
      makeExtensionsImmutable();
    }
  }
  public static final com.google.protobuf.Descriptors.Descriptor
      getDescriptor() {
    return org.openmit.entry.InstanceProtos.internal_static_openmit_pb_Feature_descriptor;
  }

  protected com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
      internalGetFieldAccessorTable() {
    return org.openmit.entry.InstanceProtos.internal_static_openmit_pb_Feature_fieldAccessorTable
        .ensureFieldAccessorsInitialized(
            org.openmit.entry.Feature.class, org.openmit.entry.Feature.Builder.class);
  }

  public static final int TAG_FIELD_NUMBER = 1;
  private long tag_;
  /**
   * <code>uint64 tag = 1;</code>
   */
  public long getTag() {
    return tag_;
  }

  public static final int ID_FIELD_NUMBER = 2;
  private long id_;
  /**
   * <code>uint64 id = 2;</code>
   */
  public long getId() {
    return id_;
  }

  public static final int VAL_FIELD_NUMBER = 3;
  private float val_;
  /**
   * <code>float val = 3;</code>
   */
  public float getVal() {
    return val_;
  }

  public static final int WEIGHT_FIELD_NUMBER = 4;
  private float weight_;
  /**
   * <code>float weight = 4;</code>
   */
  public float getWeight() {
    return weight_;
  }

  public static final int TYPE_FIELD_NUMBER = 5;
  private volatile java.lang.Object type_;
  /**
   * <code>string type = 5;</code>
   */
  public java.lang.String getType() {
    java.lang.Object ref = type_;
    if (ref instanceof java.lang.String) {
      return (java.lang.String) ref;
    } else {
      com.google.protobuf.ByteString bs = 
          (com.google.protobuf.ByteString) ref;
      java.lang.String s = bs.toStringUtf8();
      type_ = s;
      return s;
    }
  }
  /**
   * <code>string type = 5;</code>
   */
  public com.google.protobuf.ByteString
      getTypeBytes() {
    java.lang.Object ref = type_;
    if (ref instanceof java.lang.String) {
      com.google.protobuf.ByteString b = 
          com.google.protobuf.ByteString.copyFromUtf8(
              (java.lang.String) ref);
      type_ = b;
      return b;
    } else {
      return (com.google.protobuf.ByteString) ref;
    }
  }

  private byte memoizedIsInitialized = -1;
  public final boolean isInitialized() {
    byte isInitialized = memoizedIsInitialized;
    if (isInitialized == 1) return true;
    if (isInitialized == 0) return false;

    memoizedIsInitialized = 1;
    return true;
  }

  public void writeTo(com.google.protobuf.CodedOutputStream output)
                      throws java.io.IOException {
    if (tag_ != 0L) {
      output.writeUInt64(1, tag_);
    }
    if (id_ != 0L) {
      output.writeUInt64(2, id_);
    }
    if (val_ != 0F) {
      output.writeFloat(3, val_);
    }
    if (weight_ != 0F) {
      output.writeFloat(4, weight_);
    }
    if (!getTypeBytes().isEmpty()) {
      com.google.protobuf.GeneratedMessageV3.writeString(output, 5, type_);
    }
    unknownFields.writeTo(output);
  }

  public int getSerializedSize() {
    int size = memoizedSize;
    if (size != -1) return size;

    size = 0;
    if (tag_ != 0L) {
      size += com.google.protobuf.CodedOutputStream
        .computeUInt64Size(1, tag_);
    }
    if (id_ != 0L) {
      size += com.google.protobuf.CodedOutputStream
        .computeUInt64Size(2, id_);
    }
    if (val_ != 0F) {
      size += com.google.protobuf.CodedOutputStream
        .computeFloatSize(3, val_);
    }
    if (weight_ != 0F) {
      size += com.google.protobuf.CodedOutputStream
        .computeFloatSize(4, weight_);
    }
    if (!getTypeBytes().isEmpty()) {
      size += com.google.protobuf.GeneratedMessageV3.computeStringSize(5, type_);
    }
    size += unknownFields.getSerializedSize();
    memoizedSize = size;
    return size;
  }

  @java.lang.Override
  public boolean equals(final java.lang.Object obj) {
    if (obj == this) {
     return true;
    }
    if (!(obj instanceof org.openmit.entry.Feature)) {
      return super.equals(obj);
    }
    org.openmit.entry.Feature other = (org.openmit.entry.Feature) obj;

    boolean result = true;
    result = result && (getTag()
        == other.getTag());
    result = result && (getId()
        == other.getId());
    result = result && (
        java.lang.Float.floatToIntBits(getVal())
        == java.lang.Float.floatToIntBits(
            other.getVal()));
    result = result && (
        java.lang.Float.floatToIntBits(getWeight())
        == java.lang.Float.floatToIntBits(
            other.getWeight()));
    result = result && getType()
        .equals(other.getType());
    result = result && unknownFields.equals(other.unknownFields);
    return result;
  }

  @java.lang.Override
  public int hashCode() {
    if (memoizedHashCode != 0) {
      return memoizedHashCode;
    }
    int hash = 41;
    hash = (19 * hash) + getDescriptor().hashCode();
    hash = (37 * hash) + TAG_FIELD_NUMBER;
    hash = (53 * hash) + com.google.protobuf.Internal.hashLong(
        getTag());
    hash = (37 * hash) + ID_FIELD_NUMBER;
    hash = (53 * hash) + com.google.protobuf.Internal.hashLong(
        getId());
    hash = (37 * hash) + VAL_FIELD_NUMBER;
    hash = (53 * hash) + java.lang.Float.floatToIntBits(
        getVal());
    hash = (37 * hash) + WEIGHT_FIELD_NUMBER;
    hash = (53 * hash) + java.lang.Float.floatToIntBits(
        getWeight());
    hash = (37 * hash) + TYPE_FIELD_NUMBER;
    hash = (53 * hash) + getType().hashCode();
    hash = (29 * hash) + unknownFields.hashCode();
    memoizedHashCode = hash;
    return hash;
  }

  public static org.openmit.entry.Feature parseFrom(
      java.nio.ByteBuffer data)
      throws com.google.protobuf.InvalidProtocolBufferException {
    return PARSER.parseFrom(data);
  }
  public static org.openmit.entry.Feature parseFrom(
      java.nio.ByteBuffer data,
      com.google.protobuf.ExtensionRegistryLite extensionRegistry)
      throws com.google.protobuf.InvalidProtocolBufferException {
    return PARSER.parseFrom(data, extensionRegistry);
  }
  public static org.openmit.entry.Feature parseFrom(
      com.google.protobuf.ByteString data)
      throws com.google.protobuf.InvalidProtocolBufferException {
    return PARSER.parseFrom(data);
  }
  public static org.openmit.entry.Feature parseFrom(
      com.google.protobuf.ByteString data,
      com.google.protobuf.ExtensionRegistryLite extensionRegistry)
      throws com.google.protobuf.InvalidProtocolBufferException {
    return PARSER.parseFrom(data, extensionRegistry);
  }
  public static org.openmit.entry.Feature parseFrom(byte[] data)
      throws com.google.protobuf.InvalidProtocolBufferException {
    return PARSER.parseFrom(data);
  }
  public static org.openmit.entry.Feature parseFrom(
      byte[] data,
      com.google.protobuf.ExtensionRegistryLite extensionRegistry)
      throws com.google.protobuf.InvalidProtocolBufferException {
    return PARSER.parseFrom(data, extensionRegistry);
  }
  public static org.openmit.entry.Feature parseFrom(java.io.InputStream input)
      throws java.io.IOException {
    return com.google.protobuf.GeneratedMessageV3
        .parseWithIOException(PARSER, input);
  }
  public static org.openmit.entry.Feature parseFrom(
      java.io.InputStream input,
      com.google.protobuf.ExtensionRegistryLite extensionRegistry)
      throws java.io.IOException {
    return com.google.protobuf.GeneratedMessageV3
        .parseWithIOException(PARSER, input, extensionRegistry);
  }
  public static org.openmit.entry.Feature parseDelimitedFrom(java.io.InputStream input)
      throws java.io.IOException {
    return com.google.protobuf.GeneratedMessageV3
        .parseDelimitedWithIOException(PARSER, input);
  }
  public static org.openmit.entry.Feature parseDelimitedFrom(
      java.io.InputStream input,
      com.google.protobuf.ExtensionRegistryLite extensionRegistry)
      throws java.io.IOException {
    return com.google.protobuf.GeneratedMessageV3
        .parseDelimitedWithIOException(PARSER, input, extensionRegistry);
  }
  public static org.openmit.entry.Feature parseFrom(
      com.google.protobuf.CodedInputStream input)
      throws java.io.IOException {
    return com.google.protobuf.GeneratedMessageV3
        .parseWithIOException(PARSER, input);
  }
  public static org.openmit.entry.Feature parseFrom(
      com.google.protobuf.CodedInputStream input,
      com.google.protobuf.ExtensionRegistryLite extensionRegistry)
      throws java.io.IOException {
    return com.google.protobuf.GeneratedMessageV3
        .parseWithIOException(PARSER, input, extensionRegistry);
  }

  public Builder newBuilderForType() { return newBuilder(); }
  public static Builder newBuilder() {
    return DEFAULT_INSTANCE.toBuilder();
  }
  public static Builder newBuilder(org.openmit.entry.Feature prototype) {
    return DEFAULT_INSTANCE.toBuilder().mergeFrom(prototype);
  }
  public Builder toBuilder() {
    return this == DEFAULT_INSTANCE
        ? new Builder() : new Builder().mergeFrom(this);
  }

  @java.lang.Override
  protected Builder newBuilderForType(
      com.google.protobuf.GeneratedMessageV3.BuilderParent parent) {
    Builder builder = new Builder(parent);
    return builder;
  }
  /**
   * Protobuf type {@code openmit.pb.Feature}
   */
  public static final class Builder extends
      com.google.protobuf.GeneratedMessageV3.Builder<Builder> implements
      // @@protoc_insertion_point(builder_implements:openmit.pb.Feature)
      org.openmit.entry.FeatureOrBuilder {
    public static final com.google.protobuf.Descriptors.Descriptor
        getDescriptor() {
      return org.openmit.entry.InstanceProtos.internal_static_openmit_pb_Feature_descriptor;
    }

    protected com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
        internalGetFieldAccessorTable() {
      return org.openmit.entry.InstanceProtos.internal_static_openmit_pb_Feature_fieldAccessorTable
          .ensureFieldAccessorsInitialized(
              org.openmit.entry.Feature.class, org.openmit.entry.Feature.Builder.class);
    }

    // Construct using org.openmit.entry.Feature.newBuilder()
    private Builder() {
      maybeForceBuilderInitialization();
    }

    private Builder(
        com.google.protobuf.GeneratedMessageV3.BuilderParent parent) {
      super(parent);
      maybeForceBuilderInitialization();
    }
    private void maybeForceBuilderInitialization() {
      if (com.google.protobuf.GeneratedMessageV3
              .alwaysUseFieldBuilders) {
      }
    }
    public Builder clear() {
      super.clear();
      tag_ = 0L;

      id_ = 0L;

      val_ = 0F;

      weight_ = 0F;

      type_ = "";

      return this;
    }

    public com.google.protobuf.Descriptors.Descriptor
        getDescriptorForType() {
      return org.openmit.entry.InstanceProtos.internal_static_openmit_pb_Feature_descriptor;
    }

    public org.openmit.entry.Feature getDefaultInstanceForType() {
      return org.openmit.entry.Feature.getDefaultInstance();
    }

    public org.openmit.entry.Feature build() {
      org.openmit.entry.Feature result = buildPartial();
      if (!result.isInitialized()) {
        throw newUninitializedMessageException(result);
      }
      return result;
    }

    public org.openmit.entry.Feature buildPartial() {
      org.openmit.entry.Feature result = new org.openmit.entry.Feature(this);
      result.tag_ = tag_;
      result.id_ = id_;
      result.val_ = val_;
      result.weight_ = weight_;
      result.type_ = type_;
      onBuilt();
      return result;
    }

    public Builder clone() {
      return (Builder) super.clone();
    }
    public Builder setField(
        com.google.protobuf.Descriptors.FieldDescriptor field,
        java.lang.Object value) {
      return (Builder) super.setField(field, value);
    }
    public Builder clearField(
        com.google.protobuf.Descriptors.FieldDescriptor field) {
      return (Builder) super.clearField(field);
    }
    public Builder clearOneof(
        com.google.protobuf.Descriptors.OneofDescriptor oneof) {
      return (Builder) super.clearOneof(oneof);
    }
    public Builder setRepeatedField(
        com.google.protobuf.Descriptors.FieldDescriptor field,
        int index, java.lang.Object value) {
      return (Builder) super.setRepeatedField(field, index, value);
    }
    public Builder addRepeatedField(
        com.google.protobuf.Descriptors.FieldDescriptor field,
        java.lang.Object value) {
      return (Builder) super.addRepeatedField(field, value);
    }
    public Builder mergeFrom(com.google.protobuf.Message other) {
      if (other instanceof org.openmit.entry.Feature) {
        return mergeFrom((org.openmit.entry.Feature)other);
      } else {
        super.mergeFrom(other);
        return this;
      }
    }

    public Builder mergeFrom(org.openmit.entry.Feature other) {
      if (other == org.openmit.entry.Feature.getDefaultInstance()) return this;
      if (other.getTag() != 0L) {
        setTag(other.getTag());
      }
      if (other.getId() != 0L) {
        setId(other.getId());
      }
      if (other.getVal() != 0F) {
        setVal(other.getVal());
      }
      if (other.getWeight() != 0F) {
        setWeight(other.getWeight());
      }
      if (!other.getType().isEmpty()) {
        type_ = other.type_;
        onChanged();
      }
      this.mergeUnknownFields(other.unknownFields);
      onChanged();
      return this;
    }

    public final boolean isInitialized() {
      return true;
    }

    public Builder mergeFrom(
        com.google.protobuf.CodedInputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws java.io.IOException {
      org.openmit.entry.Feature parsedMessage = null;
      try {
        parsedMessage = PARSER.parsePartialFrom(input, extensionRegistry);
      } catch (com.google.protobuf.InvalidProtocolBufferException e) {
        parsedMessage = (org.openmit.entry.Feature) e.getUnfinishedMessage();
        throw e.unwrapIOException();
      } finally {
        if (parsedMessage != null) {
          mergeFrom(parsedMessage);
        }
      }
      return this;
    }

    private long tag_ ;
    /**
     * <code>uint64 tag = 1;</code>
     */
    public long getTag() {
      return tag_;
    }
    /**
     * <code>uint64 tag = 1;</code>
     */
    public Builder setTag(long value) {
      
      tag_ = value;
      onChanged();
      return this;
    }
    /**
     * <code>uint64 tag = 1;</code>
     */
    public Builder clearTag() {
      
      tag_ = 0L;
      onChanged();
      return this;
    }

    private long id_ ;
    /**
     * <code>uint64 id = 2;</code>
     */
    public long getId() {
      return id_;
    }
    /**
     * <code>uint64 id = 2;</code>
     */
    public Builder setId(long value) {
      
      id_ = value;
      onChanged();
      return this;
    }
    /**
     * <code>uint64 id = 2;</code>
     */
    public Builder clearId() {
      
      id_ = 0L;
      onChanged();
      return this;
    }

    private float val_ ;
    /**
     * <code>float val = 3;</code>
     */
    public float getVal() {
      return val_;
    }
    /**
     * <code>float val = 3;</code>
     */
    public Builder setVal(float value) {
      
      val_ = value;
      onChanged();
      return this;
    }
    /**
     * <code>float val = 3;</code>
     */
    public Builder clearVal() {
      
      val_ = 0F;
      onChanged();
      return this;
    }

    private float weight_ ;
    /**
     * <code>float weight = 4;</code>
     */
    public float getWeight() {
      return weight_;
    }
    /**
     * <code>float weight = 4;</code>
     */
    public Builder setWeight(float value) {
      
      weight_ = value;
      onChanged();
      return this;
    }
    /**
     * <code>float weight = 4;</code>
     */
    public Builder clearWeight() {
      
      weight_ = 0F;
      onChanged();
      return this;
    }

    private java.lang.Object type_ = "";
    /**
     * <code>string type = 5;</code>
     */
    public java.lang.String getType() {
      java.lang.Object ref = type_;
      if (!(ref instanceof java.lang.String)) {
        com.google.protobuf.ByteString bs =
            (com.google.protobuf.ByteString) ref;
        java.lang.String s = bs.toStringUtf8();
        type_ = s;
        return s;
      } else {
        return (java.lang.String) ref;
      }
    }
    /**
     * <code>string type = 5;</code>
     */
    public com.google.protobuf.ByteString
        getTypeBytes() {
      java.lang.Object ref = type_;
      if (ref instanceof String) {
        com.google.protobuf.ByteString b = 
            com.google.protobuf.ByteString.copyFromUtf8(
                (java.lang.String) ref);
        type_ = b;
        return b;
      } else {
        return (com.google.protobuf.ByteString) ref;
      }
    }
    /**
     * <code>string type = 5;</code>
     */
    public Builder setType(
        java.lang.String value) {
      if (value == null) {
    throw new NullPointerException();
  }
  
      type_ = value;
      onChanged();
      return this;
    }
    /**
     * <code>string type = 5;</code>
     */
    public Builder clearType() {
      
      type_ = getDefaultInstance().getType();
      onChanged();
      return this;
    }
    /**
     * <code>string type = 5;</code>
     */
    public Builder setTypeBytes(
        com.google.protobuf.ByteString value) {
      if (value == null) {
    throw new NullPointerException();
  }
  checkByteStringIsUtf8(value);
      
      type_ = value;
      onChanged();
      return this;
    }
    public final Builder setUnknownFields(
        final com.google.protobuf.UnknownFieldSet unknownFields) {
      return super.setUnknownFieldsProto3(unknownFields);
    }

    public final Builder mergeUnknownFields(
        final com.google.protobuf.UnknownFieldSet unknownFields) {
      return super.mergeUnknownFields(unknownFields);
    }


    // @@protoc_insertion_point(builder_scope:openmit.pb.Feature)
  }

  // @@protoc_insertion_point(class_scope:openmit.pb.Feature)
  private static final org.openmit.entry.Feature DEFAULT_INSTANCE;
  static {
    DEFAULT_INSTANCE = new org.openmit.entry.Feature();
  }

  public static org.openmit.entry.Feature getDefaultInstance() {
    return DEFAULT_INSTANCE;
  }

  private static final com.google.protobuf.Parser<Feature>
      PARSER = new com.google.protobuf.AbstractParser<Feature>() {
    public Feature parsePartialFrom(
        com.google.protobuf.CodedInputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return new Feature(input, extensionRegistry);
    }
  };

  public static com.google.protobuf.Parser<Feature> parser() {
    return PARSER;
  }

  @java.lang.Override
  public com.google.protobuf.Parser<Feature> getParserForType() {
    return PARSER;
  }

  public org.openmit.entry.Feature getDefaultInstanceForType() {
    return DEFAULT_INSTANCE;
  }

}


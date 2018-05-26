// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: instance.proto

package org.openmit.entry;

/**
 * Protobuf type {@code openmit.pb.Instance}
 */
public  final class Instance extends
    com.google.protobuf.GeneratedMessageV3 implements
    // @@protoc_insertion_point(message_implements:openmit.pb.Instance)
    InstanceOrBuilder {
private static final long serialVersionUID = 0L;
  // Use Instance.newBuilder() to construct.
  private Instance(com.google.protobuf.GeneratedMessageV3.Builder<?> builder) {
    super(builder);
  }
  private Instance() {
    instId_ = 0L;
    instWeight_ = 0F;
    seqId_ = 0;
  }

  @java.lang.Override
  public final com.google.protobuf.UnknownFieldSet
  getUnknownFields() {
    return this.unknownFields;
  }
  private Instance(
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

            instId_ = input.readUInt64();
            break;
          }
          case 21: {

            instWeight_ = input.readFloat();
            break;
          }
          case 26: {
            org.openmit.entry.Label.Builder subBuilder = null;
            if (label_ != null) {
              subBuilder = label_.toBuilder();
            }
            label_ = input.readMessage(org.openmit.entry.Label.parser(), extensionRegistry);
            if (subBuilder != null) {
              subBuilder.mergeFrom(label_);
              label_ = subBuilder.buildPartial();
            }

            break;
          }
          case 34: {
            org.openmit.entry.Features.Builder subBuilder = null;
            if (features_ != null) {
              subBuilder = features_.toBuilder();
            }
            features_ = input.readMessage(org.openmit.entry.Features.parser(), extensionRegistry);
            if (subBuilder != null) {
              subBuilder.mergeFrom(features_);
              features_ = subBuilder.buildPartial();
            }

            break;
          }
          case 40: {

            seqId_ = input.readUInt32();
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
    return org.openmit.entry.InstanceProtos.internal_static_openmit_pb_Instance_descriptor;
  }

  protected com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
      internalGetFieldAccessorTable() {
    return org.openmit.entry.InstanceProtos.internal_static_openmit_pb_Instance_fieldAccessorTable
        .ensureFieldAccessorsInitialized(
            org.openmit.entry.Instance.class, org.openmit.entry.Instance.Builder.class);
  }

  public static final int INST_ID_FIELD_NUMBER = 1;
  private long instId_;
  /**
   * <code>uint64 inst_id = 1;</code>
   */
  public long getInstId() {
    return instId_;
  }

  public static final int INST_WEIGHT_FIELD_NUMBER = 2;
  private float instWeight_;
  /**
   * <code>float inst_weight = 2;</code>
   */
  public float getInstWeight() {
    return instWeight_;
  }

  public static final int LABEL_FIELD_NUMBER = 3;
  private org.openmit.entry.Label label_;
  /**
   * <code>.openmit.pb.Label label = 3;</code>
   */
  public boolean hasLabel() {
    return label_ != null;
  }
  /**
   * <code>.openmit.pb.Label label = 3;</code>
   */
  public org.openmit.entry.Label getLabel() {
    return label_ == null ? org.openmit.entry.Label.getDefaultInstance() : label_;
  }
  /**
   * <code>.openmit.pb.Label label = 3;</code>
   */
  public org.openmit.entry.LabelOrBuilder getLabelOrBuilder() {
    return getLabel();
  }

  public static final int FEATURES_FIELD_NUMBER = 4;
  private org.openmit.entry.Features features_;
  /**
   * <code>.openmit.pb.Features features = 4;</code>
   */
  public boolean hasFeatures() {
    return features_ != null;
  }
  /**
   * <code>.openmit.pb.Features features = 4;</code>
   */
  public org.openmit.entry.Features getFeatures() {
    return features_ == null ? org.openmit.entry.Features.getDefaultInstance() : features_;
  }
  /**
   * <code>.openmit.pb.Features features = 4;</code>
   */
  public org.openmit.entry.FeaturesOrBuilder getFeaturesOrBuilder() {
    return getFeatures();
  }

  public static final int SEQ_ID_FIELD_NUMBER = 5;
  private int seqId_;
  /**
   * <code>uint32 seq_id = 5;</code>
   */
  public int getSeqId() {
    return seqId_;
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
    if (instId_ != 0L) {
      output.writeUInt64(1, instId_);
    }
    if (instWeight_ != 0F) {
      output.writeFloat(2, instWeight_);
    }
    if (label_ != null) {
      output.writeMessage(3, getLabel());
    }
    if (features_ != null) {
      output.writeMessage(4, getFeatures());
    }
    if (seqId_ != 0) {
      output.writeUInt32(5, seqId_);
    }
    unknownFields.writeTo(output);
  }

  public int getSerializedSize() {
    int size = memoizedSize;
    if (size != -1) return size;

    size = 0;
    if (instId_ != 0L) {
      size += com.google.protobuf.CodedOutputStream
        .computeUInt64Size(1, instId_);
    }
    if (instWeight_ != 0F) {
      size += com.google.protobuf.CodedOutputStream
        .computeFloatSize(2, instWeight_);
    }
    if (label_ != null) {
      size += com.google.protobuf.CodedOutputStream
        .computeMessageSize(3, getLabel());
    }
    if (features_ != null) {
      size += com.google.protobuf.CodedOutputStream
        .computeMessageSize(4, getFeatures());
    }
    if (seqId_ != 0) {
      size += com.google.protobuf.CodedOutputStream
        .computeUInt32Size(5, seqId_);
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
    if (!(obj instanceof org.openmit.entry.Instance)) {
      return super.equals(obj);
    }
    org.openmit.entry.Instance other = (org.openmit.entry.Instance) obj;

    boolean result = true;
    result = result && (getInstId()
        == other.getInstId());
    result = result && (
        java.lang.Float.floatToIntBits(getInstWeight())
        == java.lang.Float.floatToIntBits(
            other.getInstWeight()));
    result = result && (hasLabel() == other.hasLabel());
    if (hasLabel()) {
      result = result && getLabel()
          .equals(other.getLabel());
    }
    result = result && (hasFeatures() == other.hasFeatures());
    if (hasFeatures()) {
      result = result && getFeatures()
          .equals(other.getFeatures());
    }
    result = result && (getSeqId()
        == other.getSeqId());
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
    hash = (37 * hash) + INST_ID_FIELD_NUMBER;
    hash = (53 * hash) + com.google.protobuf.Internal.hashLong(
        getInstId());
    hash = (37 * hash) + INST_WEIGHT_FIELD_NUMBER;
    hash = (53 * hash) + java.lang.Float.floatToIntBits(
        getInstWeight());
    if (hasLabel()) {
      hash = (37 * hash) + LABEL_FIELD_NUMBER;
      hash = (53 * hash) + getLabel().hashCode();
    }
    if (hasFeatures()) {
      hash = (37 * hash) + FEATURES_FIELD_NUMBER;
      hash = (53 * hash) + getFeatures().hashCode();
    }
    hash = (37 * hash) + SEQ_ID_FIELD_NUMBER;
    hash = (53 * hash) + getSeqId();
    hash = (29 * hash) + unknownFields.hashCode();
    memoizedHashCode = hash;
    return hash;
  }

  public static org.openmit.entry.Instance parseFrom(
      java.nio.ByteBuffer data)
      throws com.google.protobuf.InvalidProtocolBufferException {
    return PARSER.parseFrom(data);
  }
  public static org.openmit.entry.Instance parseFrom(
      java.nio.ByteBuffer data,
      com.google.protobuf.ExtensionRegistryLite extensionRegistry)
      throws com.google.protobuf.InvalidProtocolBufferException {
    return PARSER.parseFrom(data, extensionRegistry);
  }
  public static org.openmit.entry.Instance parseFrom(
      com.google.protobuf.ByteString data)
      throws com.google.protobuf.InvalidProtocolBufferException {
    return PARSER.parseFrom(data);
  }
  public static org.openmit.entry.Instance parseFrom(
      com.google.protobuf.ByteString data,
      com.google.protobuf.ExtensionRegistryLite extensionRegistry)
      throws com.google.protobuf.InvalidProtocolBufferException {
    return PARSER.parseFrom(data, extensionRegistry);
  }
  public static org.openmit.entry.Instance parseFrom(byte[] data)
      throws com.google.protobuf.InvalidProtocolBufferException {
    return PARSER.parseFrom(data);
  }
  public static org.openmit.entry.Instance parseFrom(
      byte[] data,
      com.google.protobuf.ExtensionRegistryLite extensionRegistry)
      throws com.google.protobuf.InvalidProtocolBufferException {
    return PARSER.parseFrom(data, extensionRegistry);
  }
  public static org.openmit.entry.Instance parseFrom(java.io.InputStream input)
      throws java.io.IOException {
    return com.google.protobuf.GeneratedMessageV3
        .parseWithIOException(PARSER, input);
  }
  public static org.openmit.entry.Instance parseFrom(
      java.io.InputStream input,
      com.google.protobuf.ExtensionRegistryLite extensionRegistry)
      throws java.io.IOException {
    return com.google.protobuf.GeneratedMessageV3
        .parseWithIOException(PARSER, input, extensionRegistry);
  }
  public static org.openmit.entry.Instance parseDelimitedFrom(java.io.InputStream input)
      throws java.io.IOException {
    return com.google.protobuf.GeneratedMessageV3
        .parseDelimitedWithIOException(PARSER, input);
  }
  public static org.openmit.entry.Instance parseDelimitedFrom(
      java.io.InputStream input,
      com.google.protobuf.ExtensionRegistryLite extensionRegistry)
      throws java.io.IOException {
    return com.google.protobuf.GeneratedMessageV3
        .parseDelimitedWithIOException(PARSER, input, extensionRegistry);
  }
  public static org.openmit.entry.Instance parseFrom(
      com.google.protobuf.CodedInputStream input)
      throws java.io.IOException {
    return com.google.protobuf.GeneratedMessageV3
        .parseWithIOException(PARSER, input);
  }
  public static org.openmit.entry.Instance parseFrom(
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
  public static Builder newBuilder(org.openmit.entry.Instance prototype) {
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
   * Protobuf type {@code openmit.pb.Instance}
   */
  public static final class Builder extends
      com.google.protobuf.GeneratedMessageV3.Builder<Builder> implements
      // @@protoc_insertion_point(builder_implements:openmit.pb.Instance)
      org.openmit.entry.InstanceOrBuilder {
    public static final com.google.protobuf.Descriptors.Descriptor
        getDescriptor() {
      return org.openmit.entry.InstanceProtos.internal_static_openmit_pb_Instance_descriptor;
    }

    protected com.google.protobuf.GeneratedMessageV3.FieldAccessorTable
        internalGetFieldAccessorTable() {
      return org.openmit.entry.InstanceProtos.internal_static_openmit_pb_Instance_fieldAccessorTable
          .ensureFieldAccessorsInitialized(
              org.openmit.entry.Instance.class, org.openmit.entry.Instance.Builder.class);
    }

    // Construct using org.openmit.entry.Instance.newBuilder()
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
      instId_ = 0L;

      instWeight_ = 0F;

      if (labelBuilder_ == null) {
        label_ = null;
      } else {
        label_ = null;
        labelBuilder_ = null;
      }
      if (featuresBuilder_ == null) {
        features_ = null;
      } else {
        features_ = null;
        featuresBuilder_ = null;
      }
      seqId_ = 0;

      return this;
    }

    public com.google.protobuf.Descriptors.Descriptor
        getDescriptorForType() {
      return org.openmit.entry.InstanceProtos.internal_static_openmit_pb_Instance_descriptor;
    }

    public org.openmit.entry.Instance getDefaultInstanceForType() {
      return org.openmit.entry.Instance.getDefaultInstance();
    }

    public org.openmit.entry.Instance build() {
      org.openmit.entry.Instance result = buildPartial();
      if (!result.isInitialized()) {
        throw newUninitializedMessageException(result);
      }
      return result;
    }

    public org.openmit.entry.Instance buildPartial() {
      org.openmit.entry.Instance result = new org.openmit.entry.Instance(this);
      result.instId_ = instId_;
      result.instWeight_ = instWeight_;
      if (labelBuilder_ == null) {
        result.label_ = label_;
      } else {
        result.label_ = labelBuilder_.build();
      }
      if (featuresBuilder_ == null) {
        result.features_ = features_;
      } else {
        result.features_ = featuresBuilder_.build();
      }
      result.seqId_ = seqId_;
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
      if (other instanceof org.openmit.entry.Instance) {
        return mergeFrom((org.openmit.entry.Instance)other);
      } else {
        super.mergeFrom(other);
        return this;
      }
    }

    public Builder mergeFrom(org.openmit.entry.Instance other) {
      if (other == org.openmit.entry.Instance.getDefaultInstance()) return this;
      if (other.getInstId() != 0L) {
        setInstId(other.getInstId());
      }
      if (other.getInstWeight() != 0F) {
        setInstWeight(other.getInstWeight());
      }
      if (other.hasLabel()) {
        mergeLabel(other.getLabel());
      }
      if (other.hasFeatures()) {
        mergeFeatures(other.getFeatures());
      }
      if (other.getSeqId() != 0) {
        setSeqId(other.getSeqId());
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
      org.openmit.entry.Instance parsedMessage = null;
      try {
        parsedMessage = PARSER.parsePartialFrom(input, extensionRegistry);
      } catch (com.google.protobuf.InvalidProtocolBufferException e) {
        parsedMessage = (org.openmit.entry.Instance) e.getUnfinishedMessage();
        throw e.unwrapIOException();
      } finally {
        if (parsedMessage != null) {
          mergeFrom(parsedMessage);
        }
      }
      return this;
    }

    private long instId_ ;
    /**
     * <code>uint64 inst_id = 1;</code>
     */
    public long getInstId() {
      return instId_;
    }
    /**
     * <code>uint64 inst_id = 1;</code>
     */
    public Builder setInstId(long value) {
      
      instId_ = value;
      onChanged();
      return this;
    }
    /**
     * <code>uint64 inst_id = 1;</code>
     */
    public Builder clearInstId() {
      
      instId_ = 0L;
      onChanged();
      return this;
    }

    private float instWeight_ ;
    /**
     * <code>float inst_weight = 2;</code>
     */
    public float getInstWeight() {
      return instWeight_;
    }
    /**
     * <code>float inst_weight = 2;</code>
     */
    public Builder setInstWeight(float value) {
      
      instWeight_ = value;
      onChanged();
      return this;
    }
    /**
     * <code>float inst_weight = 2;</code>
     */
    public Builder clearInstWeight() {
      
      instWeight_ = 0F;
      onChanged();
      return this;
    }

    private org.openmit.entry.Label label_ = null;
    private com.google.protobuf.SingleFieldBuilderV3<
        org.openmit.entry.Label, org.openmit.entry.Label.Builder, org.openmit.entry.LabelOrBuilder> labelBuilder_;
    /**
     * <code>.openmit.pb.Label label = 3;</code>
     */
    public boolean hasLabel() {
      return labelBuilder_ != null || label_ != null;
    }
    /**
     * <code>.openmit.pb.Label label = 3;</code>
     */
    public org.openmit.entry.Label getLabel() {
      if (labelBuilder_ == null) {
        return label_ == null ? org.openmit.entry.Label.getDefaultInstance() : label_;
      } else {
        return labelBuilder_.getMessage();
      }
    }
    /**
     * <code>.openmit.pb.Label label = 3;</code>
     */
    public Builder setLabel(org.openmit.entry.Label value) {
      if (labelBuilder_ == null) {
        if (value == null) {
          throw new NullPointerException();
        }
        label_ = value;
        onChanged();
      } else {
        labelBuilder_.setMessage(value);
      }

      return this;
    }
    /**
     * <code>.openmit.pb.Label label = 3;</code>
     */
    public Builder setLabel(
        org.openmit.entry.Label.Builder builderForValue) {
      if (labelBuilder_ == null) {
        label_ = builderForValue.build();
        onChanged();
      } else {
        labelBuilder_.setMessage(builderForValue.build());
      }

      return this;
    }
    /**
     * <code>.openmit.pb.Label label = 3;</code>
     */
    public Builder mergeLabel(org.openmit.entry.Label value) {
      if (labelBuilder_ == null) {
        if (label_ != null) {
          label_ =
            org.openmit.entry.Label.newBuilder(label_).mergeFrom(value).buildPartial();
        } else {
          label_ = value;
        }
        onChanged();
      } else {
        labelBuilder_.mergeFrom(value);
      }

      return this;
    }
    /**
     * <code>.openmit.pb.Label label = 3;</code>
     */
    public Builder clearLabel() {
      if (labelBuilder_ == null) {
        label_ = null;
        onChanged();
      } else {
        label_ = null;
        labelBuilder_ = null;
      }

      return this;
    }
    /**
     * <code>.openmit.pb.Label label = 3;</code>
     */
    public org.openmit.entry.Label.Builder getLabelBuilder() {
      
      onChanged();
      return getLabelFieldBuilder().getBuilder();
    }
    /**
     * <code>.openmit.pb.Label label = 3;</code>
     */
    public org.openmit.entry.LabelOrBuilder getLabelOrBuilder() {
      if (labelBuilder_ != null) {
        return labelBuilder_.getMessageOrBuilder();
      } else {
        return label_ == null ?
            org.openmit.entry.Label.getDefaultInstance() : label_;
      }
    }
    /**
     * <code>.openmit.pb.Label label = 3;</code>
     */
    private com.google.protobuf.SingleFieldBuilderV3<
        org.openmit.entry.Label, org.openmit.entry.Label.Builder, org.openmit.entry.LabelOrBuilder> 
        getLabelFieldBuilder() {
      if (labelBuilder_ == null) {
        labelBuilder_ = new com.google.protobuf.SingleFieldBuilderV3<
            org.openmit.entry.Label, org.openmit.entry.Label.Builder, org.openmit.entry.LabelOrBuilder>(
                getLabel(),
                getParentForChildren(),
                isClean());
        label_ = null;
      }
      return labelBuilder_;
    }

    private org.openmit.entry.Features features_ = null;
    private com.google.protobuf.SingleFieldBuilderV3<
        org.openmit.entry.Features, org.openmit.entry.Features.Builder, org.openmit.entry.FeaturesOrBuilder> featuresBuilder_;
    /**
     * <code>.openmit.pb.Features features = 4;</code>
     */
    public boolean hasFeatures() {
      return featuresBuilder_ != null || features_ != null;
    }
    /**
     * <code>.openmit.pb.Features features = 4;</code>
     */
    public org.openmit.entry.Features getFeatures() {
      if (featuresBuilder_ == null) {
        return features_ == null ? org.openmit.entry.Features.getDefaultInstance() : features_;
      } else {
        return featuresBuilder_.getMessage();
      }
    }
    /**
     * <code>.openmit.pb.Features features = 4;</code>
     */
    public Builder setFeatures(org.openmit.entry.Features value) {
      if (featuresBuilder_ == null) {
        if (value == null) {
          throw new NullPointerException();
        }
        features_ = value;
        onChanged();
      } else {
        featuresBuilder_.setMessage(value);
      }

      return this;
    }
    /**
     * <code>.openmit.pb.Features features = 4;</code>
     */
    public Builder setFeatures(
        org.openmit.entry.Features.Builder builderForValue) {
      if (featuresBuilder_ == null) {
        features_ = builderForValue.build();
        onChanged();
      } else {
        featuresBuilder_.setMessage(builderForValue.build());
      }

      return this;
    }
    /**
     * <code>.openmit.pb.Features features = 4;</code>
     */
    public Builder mergeFeatures(org.openmit.entry.Features value) {
      if (featuresBuilder_ == null) {
        if (features_ != null) {
          features_ =
            org.openmit.entry.Features.newBuilder(features_).mergeFrom(value).buildPartial();
        } else {
          features_ = value;
        }
        onChanged();
      } else {
        featuresBuilder_.mergeFrom(value);
      }

      return this;
    }
    /**
     * <code>.openmit.pb.Features features = 4;</code>
     */
    public Builder clearFeatures() {
      if (featuresBuilder_ == null) {
        features_ = null;
        onChanged();
      } else {
        features_ = null;
        featuresBuilder_ = null;
      }

      return this;
    }
    /**
     * <code>.openmit.pb.Features features = 4;</code>
     */
    public org.openmit.entry.Features.Builder getFeaturesBuilder() {
      
      onChanged();
      return getFeaturesFieldBuilder().getBuilder();
    }
    /**
     * <code>.openmit.pb.Features features = 4;</code>
     */
    public org.openmit.entry.FeaturesOrBuilder getFeaturesOrBuilder() {
      if (featuresBuilder_ != null) {
        return featuresBuilder_.getMessageOrBuilder();
      } else {
        return features_ == null ?
            org.openmit.entry.Features.getDefaultInstance() : features_;
      }
    }
    /**
     * <code>.openmit.pb.Features features = 4;</code>
     */
    private com.google.protobuf.SingleFieldBuilderV3<
        org.openmit.entry.Features, org.openmit.entry.Features.Builder, org.openmit.entry.FeaturesOrBuilder> 
        getFeaturesFieldBuilder() {
      if (featuresBuilder_ == null) {
        featuresBuilder_ = new com.google.protobuf.SingleFieldBuilderV3<
            org.openmit.entry.Features, org.openmit.entry.Features.Builder, org.openmit.entry.FeaturesOrBuilder>(
                getFeatures(),
                getParentForChildren(),
                isClean());
        features_ = null;
      }
      return featuresBuilder_;
    }

    private int seqId_ ;
    /**
     * <code>uint32 seq_id = 5;</code>
     */
    public int getSeqId() {
      return seqId_;
    }
    /**
     * <code>uint32 seq_id = 5;</code>
     */
    public Builder setSeqId(int value) {
      
      seqId_ = value;
      onChanged();
      return this;
    }
    /**
     * <code>uint32 seq_id = 5;</code>
     */
    public Builder clearSeqId() {
      
      seqId_ = 0;
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


    // @@protoc_insertion_point(builder_scope:openmit.pb.Instance)
  }

  // @@protoc_insertion_point(class_scope:openmit.pb.Instance)
  private static final org.openmit.entry.Instance DEFAULT_INSTANCE;
  static {
    DEFAULT_INSTANCE = new org.openmit.entry.Instance();
  }

  public static org.openmit.entry.Instance getDefaultInstance() {
    return DEFAULT_INSTANCE;
  }

  private static final com.google.protobuf.Parser<Instance>
      PARSER = new com.google.protobuf.AbstractParser<Instance>() {
    public Instance parsePartialFrom(
        com.google.protobuf.CodedInputStream input,
        com.google.protobuf.ExtensionRegistryLite extensionRegistry)
        throws com.google.protobuf.InvalidProtocolBufferException {
      return new Instance(input, extensionRegistry);
    }
  };

  public static com.google.protobuf.Parser<Instance> parser() {
    return PARSER;
  }

  @java.lang.Override
  public com.google.protobuf.Parser<Instance> getParserForType() {
    return PARSER;
  }

  public org.openmit.entry.Instance getDefaultInstanceForType() {
    return DEFAULT_INSTANCE;
  }

}

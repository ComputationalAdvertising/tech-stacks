// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: instance.proto

package org.openmit.entry;

public interface InstanceOrBuilder extends
    // @@protoc_insertion_point(interface_extends:openmit.pb.Instance)
    com.google.protobuf.MessageOrBuilder {

  /**
   * <code>uint64 inst_id = 1;</code>
   */
  long getInstId();

  /**
   * <code>float inst_weight = 2;</code>
   */
  float getInstWeight();

  /**
   * <code>.openmit.pb.Label label = 3;</code>
   */
  boolean hasLabel();
  /**
   * <code>.openmit.pb.Label label = 3;</code>
   */
  org.openmit.entry.Label getLabel();
  /**
   * <code>.openmit.pb.Label label = 3;</code>
   */
  org.openmit.entry.LabelOrBuilder getLabelOrBuilder();

  /**
   * <code>.openmit.pb.Features features = 4;</code>
   */
  boolean hasFeatures();
  /**
   * <code>.openmit.pb.Features features = 4;</code>
   */
  org.openmit.entry.Features getFeatures();
  /**
   * <code>.openmit.pb.Features features = 4;</code>
   */
  org.openmit.entry.FeaturesOrBuilder getFeaturesOrBuilder();

  /**
   * <code>uint32 seq_id = 5;</code>
   */
  int getSeqId();
}
// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: instance.proto

package org.openmit.entry;

public interface DenseFeatureOrBuilder extends
    // @@protoc_insertion_point(interface_extends:openmit.pb.DenseFeature)
    com.google.protobuf.MessageOrBuilder {

  /**
   * <code>string type = 1;</code>
   */
  java.lang.String getType();
  /**
   * <code>string type = 1;</code>
   */
  com.google.protobuf.ByteString
      getTypeBytes();

  /**
   * <code>repeated float values = 2;</code>
   */
  java.util.List<java.lang.Float> getValuesList();
  /**
   * <code>repeated float values = 2;</code>
   */
  int getValuesCount();
  /**
   * <code>repeated float values = 2;</code>
   */
  float getValues(int index);
}
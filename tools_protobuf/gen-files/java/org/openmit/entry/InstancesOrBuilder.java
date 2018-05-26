// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: instance.proto

package org.openmit.entry;

public interface InstancesOrBuilder extends
    // @@protoc_insertion_point(interface_extends:openmit.pb.Instances)
    com.google.protobuf.MessageOrBuilder {

  /**
   * <code>repeated .openmit.pb.Instance instances = 1;</code>
   */
  java.util.List<org.openmit.entry.Instance> 
      getInstancesList();
  /**
   * <code>repeated .openmit.pb.Instance instances = 1;</code>
   */
  org.openmit.entry.Instance getInstances(int index);
  /**
   * <code>repeated .openmit.pb.Instance instances = 1;</code>
   */
  int getInstancesCount();
  /**
   * <code>repeated .openmit.pb.Instance instances = 1;</code>
   */
  java.util.List<? extends org.openmit.entry.InstanceOrBuilder> 
      getInstancesOrBuilderList();
  /**
   * <code>repeated .openmit.pb.Instance instances = 1;</code>
   */
  org.openmit.entry.InstanceOrBuilder getInstancesOrBuilder(
      int index);

  /**
   * <code>uint64 logid = 2;</code>
   */
  long getLogid();

  /**
   * <code>map&lt;string, string&gt; meta_info = 3;</code>
   */
  int getMetaInfoCount();
  /**
   * <code>map&lt;string, string&gt; meta_info = 3;</code>
   */
  boolean containsMetaInfo(
      java.lang.String key);
  /**
   * Use {@link #getMetaInfoMap()} instead.
   */
  @java.lang.Deprecated
  java.util.Map<java.lang.String, java.lang.String>
  getMetaInfo();
  /**
   * <code>map&lt;string, string&gt; meta_info = 3;</code>
   */
  java.util.Map<java.lang.String, java.lang.String>
  getMetaInfoMap();
  /**
   * <code>map&lt;string, string&gt; meta_info = 3;</code>
   */

  java.lang.String getMetaInfoOrDefault(
      java.lang.String key,
      java.lang.String defaultValue);
  /**
   * <code>map&lt;string, string&gt; meta_info = 3;</code>
   */

  java.lang.String getMetaInfoOrThrow(
      java.lang.String key);
}
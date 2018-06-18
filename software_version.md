
# 软件与Build顺序

## 软件版本

| 软件名 | 版本 | 模块 | 备注 |
| --- | --- | --- | --- |
| `boost` | `1.60.0` | `cpp_boost` | `rpc_muduo/rpc_thrift`的上游，因muduo不支持高版本boost，因此最高boost版本为1.60.0 （也是ubuntu16.04的默认版本） |
| `gperftools` | `2.7` | `rpc_muduo` | 性能测试工具 | 
| `muduo` | `1.1.0` | `rpc_muduo` | 依赖`boost/protobuf/thrift`等，**其中boost版本最高为`1.60.0`**，再高则`no match function...` |
| `protobuf` | `3.5.0` | `tools_protobuf` | `rpc_thrift/rpc_muduo`模块的上游，目前可以满足下游的版本需求 | 
| `thrift` | `0.10.0` | `rpc_thrift` | `rpc_muduo`的上游，因为很多依赖thrift的程序没有切换成`stdcxx::shared_ptr`，用`0.11.0`版本，会造成`no match function...`参数类型问题。|
| `snappy` | `1.1.7` | `rpc_thrift` | 软件压缩库 |


## build顺序 

1. `sh cpp_boost/install-dependencies.sh -m yes`  #  是否移动至`~/local/`
2. `sh tools_protobuf/install`
3. ``

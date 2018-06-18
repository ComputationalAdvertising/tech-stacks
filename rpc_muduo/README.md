# muduo: c++ multi-thread network tools 

**软件版本与依赖**

| 软件名 | 版本 | 必须? | 备注 |
| --- | --- | --- | --- |
| `thrift` | `0.10.0` | yes | 最新版`0.11.0`会出现`no match function ...`错误，<br>原因主要是：`stdcxx::shared_ptr`和`boost::shared_ptr`参数类型问题。用`thrift-0.10.0`不存在该问题 |
| `gperftools` | `2.7` | no | 性能测试程序`profiler`。安装在`~/software/local`下 |
| `protobuf` | `3.5.0` | no | 安装在`~/software/local`下。muduo/CMakeLists.txt中的`find_package(Protobuf)`默认获取`/usr/lib`下的protobuf.so，因此需要删除掉`/usr/lib`下的proto相关动态库；|
| `boost` | `1.58.0` | yes | 



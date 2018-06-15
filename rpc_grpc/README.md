# rpc-grpc

+ author: zhouyongsdzh@foxmail.com
+ date: 2016

##  示例

### 程序使用

+ `conf/env_path.conf`：配置文件 `PROTOBUF_HOME`和`GRPC_HOME`
+ `proto/helloworld.proto`: 简单的测试proto
+ `compile-pb-with-grpc.sh`：编译proto
+ 构建：`sh build.sh`
+ 示例：
    + server：`./bin/greeter_server` 
    + worker: `./bin/greeter_worker`

### gRPC任务启动





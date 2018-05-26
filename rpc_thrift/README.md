# Thrift Learning and Use

## 安装 

运行环境：GCC版本支持c++11.

1. `thrift`: rpc框架；
2. `snappy`: 数据压缩工具，主要包含`Compress`和`UnCompress`功能；
3. `build.sh`中需设定`export ${THRIFT_HOME}`和`export ${PROTOBUF_HOME}`

## 示例

1. `learning/basic_{client,server}.cc` 官方demo；
2. `learning/basic_pb_{client,server}.cc`：pb数据包装在thrift-binary中。（proto IDL定义在`tools_protobuf/proto`目录中）






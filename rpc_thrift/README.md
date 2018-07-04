# Thrift Learning and Use


**软件版本与依赖**

| 软件名 | 版本 | 必须? | 备注 |
| --- | --- | --- | --- |
| `thrift` | `0.10.0` | yes | 安装目标，因为很多依赖thrift的程序没有切换成`stdcxx::shared_ptr`，用`0.11.0`版本，会造成`no match function...`参数类型问题。|
| `snappy` | `1.1.7` | no | 软件压缩库 |
| `boost` | `1.60.0` | yes | 依赖库，因muduo不支持高版本boost，因此最高boost版本为1.60.0 （也是ubuntu16.04的默认版本） |
| `libevent` | `2.0.22` | yes | 依赖库，使用`TNonBlockingServer`需要libevent. 需要提前安装libevent. 并且configure thrift时要指定目录 `-with-libevent=${dir}` |
| `openssl` | `1.1.1` | yes (for centos) | 依赖库，centos默认不安装openssl(ubuntu默认有)，需要先安装openssl, 安装thrift前 需要`export LD_LIBRARY_PATH=${OPENSSL_HOME}/lib:$LD_LIBRARY_PATH` |

## 安装 

运行环境：GCC版本支持c++11.

+ `thrift`: rpc框架；
+ `libevent`: 网络库。`TNonBlockingServer`需要libevent；
+ `snappy`: 数据压缩工具，主要包含`Compress`和`UnCompress`功能；
+ `openssl`: thrift依赖的加密工具库;
+ `build.sh`中需设定`export ${THRIFT_HOME}`和`export ${PROTOBUF_HOME}`

## 示例

1. `learning/basic_{client,server}.cc` 官方demo；
2. `learning/basic_pb_{client,server}.cc`：pb数据包装在thrift-binary中。（proto IDL定义在`tools_protobuf/proto`目录中）

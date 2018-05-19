# tensorflow_cpp

+ author: zhouyongsdzh@foxmail.com

## 目录

+ 依赖构建与测试

## 依赖构建与测试

### 编译TF静态库

**安装上游依赖**

安装TensorFlow编译所需环境：**bazel**。 Ubuntu安装过程：

```bash
# 1. 安装java8版本
sudo add-apt-repository ppa:webupd8team/java
sudo apt-get update 
sudo apt-get install oracle-java8-installer     // 安装JDK8版本
# 2. Add Bazel distribution URI as a package source
echo "deb [arch=amd64] http://storage.googleapis.com/bazel-apt stable jdk1.8" | sudo tee /etc/apt/sources.list.d/bazel.list
curl https://bazel.build/bazel-release.pub.gpg | sudo apt-key add -
# 3. 安装和更新bazel
sudo apt-get update && sudo apt-get install bazel
# sudo apt-get upgrade bazel // 用于更新版本
which bazel
/usr/bin/bazel  // 安装成功
```

> Ubuntu上安装bazel 参考官网：https://docs.bazel.build/versions/master/install-ubuntu.html . 官网也介绍了bazel的二进制安装方式（Install using binary installer） 
> 
参考：https://www.tensorflow.org/get_started/get_started

**源码编译TF**

```bash
# 1. 下载
git clone --recursive https://github.com/tensorflow/tensorflow
cd tensorflow
# 2. 编译生成.so文件, 编译C++ API的库 
bazel build //tensorflow:libtensorflow_cc.so
# 编译C API的库 ［可选］
bazel build //tensorflow:libtensorflow.so
# 编译成功后，在tensorflow根目录bazel-bin/tensorflow/目录下会出现libtensorflow.so/libtensorflow_cc.so/libtensorflow_framework.so文件
# 3. 生成必要的依赖头文件, 执行
sh tensorflow/contrib/makefile/build_all_linux.sh
# 可以看到tensorflow/contrib/makefile/gen/protobuf/include目录，需要包含在cmake的include_directories()里.
# tensorflow和bazel-genfiles也需要放在include_dicectories目录下。
```

> 如果编译失败，提示错误码为`4`，应该是swap空间问题，重复编译几次即可。

### 测试：CPP程序调用TF库文件和头文件

```bash
# 1. 源码 learning/tf_session.cc
sh build.sh
./bin/tf_session
```

**CMake过程中遇到错误**

> 1. `tensorflow/tensorflow/core/platform/default/mutex.h:25:22: fatal error: nsync_cv.h: No such file or directory`
> 需要在CMakeLists.txt中的配置`include_directories`添加：`/home/zhouyongsdzh/software/tensorflow-family/tensorflow/bazel-tensorflow/external/nsync/public`
> 
> 2. `/tensorflow/third_party/eigen3/unsupported/Eigen/CXX11/Tensor:1:42: fatal error: unsupported/Eigen/CXX11/Tensor: No such file or directory`
> 错误原因： 没有安装或找到Eigen的路径。
> 需要在CMakeLists.txt中的配置`include_directories`添加：`${tf_root_dir}/tensorflow/tensorflow/contrib/makefile/downloads/eigen`
> 
> 3. `libtensorflow_cc.so: undefined reference to tensorflow::_OptimizerOptions_default_instance_`
>  错误原因：没有`tensorflow_framework`动态库 （与`libtensorflow_cc.so`在同一个目录）
> 解决方案：将`libtensorflow_framework.so`添加到`include_libraries`里，同时配置`list(APPEND tfserving_LINKER_LIBS tensorflow_framework)`

此外，需要注意：

> 1. cpp程序构建的gcc版本不能小于TF源码编译的gcc版本。否则会提示`GLIBCXX`版本问题。如下：
> `libtensorflow_framework.so: undefined reference to 'typeinfo for std::thread::_State@GLIBCXX_3.4.22'`

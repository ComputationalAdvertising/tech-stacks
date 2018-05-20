# tensorflow_cpp

+ author: zhouyongsdzh@foxmail.com

## 目录

+ 依赖构建与测试
+ [Tensorflow测试程序](Tensorflow测试程序)

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

> 1. Ubuntu上安装bazel 参考官网：https://docs.bazel.build/versions/master/install-ubuntu.html . 官网也介绍了bazel的二进制安装方式（Install using binary installer） .参考：https://www.tensorflow.org/get_started/get_started
> 2. 注意Tensorflow版本与bazel版本的一致性；

**源码编译TF**

```bash
# 1. 下载
git clone --recursive https://github.com/tensorflow/tensorflow
cd tensorflow
运行./configure 完成一系列配置
# 2. 编译生成.so文件, 编译C++ API的库 
bazel build //tensorflow:libtensorflow_cc.so
# 编译C API的库 ［可选］
bazel build //tensorflow:libtensorflow.so
# 编译成功后，在tensorflow根目录bazel-bin/tensorflow/目录下会出现libtensorflow.so/libtensorflow_cc.so/libtensorflow_framework.so文件
# linux安装依赖，生成必要的依赖头文件, 执行
sh tensorflow/contrib/makefile/build_all_linux.sh
# 可以看到tensorflow/contrib/makefile/gen/protobuf/include目录，需要包含在cmake的include_directories()里.
# tensorflow和bazel-genfiles也需要放在include_dicectories目录下。
# 4. bazel源码编译TF
bazel build  -c opt --copt=-msse4.1 --copt=-msse4.2 --copt=-mavx --copt=-mavx2 --copt=-mfma --copt=-O3 //tensorflow/...
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


## Tensorflow测试程序

在`${TENSORFLOW_HOME}/tensorflow/{cc,core}`目录下，可以看到有`*_test.cc`的测试文件，如果我们想在TF bazel下运行这些测试文件，需要先编译，使用`bazel test`命令。 进入`${TENSORFLOW_HOME}`目录：

| 命令 | 操作 |
| --- | --- |
| 编译所有test程序（C++）| `bazel test //tensorflow/...` |
| 编译所有test程序（Python）| `bazel test //tensorflow/python/...` |
| 所有的test程序（with GPU）| `bazel test -c opt --config=cuda //tensorflow/...`<br>`bazel test -c opt --config=cuda //tensorflow/python/...` |

+ `bazel test tensorflow/core:ops_string_ops_test` ：编译`tensorflow/core/ops/string_ops_test.cc`文件.

> 因为BUILD是放在`tensorflow/core`目录下的，编译目标`ops_string_ops_test`实则对应`ops/string_ops_test.cc`原文件。

**构建错误**

1. 编译`tech-stacks/tensorflow_cpp/learning/string_ops_test.cc`时，报错：

    `string_ops_test.cc:37: undefined reference to tensorflow::shape_inference::ShapeInferenceTestutil::InferShapes(tensorflow::ShapeInferenceTestOp, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)'`

    主要原因：`tensorflow/core`目录很多源码没有编译，比如`tensorflow/core/framework/shape_inference_testutil.h`. 没有`bazel-bin/tensorflow/core/lib*.so`
    
    解决办法：构建Tensorflow，可运行`bazel test tensorflow/core:ops_string_ops_test`。 然后在`bazel-bin/tensorflow/core/{cc,core}`可看到对应的so库文件，将其路径放入项目CMakeLists.txt的`link_directories`和`target_link_libraries`中。
    
    ```c++
    set(link_library_names  -pthread  tensorflow_cc  tensorflow_framework
  ...  shape_inference_testutil   (关键so)
  ... ) 
    ```

2. 编译`tech-stacks/tensorflow_cpp/learning/cc_op_gen_test.cc`报错：

    ```c++
    /tensorflow_cpp/learning/cc_op_gen_test.cc:95: undefined reference to `tensorflow::WriteCCOps(...)
    ```
    
    原文件在：`${TENSORFLOW_HOME}/tensorflow/cc/framework/cc_op_gen_test.cc`。原因同上。`WriteCCOps`在`tensorflow/cc/framework/cc_op_gen.h`中定义。 
    
    问题原因：看`tensorflow/cc/BUILD`中，没有把`cc_op_gen.cc`生成独立的so来引用；
    
3. 编译错误：

    ```
    tensorflow/cc/framework/cc_ops_test.cc:19:10: fatal error: tensorflow/cc/ops/test_op.h: No such file or directory #include "tensorflow/cc/ops/test_op.h"
 ```

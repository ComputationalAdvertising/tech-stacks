### Tensor的定义与操作

Tensor是TF的信息存储单元，其结构定义在tensor.proto文件中，包含数据类型、TensorShape，以及其它变量信息。一个比较重要的字段：`bytes tensor_content = 4` 存储Tensor的内容，用于grpc通信机器间信息交互和`Tensor::AsProtoTensorContent`。具体见`tensorflow/core/framework/tensor.proto`

tensor.h给出了Tensor的操作和功能。

+ 代码：`tensorflow/core/framework/tensor.{h/cc/proto}` 
+ 内容：
    + 基本数据类型：这里面用到了`Eigen/CXX11/Tensor`信息。代码：`tensorflow/core/framework/types.{h/proto}` 
    
### TensorFlow运行

+ `session/session_factory`

用GraphDef来创建Session. 
测试`session_test`: `./bazel-bin/tensorflow/core/common_runtime_session_test`

+ `direct_session` 本地模式

测试：`./bazel-bin/tensorflow/core/common_runtime_direct_session_test`

Graph中可以添加Node，也可以添加Var，具体的节点类型可以很多，比如`Send/Recv/Reduce/...`，实现在`tensorflow/core/graph/testlib.cc`

```c++
// Adds a send node "g" sending "input" as a named "tensor" from
// "sender" to "receiver".
Node* Send(Graph* g, Node* input, const string& tensor, const string& sender,
           const uint64 sender_incarnation, const string& receiver);

// Adds a recv node in "g" receiving a named "tensor" from "sender"
// to "receiver".
Node* Recv(Graph* g, const string& tensor, const string& type,
           const string& sender, const uint64 sender_incarnation,
           const string& receiver);
```

这里的调用关系是: `direct_session_test.cc --> NodeBuilder --> NodeDefBuilder`

+ `grpc_session`: 分布式

GRpcSession作为入口：

```c++
// step1 (tensorflow/core/distributed_runtime/rpc/grpc_session.h)
Status RunProto(CallOptions* call_options, MutableRunStepRequestWrapper* req, MutableRunStepResponseWrapper* resp);
// step2
```

类`Rendevous`是一个针对`<produces, consumers>`的抽象，包括多个通道(channel)。通过`SendOp`和`RecvOp`实现跨机器通信。代码：`tensorflow/core/framework/rendezvous.cc`
具体的`SendOp/RecvOp`实现代码在`tensorflow/core/kernels/sendrecv_ops.{h/cc}`

**测试程序：`./bazel-bin/tensorflow/core/distributed_runtime/tensor_coding_test`**

通信的主要数据结构`RecvTensorRequest`和`RecvTensorResponse`定义在`tensorflow/core/protobuf/worker.proto`中；

**测试程序: ``**

分布式机器通信由rpc实现。 `rpc/grpc_tensor_coding.{h/cc}`负责Tensor与::grpc::ByteBuffer的转化；

分布式程序测试入口：

+ 源文件：`tensorflow/core/distributed_runtime/executor_test.cc`
+ 编译：`bazel build //tensorflow/core/distributed_runtime:executor_test`
+ 执行文件：`./bazel-bin/tensorflow/core/distributed_runtime/executor_test`

```c++
// 1. 测试入口 
[tensorflow/core/distributed_runtime/execute_test.cc] Graph* g = new Graph(OpRegistry::Global());
// 2. 创建Graph
-> [tensorflow/tensorflow/core/graph/graph.cc] Graph::Graph(const OpRegistryInterface* ops)
->->
// 3. 添加节点，支持各种Node类型（见testlib.h）
[tensorflow/core/distributed_runtime/execute_test] auto in0 = test::graph::Recv(g, "a", "float", ALICE, 1, BOB);
-> [tensorflow/tensorflow/core/graph/testlib.cc] Node* Recv(Graph* g, const string& tensor, ..., const string& sender, ..., const string& receiver)
--> 
// 4. Create(graph)，重置executor
[tensorflow/core/distributed_runtime/execute_test.cc] void Create(const Graph* graph) { 
    LocalExecutorParams params; // 提供了Executor的Context. 
    params.device = device_;
    // (**非常重要**) 注册create_kernel和delete_kernel的实现逻辑 
    params.create_kernel = [this, version](const NodeDef& ndef, OpKernel** kernel) {
      return CreateNonCachedKernel(device_, nullptr, ndef, version, kernel);
    };
    params.delete_kernel = [](OpKernel* kernel) {
      DeleteNonCachedKernel(kernel);
    };
    ...
    TF_CHECK_OK(NewLocalExecutor(params, graph, &exec_)); // 创建本地executor
    rendez_ = NewLocalRendezvous();   // 初始化grpc通信协议
}
-> [tensorflow/core/common_runtime/executor.cc:2584] ExecutorImpl* impl = new ExecutorImpl(params, graph); 
-> [tensorflow/core/common_runtime/executor.cc:2585] const Status s = impl->Initialize(); Executor实体初始化
-> [tensorflow/core/common_runtime/executor.cc:605] Status ExecutorImpl::Initialize() { ... }
->-> [tensorflow/core/common_runtime/executor.cc:606] gview_.Initialize(graph_); // 初始化图节点
->-> [tensorflow/core/common_runtime/executor.cc:560] void GraphView::Initialize(const Graph* g) { ptr = InitializeNode(ptr, n); }
->->-> [tensorflow/core/common_runtime/executor.cc:487] char* GraphView::InitializeNode(char* ptr, const Node* n); // 建立NodeItem,EdgeInfo
// 小结：Executor创建和初始化的过程，实质上是计算图节点创建的过程（在执行层面），依赖和边的构建
->-> [tensorflow/core/common_runtime/executor.cc:639] Status s = params_.create_kernel(n->def(), &item->kernel); 
    // 基于NodeDef创建OpKernel实例。直接调用params.create_kernel的CreateNonCachedKernel方法
->->-> [tensorflow/core/framework/op_kernel.cc:1053] Status CreateOpKernel(DeviceType device_type, ..., const NodeDef& node_def, ..., OpKernel** kernel) 
// 
```

    


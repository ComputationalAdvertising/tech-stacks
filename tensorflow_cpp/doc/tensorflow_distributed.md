### Tensor的定义与操作

Tensor是TF的信息存储单元，其结构定义在tensor.proto文件中，包含DataType、TensorShape，以及其它变量信息。一个比较重要的字段：`bytes tensor_content = 4` 存储Tensor的内容，用于grpc通信时机器间信息交互和`Tensor::AsProtoTensorContent`。具体见`tensorflow/core/framework/tensor.proto`

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

Graph中可以添加Node，也可以添加Var，具体的节点类型 很多，比如`Send/Recv/Reduce/...`，实现在`tensorflow/core/graph/testlib.cc`

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
->->-> [core/framework/op_kernel.cc:1053] Status CreateOpKernel(DeviceType device_type, ..., const NodeDef& node_def, ..., OpKernel** kernel)  // 创建OpKernel的方法
->->->-> [core/framework/op_kernel.cc:1110] OpKernelConstruction context(...);  // 用OpKernel构造器完成之后，调用OpKernel注册工厂完成注册。OpKernelRegistrar::Factory
->->->-> [core/framework/op_kernel.cc:1113] *kernel = (*registration->factory)(&context);
->->->->-> [core/framework/op_kernel.cc:816] struct KernelRegistration { kernel_factory::OpKernelRegistrar::Factory factory; }
// ???? 如何调用到具体的opkernel的？
```



########## 代码

1. MasterSession: 资源分配，Node在device上的分配，图计算；
2. Rendezous：负责Send/Recv功能
    + `RpcRendezvousMgr`
3. dist/master.h中的`std::unordered_map<string, MasterSession*> sessions_ GUARDED_BY(mu_);` 含义是什么？
4. 博客`GrpcRemoteWorker接收master的请求，交由GrpcWorkerService执行。`如何做到的？
    + https://zhuanlan.zhihu.com/p/26031658
5. 节点执行过程

    ```
    tensorflow/core/common_runtime/executor.cc
    core/kernels/sendrecv_ops.cc:79
    tensorflow/core/framework/rendezvous.cc
    ``` 
    
    rendez_->Send(Key(ALICE, kIncarnation, BOB, "a"), args, V(1.0)...)直接远端直接分配内存：MemoryLogTensorAllocation
    
6. OpKernelContext包含的信息？
7. 构建图的时候会涉及到SendOp/RecvOp? 指定Tensor的名字，在真正执行操作时会按照tensor name来传输，怎么在真正执行时拆分呢？


**问题**

1. 分布式图构建时，已经根据tensor name建立了`<worker, ps>`之间的连接，接下来的数据通信是以tensor为单位进行的，如何拆解？ DoneCallBack的处理逻辑是什么？
2. 改写Tensor，完成Tensor的拆解；
3. DoneCallBack执行：NodeDone(s, state->item->node, ready, stats, nullptr);（executor）
    
    


//#include <Eigen/Dense>
//#include <Eigen/Eigen>
#include <unsupported/Eigen/CXX11/Tensor>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> MatrixF;
typedef Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> MatrixI;

void tensormap_basic() {
  std::cout << "\n======================= [Eigen::TensorMap] ====================\n" << std::endl;
  int d0 = 4, d1 = 5, d2 = 3;
  std::vector<int> v(d0*d1*d2, 0);
  for (int i = 0; i < d0 * d1 * d2; ++i) {
    v[i] = i+1;
  }

  // [Eigen::TensorMap]
  Eigen::DSizes<Eigen::DenseIndex, 3> dsizes;
  dsizes[0] = d0; dsizes[1] = d1; dsizes[2] = d2;
  auto mapped = Eigen::TensorMap<Eigen::Tensor<int, 3>>(v.data(), dsizes);
  //auto mapped = Eigen::TensorMap<Eigen::Tensor<int, 3>>(v.data(), d0, d1, d2);

  std::cout << "[TensorMap] rank: " << mapped.rank() << ", dimensions: [" << mapped.dimension(0) 
            << ", " << mapped.dimension(1) << ", " << mapped.dimension(2) << "], size: " << mapped.size() << std::endl;

  std::cout << "[TensorMap] mapped:\n" << mapped << std::endl;
  
  Eigen::Tensor<int, 3> mapped2tensor = mapped;
  std::cout << "[Tensor] mapped2tensor:\n" << mapped2tensor << std::endl;
  std::cout << "[Tensor] mapped2tensor. dimensions: " << mapped2tensor.dimension(0) 
            << ", " << mapped2tensor.dimension(1) 
            << ", " << mapped2tensor.dimension(2) << std::endl;

  // ColMajor -> RowMajor
  Eigen::Tensor<int, 3, Eigen::RowMajor> swapped_tensor = mapped2tensor.swap_layout();
  std::cout << "\n[Tensor] swapped_tensor:\n" << swapped_tensor << std::endl;  
  std::cout << "[Tensor] swapped_tensor. dimensions: " 
            << swapped_tensor.dimension(0) << ", " 
            << swapped_tensor.dimension(1) << ", " 
            << swapped_tensor.dimension(2) << std::endl;

  // TensorMap::slice
  Eigen::array<long,3> startIdx = {{0,0,0}};
  Eigen::array<long,3> extent = {{2,2,2}};
  Eigen::Tensor<int,3> sliced_tensor = mapped2tensor.slice(startIdx, extent); 
  std::cout << "[TensorMap] sliced_tensor:\n" << sliced_tensor << std::endl;
  std::cout << "[TensorMap] sliced_tensor. dimensions: " 
            << sliced_tensor.dimension(0) << ", " 
            << sliced_tensor.dimension(1) << ", " 
            << sliced_tensor.dimension(2) << std::endl;

}

void tensor_basic() {
  // [Eigen::Tensor] 
  std::cout << "\n======================= [Eigen::Tensor] ====================\n" << std::endl;
  const int d0 = 4, d1 = 5, d2 = 3;
  float* fv = new float[d0*d1*d2];
  for (int i = 0; i < d0*d1*d2; ++i) {
    fv[i] = i + 1;
  }

  // default 'column-major', http://eigen.tuxfamily.org/index.php?title=Tensor_support
  Eigen::Tensor<float, 3, Eigen::RowMajor> tensor(d0, d1, d2);
  tensor.setZero();
  tensor.setRandom();
  tensor.setConstant(11.0f);
  std::cout << "[Tensor] tensor initialization:\n" << tensor << std::endl; 

  Eigen::TensorMap<Eigen::Tensor<float, 3, Eigen::RowMajor>> tmap(fv, d0, d1, d2);
  std::cout << "[Tensor] TensorMap tmap:\n" << tmap << std::endl;
  tensor = tmap;
  
  // slice 
  Eigen::array<long, 3> startIdx = {{0, 0, 0}};
  //Eigen::array<long, 3> extent = {{d0-1, d1-1, d2-1}};
  Eigen::array<long, 3> extent = {{1, d1, d2}};
  Eigen::Tensor<float, 3, Eigen::RowMajor> sliced_tensor = tensor.slice(startIdx, extent);
  std::cout << "[Tensor] sliced_tensor:\n" << sliced_tensor << std::endl;

  // swap op 
  Eigen::Tensor<float, 3> swapped_tensor = Eigen::TensorLayoutSwapOp<Eigen::Tensor<float, 3, Eigen::RowMajor>>(tensor);
  std::cout << "[Tensor] swapped_tensor:\n" << swapped_tensor << std::endl;

  // element-wise product 
  Eigen::Tensor<float, 3, Eigen::RowMajor> t1 = tensor * tensor;
  std::cout << "[Tensor] Tensor element-wise product:\n" << t1 << std::endl;
  std::cout << "dim(0): " << t1.dimension(0) << std::endl;
  // TensorFixedSize
  Eigen::TensorFixedSize<float, Eigen::Sizes<d0, d1, d2>, Eigen::RowMajor> tfs = tensor * 0.1f;
  std::cout << "[Tensor] TensorFixedSize element-wise product:\n" << tfs << std::endl;
  std::cout << "[Tensor] exp:\n" << tensor.exp() << std::endl;

  // Eigen::Tensor --> Eigen::Matrix 
  MatrixF matrixf(d0, d1 * d2);
  matrixf = Eigen::Map<const MatrixF>(tmap.data(), d0, d1 * d2);
  std::cout << "[Tensor] MatrixF matrixf:\n" << matrixf << std::endl;
  std::cout << "[Tensor] MatrixF matrixf. rows: " << matrixf.rows() << ", cols: " << matrixf.cols() << std::endl; 
}

typedef Eigen::ThreadPoolDevice CPUDevice;
typedef Eigen::GpuDevice GPUDevice;

/*
template <typename T>
Eigen::Map<const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> 
ToEigenMatrix(const Tensor& tensor) {
  auto matrix = tensor.Matrix<T>();
  return Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>::Map(matrix.data(), matrix.dimension(0), matrix.dimension(1));
}
*/

void tensor_binary_operator() {
  std::cout << "======================= [Eigen::Tensor] binary operator ====================" << std::endl;
  const int d0 = 3, d1 = 4;
  float* fv1 = new float[d0*d1];
  for (int i = 0; i < d0*d1; ++i) {
    fv1[i] = i+1;
  }
  float* fv2 = new float[1*d1];
  for (int i = 0; i < 1*d1; ++i) {
    fv2[i] = i+1;
  }

  Eigen::Tensor<float, 2, Eigen::RowMajor> tensor1(d0, d1);
  Eigen::TensorMap<Eigen::Tensor<float, 2, Eigen::RowMajor>> tmap1(fv1, d0, d1);
  tensor1 = tmap1;

  Eigen::Tensor<float, 2, Eigen::RowMajor> tensor2(1, d1);
  Eigen::TensorMap<Eigen::Tensor<float, 2, Eigen::RowMajor>> tmap2(fv2, 1, d1);
  tensor2 = tmap2;

  std::cout << "========= tensor1 ==========" << std::endl;
  std::cout << "tensor1.rank:" << tensor1.rank() << ", dim[0]: " << tensor1.dimension(0) << ", dim[1]: " << tensor1.dimension(1) << std::endl;
  std::cout << "value:\n" << tensor1 << std::endl;

  std::cout << "========= tensor2 ==========" << std::endl;
  std::cout << "tensor2.rank:" << tensor2.rank() << ", dim[0]: " << tensor2.dimension(0) << ", dim[1]: " << tensor2.dimension(1) << std::endl;
  std::cout << "value:\n" << tensor2 << std::endl;
  
  Eigen::Tensor<float, 2> swapped_tensor2 = Eigen::TensorLayoutSwapOp<Eigen::Tensor<float, 2, Eigen::RowMajor>>(tensor2);
  std::cout << "========= swapped_tensor2 ==========" << std::endl;
  std::cout << "tensor2.rank:" << swapped_tensor2.rank() << ", dim[0]: " << swapped_tensor2.dimension(0) << ", dim[1]: " << swapped_tensor2.dimension(1) << std::endl;
  std::cout << "value:\n" << swapped_tensor2 << std::endl;
  
  
  MatrixF matrixf1(d0, d1);
  matrixf1 = Eigen::Map<const MatrixF>(tmap1.data(), d0, d1);
  
  MatrixF matrixf2(1, d1);
  matrixf2 = Eigen::Map<const MatrixF>(tmap2.data(), 1, d1);

  std::cout << "======== tensor1 * tensor2 ========" << std::endl;
  std::cout << tensor1 * tensor1 << std::endl;

  std::cout << "matrixf1 * matrixf2.transpose:\n" << matrixf1 * matrixf2.transpose() << std::endl;
}

void add_op() {
  Eigen::Tensor<float, 2, Eigen::RowMajor> t1(2, 3);
  t1.setConstant(2);

  Eigen::Tensor<float, 1, Eigen::RowMajor> t2(3);
  t2.setConstant(3);

  Eigen::array<int, 2> dims;
  dims[0] = 1;
  dims[1] = t2.dimension(0);
  Eigen::array<int, 2> bcast({2, 1});
  //auto t3 = t2.reshape(dims);
  std::cout << "t1:\n" << t1 << ", shape: " << t1.dimension(0) << "," << t1.dimension(1)
    << "\n,t2:\n" << t2  << ", shape: "<< "," << t2.dimension(0)
    << "\n, t1+t2:\n" << t1 + t2.reshape(dims).broadcast(bcast) 
    << std::endl;
}

void concat_op() {
  std::vector<Eigen::Tensor<float, 2, Eigen::RowMajor>> vecs;
  
  Eigen::Tensor<float, 2, Eigen::RowMajor> t1(2,3);
  t1.setConstant(3);
  vecs.push_back(t1);

  Eigen::Tensor<float, 2, Eigen::RowMajor> t2(2,5);
  t2.setConstant(5);
  vecs.push_back(t2);

  Eigen::Tensor<float, 2, Eigen::RowMajor> t3(2,8);
  t3.setConstant(8);
  vecs.push_back(t3);

  int column_size = 0;
  for (auto& t: vecs) {
    column_size += t.dimension(1);
  }
  std::cout << "column_size: " << column_size << std::endl;

  Eigen::Tensor<float, 2, Eigen::RowMajor> concat(2,column_size);
  concat.setConstant(-1);

  int startIdx0 = 0, startIdx1 = 0, extent0 = 0, extent1 = 0;
  Eigen::array<long, 2> startIdx;
  Eigen::array<long, 2> extent;
  for (auto& t: vecs) {
    startIdx = {{startIdx0, startIdx1}};
    int row_size = t.dimension(0);
    int col_size = t.dimension(1);
    extent0 = row_size;
    extent1 = col_size;
    extent = {{extent0, extent1}};
    std::cout << "(" << startIdx0 << "," << startIdx1 << "), (" << extent0 << "," << extent1 << ")" << std::endl;
    concat.slice(startIdx, extent) = t;
    startIdx1 += col_size;
  }

  extent[1] = 10000;

  std::cout << "test extent[1]: " << extent[1] << std::endl;
  
  std::cout << "concat:\n" << concat << std::endl;
}

void sum_op() {
  Eigen::ThreadPool tp(1);
  Eigen::ThreadPoolDevice d(&tp, tp.NumThreads());

  const int NDIM = 2;
  Eigen::Tensor<float, NDIM, Eigen::RowMajor> t1(2,3);
  t1.setConstant(2);

  Eigen::array<int, 1> depth_dim;
  depth_dim[0] = NDIM - 1;

  Eigen::array<int, 2> out_dims;
  out_dims[0] = 2;
  out_dims[1] = 1;
  Eigen::Tensor<float, 2, Eigen::RowMajor> t2(2, 1);
  t2.setConstant(0.1);
  t2.device(d) = t1.sum(depth_dim).eval();

  std::cout << __FUNCTION__ <<  " t1:\n" << t1 << ",\nt2=t1.sum(1):\n" << t2 << std::endl;
  std::cout << "t1.sum():\n" << t1.sum(depth_dim) << std::endl;
}

template <int NDIMS>
void reshape_dims(int max_dims, int* shape1, int* shape2, int* reshape_dims1, int* reshape_dims2, int shape1_dims, int shape2_dims, int* x) {
  for (int i = 0; i < shape1_dims; ++i) {
    reshape_dims1[i] = shape1[i];
    x[i] = shape1[i];
  }
  for (int i = shape1_dims; i < max_dims; ++i) {
    reshape_dims1[i] = 1;
    x[i] = 1;
  }
  for (int i = 0; i < shape2_dims; ++i) {
    reshape_dims2[i] = shape2[i];
  }
  for (int i = shape2_dims; i < max_dims; ++i) {
    reshape_dims2[i] = 1;
  }
}

template <int NDIMS, typename T>
void unary_map(T* in, T* out, int* in_shape, int* out_shape, int in_size, int out_size, bool need_bcast = false) {
  Eigen::array<Eigen::DenseIndex, NDIMS> in_dims, out_dims;
  for (int i = 0; i < in_size; ++i) {
    in_dims[i] = in_shape[i];
  }
  for (int i = in_size; i < NDIMS; ++i) {
    in_dims[i] = 1;
  }
  for (int i = 0; i < out_size; ++i) {
    out_dims[i] = out_shape[i];
  }
  for (int i = out_size; i < NDIMS; ++i) {
    out_dims[i] = 1;
  }

  if (in_size == out_size) {
    bool same_shape = true;
    for (int i = 0; i < in_size; ++i) {
      if (in_shape[i] != out_shape[i]) {
        same_shape = false;
        break;
      }
    }

    if (same_shape) {
      Eigen::TensorMap<Eigen::Tensor<T, NDIMS>> in_t(in, in_dims);
      Eigen::TensorMap<Eigen::Tensor<T, NDIMS>> out_t(out, out_dims);
      out_t = in_t;
    } else {
      std::runtime_error("shape not match");
    }
  } else if (in_size > out_size) { 
    // reduce sum 
    int axis = in_size - 1;
    Eigen::array<Eigen::DenseIndex, 1> depth_dim;
    depth_dim[0] = axis;
    Eigen::TensorMap<Eigen::Tensor<T, NDIMS>> in_t(in, in_dims);
    Eigen::TensorMap<Eigen::Tensor<T, NDIMS>> out_t(out, out_dims);
    out_t = in_t.sum(depth_dim).reshape(out_dims);
    std::cout << "Y:\n" << out_t << std::endl;

  } else if (in_size < out_size) {
    // broadcast 
    Eigen::array<Eigen::DenseIndex, NDIMS> reshape_dims, bcast_dims;
    for (int i = 0; i < in_size; ++i) {
      reshape_dims[i] = out_shape[i];
    }
    for (int i = in_size; i < NDIMS; ++i) {
      reshape_dims[i] = 1;
    }

    for (int i = 0; i < NDIMS; ++i) {
      bcast_dims[i] = reshape_dims[i] == 1 ? out_shape[i] : 1;
      std::cout << "bcast_dims i: " << i << ", v: " << bcast_dims[i] << std::endl;
    }

    Eigen::TensorMap<Eigen::Tensor<T, NDIMS>> in_t(in, in_dims);
    Eigen::TensorMap<Eigen::Tensor<T, NDIMS>> out_t(out, out_dims);

    std::cout << "in_t:\n" << in_t << ",\nout_t:\n" << out_t << std::endl;

    out_t = in_t.reshape(reshape_dims).broadcast(bcast_dims);
  }
}

void unary_map_test() {
  Eigen::Tensor<float, 2, Eigen::RowMajor> in(2, 3);
  //in.setConstant(2);
  Eigen::Tensor<float, 1, Eigen::RowMajor> out(2);
  out.setConstant(2);
  int in_size[2];
  in_size[0] = 2; in_size[1] = 3;
  int out_size[1];
  out_size[0] = 2;
  // rank(in) > rank(out)
  //unary_map<2, float>(in.data(), out.data(), in_size, out_size, 2, 1);
  //std::cout << __FUNCTION__ << " reduce_sum. in:\n" << in << "\nout:\n" << out << "\n"; 
  // rank(in) < rank(out)
  unary_map<2, float>(out.data(), in.data(), out_size, in_size, 1, 2);
  std::cout << __FUNCTION__ << " reduce_sum. in:\n" << out << "\nout:\n" << in << "\n"; 
}

template <int NDIMS>
void eigen_array(Eigen::array<Eigen::DenseIndex, NDIMS>& in) {
  for (int i = 0; i < NDIMS; ++i) {
    //(*in)[i] = i+1;
    in[i] = i+1;
  }
}

void eigen_array_test() {
  const int ndims = 5;
  Eigen::array<Eigen::DenseIndex, ndims> x;
  eigen_array<ndims>(x);
  for (int i = 0; i < ndims; ++i) {
    std::cout << "i: " << i << ", dim: " << x[i] << std::endl;
  }
}

void tensor_one_operator() {
  // [Eigen::Tensor] 
  std::cout << "\n======================= [Eigen::Tensor] ====================\n" << std::endl;
  const int d0 = 4, d1 = 5, d2 = 3;
  float* fv = new float[d0*d1*d2];
  for (int i = 0; i < d0*d1*d2; ++i) {
    fv[i] = i + 1;
  }

  Eigen::Tensor<float, 3, Eigen::RowMajor> tensor(d0, d1, d2);
  tensor.setConstant(0);
  std::cout << "[Tensor] tensor initialization:\n" << tensor << std::endl; 
  auto norm_fn = [](float x, float eps =16.f) -> float {
    return (x < -eps) ? -eps : ((x > eps) ? eps : x);
  };
  std::cout << "[Tensor] tensor + 1.0f:\n" << tensor + 1.0f << std::endl; 

  //CPUDevice d;
  Eigen::Tensor<float, 3, Eigen::RowMajor> tensor_logistic(d0, d1, d2);
  tensor_logistic = ((-tensor.unaryExpr(norm_fn)).exp() + 1.0f).inverse();
  /*
  Eigen::ThreadPool tp(2);
  Eigen::ThreadPoolDevice d(&tp, tp.NumThreads());
  tensor_logistic.device(d) = ((-tensor.unaryExpr(norm_fn)).exp() + 1.0f).inverse();
  */
  //tensor_logistic.device(d) = (tensor_logistic + 1.0f).inverse();
  /*
  std::cout << "----------- tensor logistic -----------\n";
  auto tensor_logistic = ((-tensor.unaryExpr(norm_fn)).exp() + 1.0f).inverse();
  */
  std::cout << tensor_logistic << std::endl;
  std::cout << "----------- tensor log -----------\n";
  tensor.setConstant(8.0f);
  std::cout << tensor.log() / static_cast<float>(log(2)) << std::endl;
  std::cout << "----------- tensor tanh(90) -----------\n";
  tensor.setConstant(60.0f);
  std::cout << tensor.tanh() << std::endl;

}

int main(int argc, char** argv) {
  //tensormap_basic();
  tensor_basic();
  //tensor_one_operator();
  //tensor_binary_operator();
  //add_op();
  //sum_op();
  //concat_op();
  //unary_map_test();
  //eigen_array_test();
  return 0;
}

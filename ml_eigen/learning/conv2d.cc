#include <Eigen/Dense>
#include <unsupported/Eigen/CXX11/Tensor>
#include <iostream>

typedef Eigen::Tensor<float, 4, Eigen::RowMajor> Tensor4F;
typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> MatrixF;

void init_input(Tensor4F& input);
void init_filter(Tensor4F& input);

void conv2d(Tensor4F& input, Tensor4F& filter, int strides) {
  int in_channels_size = filter.dimension(2);
  int out_channels_size = filter.dimension(3);
  for (int out_idx = 0; out_idx < out_channels_size; ++out_idx) {
    for (int in_idx = 0; in_idx < in_channels_size; ++in_idx) {
       // TODO 每一个Input Volume与Filter做内积
    }
  }
}

// conv2d 如何反向求导?

int main() {
  int batch_size = 1;
  const int in_height = 7;
  const int in_width = 7;
  int in_channels = 3;

  float* fv = new float[batch_size * in_height * in_width * in_channels];
  Eigen::TensorMap<const Tensor4F> input_tensormap(fv, batch_size, in_height, in_width, in_channels);
  Tensor4F input = input_tensormap;
  
  init_input(input);
  for (int i = 0; i < in_channels; ++i) {
    Eigen::array<long, 4> startIdx = {{0, 0, 0, i}};
    Eigen::array<long, 4> extent = {{1, 7, 7, 1}};
    Tensor4F tensor_i = input.slice(startIdx, extent);
    MatrixF matrix_i = Eigen::Map<const MatrixF>(tensor_i.data(), in_height, in_width);
    std::cout << "[Matrix] matrix_" << i << ":\n" << matrix_i << std::endl;
  }

  int filter_height = 3;
  int filter_width = 3;
  int out_channels = 2;
  float* ff = new float[filter_height * filter_width * in_channels * out_channels];
  Eigen::TensorMap<const Tensor4F> filter_tensormap(ff, filter_height, filter_width, in_channels, out_channels); 
  Tensor4F filter = filter_tensormap;

  init_filter(filter);
  for (int i = 0; i < out_channels; ++i) {
    for (int j = 0; j < in_channels; ++j) {
      Eigen::array<long, 4> startIdx = {{0, 0, j, i}};
      Eigen::array<long, 4> extent = {{filter_height, filter_width, 1, 1}};
      Tensor4F sliced_ij = filter.slice(startIdx, extent);
      MatrixF matrix_ij = Eigen::Map<const MatrixF>(sliced_ij.data(), filter_height, filter_width);
      std::cout << "[Matrix] filter[" << i << "][" << j << "]:\n" << matrix_ij << std::endl;
    }
  }

  int strides = 4; // step size  

  //conv2d(input_tensormap, filter, strides);
};


void init_input(Tensor4F& input) {
  input(0, 1, 2, 0) = 1.0f;
  input(0, 1, 3, 0) = 1.0f;
  input(0, 1, 4, 0) = 2.0f;
  input(0, 1, 5, 0) = 2.0f;
  input(0, 2, 2, 0) = 1.0f;
  input(0, 2, 3, 0) = 1.0f;
  input(0, 3, 1, 0) = 1.0f;
  input(0, 3, 2, 0) = 1.0f;
  input(0, 3, 4, 0) = 1.0f;
  input(0, 4, 1, 0) = 1.0f;
  input(0, 4, 3, 0) = 1.0f;
  input(0, 4, 4, 0) = 1.0f;
  input(0, 4, 5, 0) = 1.0f;
  input(0, 5, 2, 0) = 2.0f;
  input(0, 5, 4, 0) = 1.0f;
  input(0, 1, 1, 1) = 1.0f;
  input(0, 1, 2, 1) = 1.0f;
  input(0, 1, 3, 1) = 1.0f;
  input(0, 1, 4, 1) = 2.0f;
  input(0, 2, 2, 1) = 2.0f;
  input(0, 2, 3, 1) = 1.0f;
  input(0, 2, 4, 1) = 1.0f;
  input(0, 2, 5, 1) = 2.0f;
  input(0, 3, 1, 1) = 1.0f;
  input(0, 3, 2, 1) = 2.0f;
  input(0, 3, 5, 1) = 2.0f;
  input(0, 4, 2, 1) = 2.0f;
  input(0, 4, 3, 1) = 1.0f;
  input(0, 4, 4, 1) = 2.0f;
  input(0, 4, 5, 1) = 1.0f;
  input(0, 5, 1, 1) = 2.0f;
  input(0, 5, 3, 1) = 1.0f;
  input(0, 5, 4, 1) = 2.0f;
  input(0, 1, 1, 2) = 2.0f;
  input(0, 1, 3, 2) = 2.0f;
  input(0, 1, 5, 2) = 2.0f;
  input(0, 2, 3, 2) = 1.0f;
  input(0, 2, 4, 2) = 2.0f;
  input(0, 2, 5, 2) = 1.0f;
  input(0, 3, 1, 2) = 1.0f;
  input(0, 3, 3, 2) = 2.0f;
  input(0, 3, 4, 2) = 2.0f;
  input(0, 3, 5, 2) = 1.0f;
  input(0, 4, 1, 2) = 2.0f;
  input(0, 4, 3, 2) = 2.0f;
  input(0, 5, 3, 2) = 1.0f;
  input(0, 5, 4, 2) = 1.0f;
  input(0, 5, 5, 2) = 2.0f;
}

void init_filter(Tensor4F& filter) {
  filter(0, 0, 0, 0) = 1.0f;
  filter(0, 1, 0, 0) = 1.0f;
  filter(0, 2, 0, 0) = -1.0f;
  filter(1, 0, 0, 0) = -1.0f;
  filter(1, 2, 0, 0) = 1.0f;
  filter(2, 0, 0, 0) = -1.0f;
  filter(2, 1, 0, 0) = -1.0f;
  filter(0, 0, 1, 0) = -1.0f;
  filter(0, 2, 1, 0) = -1.0f;
  filter(1, 2, 1, 0) = -1.0f;
  filter(2, 0, 1, 0) = 1.0f;
  filter(2, 1, 1, 0) = -1.0f;
  filter(0, 1, 2, 0) = 1.0f;
  filter(1, 0, 2, 0) = 1.0f;
  filter(1, 2, 2, 0) = 1.0f;
  filter(2, 1, 2, 0) = -1.0f;
  filter(2, 2, 2, 0) = 1.0f;
  filter(0, 0, 0, 1) = -1.0f;
  filter(0, 1, 0, 1) = -1.0f;
  filter(1, 0, 0, 1) = -1.0f;
  filter(1, 1, 0, 1) = 1.0f;
  filter(2, 0, 0, 1) = -1.0f;
  filter(2, 1, 0, 1) = 1.0f;
  filter(0, 0, 1, 1) = 1.0f;
  filter(0, 1, 1, 1) = -1.0f;
  filter(1, 0, 1, 1) = -1.0f;
  filter(1, 2, 1, 1) = -1.0f;
  filter(2, 0, 1, 1) = -1.0f;
  filter(0, 0, 2, 1) = -1.0f;
  filter(0, 2, 2, 1) = 1.0f;
  filter(1, 0, 2, 1) = 1.0f;
  filter(1, 2, 2, 1) = 1.0f;
  filter(2, 1, 2, 1) = -1.0f;
}

#include <Eigen/Dense>
#include <unsupported/Eigen/CXX11/Tensor>
#include <vector>
#include <iostream>

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
  auto mapped = Eigen::TensorMap<Eigen::Tensor<int, 3>>(v.data(), d0, d1, d2);

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
  Eigen::array<long, 3> extent = {{d0-1, d1-1, d2-1}};
  Eigen::Tensor<float, 3, Eigen::RowMajor> sliced_tensor = tensor.slice(startIdx, extent);
  std::cout << "[Tensor] sliced_tensor:\n" << sliced_tensor << std::endl;

  // element-wise product 
  Eigen::Tensor<float, 3, Eigen::RowMajor> t1 = tensor * tensor;
  std::cout << "[Tensor] Tensor element-wise product:\n" << t1 << std::endl;
  // TensorFixedSize
  Eigen::TensorFixedSize<float, Eigen::Sizes<d0, d1, d2>, Eigen::RowMajor> tfs = tensor * 0.1f;
  std::cout << "[Tensor] TensorFixedSize element-wise product:\n" << tfs << std::endl;

  // Eigen::Tensor --> Eigen::Matrix 
  MatrixF matrixf(d0, d1 * d2);
  matrixf = Eigen::Map<const MatrixF>(tmap.data(), d0, d1 * d2);
  std::cout << "[Tensor] MatrixF matrixf:\n" << matrixf << std::endl;
  std::cout << "[Tensor] MatrixF matrixf. rows: " << matrixf.rows() << ", cols: " << matrixf.cols() << std::endl; 
}

int main(int argc, char** argv) {
  tensormap_basic();
  tensor_basic();
  return 0;
}

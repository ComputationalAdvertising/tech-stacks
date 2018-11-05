/*=======================================
1. Eigen::MatrixXd   rows()/cols()/size()
2. MatrixXd * MatrixXd
3. Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> dimensions are known at compile time
4. 
=======================================*/

#include <iostream>
#include <vector>
#include <Eigen/Dense>

using namespace Eigen;

//using MatrixF = Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>  // error
typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> MatrixF;
typedef Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> MatrixI;
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> MatrixD;

void matrix_basic() {
  int size = 20, rows = 4, cols = size / rows;
  std::vector<float> v(size);
  for (int i = 0; i < size; ++i) {
    v[i] = i + 1;
  }

  auto mmap = Eigen::Map<MatrixF>(v.data(), rows, cols);
  MatrixF matrixf = mmap * 2.0f;

  std::cout << "[Matrix Basic] mmap:\n" << mmap << std::endl;
  std::cout << "[Matrix Basic] matrixf:\n" << matrixf << std::endl;
}

// 2. MatrixXd * MatrixXd 
void matrix_matmul() {

}

// 3. Eigen::Dynamic 
void matrix_dynamic(MatrixF& m) {
  //Eigen::Matrix3f m3 = Eigen::Matrix3f::Zero(3,3);
  Eigen::Matrix3f m3 = Eigen::Matrix3f::Identity(3,3);
  m3(0, 2) = 3;
  m = m3; 
  std::cout << "[EXP3] Eigen::Dynamic m =\n" << m << "\nm.row(1):\n" << m.row(1) << std::endl;
}

int main(int argc, char** argv) {
  // Basic
  matrix_basic();

  Eigen::MatrixXd m = MatrixXd::Constant(4,4,0.1);
  m(0, 1) = -1;
  m(1, 1) = m(1, 0) + m(0, 1);
  std::cout << "[EXP1] m:\n" << m << "\n[EXP1] m.rows: "<< m.rows() << ", m.cols: " << m.cols() << ", m.size: " << m.size() << std::endl;
  m.resize(2, m.size()/2);
  std::cout << "[EXP1] MatrixXd::resize:\n" << m << "\n[EXP1] m.rows: " << m.rows() << std::endl;
  std::cout << "[EXP1] MatrixXd::array:\n" << m.array() << std::endl;
  std::cout << "[EXP1] middleCols(2,cols):\n" << m.middleCols<5>(2) << std::endl;

  MatrixXd em = MatrixXd::Random(3,3);
  em = (em + MatrixXd::Constant(3, 3, 1.2)) * 50;
  std::cout << "constant:\n" << MatrixXd::Constant(3,3,1.2) << std::endl;
  std::cout << "\n=========================\n[EXP2] em =\n" << em << std::endl;
  Eigen::VectorXd v(3);
  v << 1, 2, 3;
  std::cout << "[EXP2] em * v = \n" << em * v << std::endl;  

  // 3. matrix dynamic 
  MatrixF mf;
  matrix_dynamic(mf);

  return 0;
}

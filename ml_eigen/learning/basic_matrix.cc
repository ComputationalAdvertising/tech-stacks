/*=======================================
1. Eigen::MatrixXd   rows()/cols()/size()
2. MatrixXd * MatrixXd
3. Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>  dimensions are known at compile time
4. 
=======================================*/

#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;

int main(int argc, char** argv) {
  Eigen::MatrixXd m = MatrixXd::Constant(4,4,0.1);
  m(0, 0) = 3;
  m(1, 0) = 2.5;
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
  return 0;
}

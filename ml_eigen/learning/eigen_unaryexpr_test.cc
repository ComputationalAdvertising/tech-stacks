#include <unsupported/Eigen/CXX11/Tensor>
#include "timer.h"
using namespace openmi;
#include <math.h>
#include <iostream>

int epoch = 10;

int d1=1000,d2=1000,d3=1000;
//int d1=2,d2=3,d3=3;
static constexpr int RANK = 3;

Eigen::Tensor<float, RANK, Eigen::RowMajor> tensor(d1, d2, d3);

auto log_exp = [](float x) -> float { 
  //return log(exp(x)); 
  return sin(x);
};

void eigen_unaryexpr_test() {
  tensor.setConstant(10.0f);
  Timer timer;
  Eigen::Tensor<float, RANK, Eigen::RowMajor> xx;
  for (int i = 0; i < epoch; ++i) {
    printf("i: %d\n", i);
    xx = tensor * tensor * tensor;
    printf("tensor.log.exp time: %f ms\n", timer.Elapsed() * 1.0 / 1000);
    xx = tensor.unaryExpr(log_exp);
    printf("unaryexp time: %f ms\n", timer.Elapsed() * 1.0 / 1000);
  }
  printf("unaryexpr time: %f ms\n", timer.Elapsed() * 1.0 / 1000);
  printf("xx(0,0,0): %f\n", xx(0,0,0));
}

int main(int argc, char** argv) {
  eigen_unaryexpr_test();
}

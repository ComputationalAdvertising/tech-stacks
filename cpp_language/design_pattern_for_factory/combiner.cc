#include "combiner.h"
#include "feature_op_factory.h"
#include "general_factory.h"
#include <iostream>

//REGISTER_FEATURE_OP(Combiner)
REGISTER_CLASS(Combiner, FeatureOp);

int Combiner::DoCompute() {
  std::cout << "[Combiner] DoCompute ..." << std::endl;
  return 0;
}

void Combiner::Print(const std::string& content) {
  std::cout << "[Combiner] Print content: " << content << std::endl;
}

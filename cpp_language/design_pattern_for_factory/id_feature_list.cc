#include "id_feature_list.h"
#include "feature_op_factory.h"
#include "general_factory.h"
#include <iostream>

//REGISTER_FEATURE_OP(IdFeatureList)
REGISTER_CLASS(IdFeatureList, FeatureOp);

int IdFeatureList::DoCompute() {
  std::cout << "[IdFeatureList] DoCompute ..." << std::endl;
  return 0;
}

void IdFeatureList::Print(const std::string& content) {
  std::cout << "[IdFeatureList] Print content: " << content << std::endl;
}

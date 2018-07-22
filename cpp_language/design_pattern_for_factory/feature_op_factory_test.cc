#include "feature_op_factory.h"

#include "general_factory.h"

#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** argv) {
  std::vector<std::string> feature_op_classes;
  feature_op_classes.emplace_back("Combiner");
  feature_op_classes.emplace_back("IdFeatureList");
  feature_op_classes.emplace_back("IdFeatureLis");
  for (auto& feature_op_name: feature_op_classes) {
    //FeatureOpPtr feature_op = FeatureOpFactory::Instance().CreateObj(feature_op_name);
    //feature_op->Print(feature_op_name); 
    FeatureOpPtr feature_op = GeneralFactory<FeatureOp>::Instance().CreateObj(feature_op_name);
    feature_op->Print(feature_op_name);
  }
  return 0;
}

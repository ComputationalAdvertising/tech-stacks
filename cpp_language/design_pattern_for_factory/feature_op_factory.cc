#include "feature_op_factory.h"

#include <iostream>

FeatureOpPtr FeatureOpFactory::CreateObj(const std::string& feature_op_name) {
  if (feature_op_class_.find(feature_op_name) == feature_op_class_.end()) {
    std::cout << "[FeatureOpFactory::CreateObj] " << feature_op_name << " not exists! return nullptr" << std::endl;
    return nullptr;
  }
  return feature_op_class_[feature_op_name]->CreateObj();
}

void FeatureOpFactory::RegisterFeatureOp(const std::string& feature_op_name, FeatureOpClassFactory* factory) {
  if (feature_op_class_.find(feature_op_name) != feature_op_class_.end()) {
    std::cout << "Error: feature op class has already registered. feature_op_name: " << feature_op_name  << std::endl;
    return;
  }
  std::cout << "[FeatureOpFactory::RegisterFeatureOp] feature_op_class_[" << feature_op_name << "] = factory" << std::endl;
  feature_op_class_[feature_op_name] = factory;
}


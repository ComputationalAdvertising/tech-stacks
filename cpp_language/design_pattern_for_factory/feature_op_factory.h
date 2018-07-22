#ifndef DESIGN_PATTERN_FOR_FACTORY_FEATURE_OP_FACTORY_H_
#define DESIGN_PATTERN_FOR_FACTORY_FEATURE_OP_FACTORY_H_ 

#include "feature_op.h"

#include <iostream>
#include <memory>
#include <unordered_map>

class FeatureOpClassFactory {
public:
  virtual std::shared_ptr<FeatureOp> CreateObj() = 0;
}; // FeatureOpClassFactory 

class FeatureOpFactory {
public:
  static FeatureOpFactory& Instance() {
    static FeatureOpFactory feature_factory;
    return feature_factory;
  }

  virtual std::shared_ptr<FeatureOp> CreateObj(const std::string& feature_op_name);

  virtual void RegisterFeatureOp(const std::string& feature_op_name, FeatureOpClassFactory* factory);

private:
  FeatureOpFactory() {}
  FeatureOpFactory(const FeatureOpFactory&);
  FeatureOpFactory* operator=(const FeatureOpFactory&);

private:
  std::unordered_map<std::string, FeatureOpClassFactory*> feature_op_class_;
}; // FeatureOpFactory

template<typename T>
class FeatureOpClassFactoryImpl : public FeatureOpClassFactory {
public:
  virtual std::shared_ptr<FeatureOp> CreateObj() {
    std::cout << "[FeatureOpClassFactoryImpl::CreateObj] ..." << std::endl;
    return std::make_shared<T>();
  }
}; // FeatureOpClassFactoryImpl 

class FeatureOpClassRegister {
public:
  FeatureOpClassRegister(const std::string& feature_op_name, FeatureOpClassFactory* feature_op_class_factory, FeatureOpFactory& feature_op_factory) {
    feature_op_factory.RegisterFeatureOp(feature_op_name, feature_op_class_factory);
  }
}; // class FeatureOpClassRegister 

#define REGISTER_FEATURE_OP(feature_op_class) \
    static FeatureOpClassFactoryImpl<feature_op_class> feature_op_class##_feature_op_factory;\
    static FeatureOpClassRegister feature_op_class##feature_op_register(#feature_op_class, &feature_op_class##_feature_op_factory, FeatureOpFactory::Instance());

#endif // DESIGN_PATTERN_FOR_FACTORY_FEATURE_OP_FACTORY_H_

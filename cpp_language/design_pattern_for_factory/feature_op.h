#ifndef DESIGN_PATTERN_FOR_FACTORY_FEATURE_OP_H_
#define DESIGN_PATTERN_FOR_FACTORY_FEATURE_OP_H_ 

#include <string>

// a abstract class for feature op 
class FeatureOp {
public:
  FeatureOp() {}
  virtual ~FeatureOp() {}

  virtual int DoCompute() = 0; 

  virtual void Print(const std::string& content);

private:
  bool is_debug_;
}; // class FeatureOp

typedef std::shared_ptr<FeatureOp> FeatureOpPtr;

#endif // DESIGN_PATTERN_FOR_FACTORY_FEATURE_OP_H_ 

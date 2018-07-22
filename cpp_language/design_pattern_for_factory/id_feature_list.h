#ifndef DESIGN_PATTERN_FOR_FACTORY_ID_FEATURE_LIST_H_
#define DESIGN_PATTERN_FOR_FACTORY_ID_FEATURE_LIST_H_

#include "feature_op.h"

class IdFeatureList: public FeatureOp {
public:
  IdFeatureList() {}
  virtual ~IdFeatureList() {}

  virtual int DoCompute(); 

  virtual void Print(const std::string& content);
};

#endif // DESIGN_PATTERN_FOR_FACTORY_ID_FEATURE_LIST_H_

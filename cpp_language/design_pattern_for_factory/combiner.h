#ifndef DESIGN_PATTERN_FOR_FACTORY_COMBINER_H_
#define DESIGN_PATTERN_FOR_FACTORY_COMBINER_H_

#include "feature_op.h"

class Combiner: public FeatureOp {
public:
  Combiner() {}
  virtual ~Combiner() {}

  virtual int DoCompute(); 

  virtual void Print(const std::string& content);
};

#endif // DESIGN_PATTERN_FOR_FACTORY_COMBINER_H_ 

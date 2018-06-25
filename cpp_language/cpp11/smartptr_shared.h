#include <iostream>
#include <memory>
#include <unordered_map>

class Variable {
public:
  Variable(int a = -1): a_(a) {} 
  ~Variable() {}
  inline void set_a(int v) { a_ = v; }
  inline int get_a() { return a_; }
private:
  int a_;
}; // class Variable 
using VariablePtr = std::shared_ptr<Variable>;

// variable manager
class VariableMgr {
public:
  VariableMgr() {} 
  ~VariableMgr() { variable_map_.clear(); } 
  
  inline VariablePtr create(const std::string& name) { 
    auto var = variable_map_.find(name);
    if (var == variable_map_.end()) {
      auto var = variable_map_[name] = std::make_shared<Variable>(1000);
      return var;
    } else {
      std::cout << "error name: " << name << " has exists in variable_map_\n";
    }
    return variable_map_[name];
  }

  inline void print() {
    auto iter = variable_map_.begin();
    while (iter != variable_map_.end()) {
      std::cout << "name: " << iter->first << ", a: " << iter->second->get_a() << std::endl;
      iter++;
    }
  }

private:
  std::unordered_map<std::string, VariablePtr> variable_map_;
};
using VariableMgrPtr = std::shared_ptr<VariableMgr>; 

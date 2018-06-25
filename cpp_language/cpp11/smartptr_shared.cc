#include <vector>
#include "smartptr_shared.h"


int main(int argc, char** argv) {
  std::vector<VariablePtr> vec;
  for (auto i = 0; i < 10; ++i) {
    vec.emplace_back(std::make_shared<Variable>(i));
    std::cout << "i: " << vec.back()->get_a() << std::endl;
  }
  VariablePtr ptr = vec[4];
  ptr->set_a(44); 
  for (auto i = 0; i < 10; ++i) {
    std::cout << "after i: " << vec[i]->get_a() << std::endl;
  }

  std::cout << "test VariableMgr ...." << std::endl;
  VariableMgrPtr var_manager_  = std::make_shared<VariableMgr>();
  VariablePtr ptr1 = var_manager_->create(std::string("ptr1"));
  VariablePtr ptr2 = var_manager_->create(std::string("ptr2"));
  std::cout << "before var_manager_ info ..." << std::endl;
  var_manager_->print();
  std::cout << "update ptr1=11111, ptr2=22222 ...." << std::endl;
  ptr1->set_a(11111);
  ptr2->set_a(22222);
  var_manager_->print();

  return 0;
}

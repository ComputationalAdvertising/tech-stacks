#include <iostream>
#include <memory>
#include <string>

// smart ptr for string
typedef std::shared_ptr<std::string> StringPtr;

int main() {
  StringPtr str = std::make_shared<std::string>("SmartPtr String");
  std::cout << "str: " << *str.get() << std::endl;
  return 0;
}

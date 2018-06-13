#include <functional>
#include <iostream>
#include <string>

std::function<int(const std::string& str1, const int& val)> Handler;

int impl(const std::string& str, const int& val, int version) {
  std::cout << "[impl] str: " << str << ", val: " << val << ", version: " << version << std::endl;
  return val + version;
}

int main(int argc, char** argv) {
  int version = 1;
  Handler = [version](const std::string& str, const int& val) {
    return impl(str, val, version);
  };

  std::string str("content");
  int val = 10;
  Handler(str, val);
  return 0;
}

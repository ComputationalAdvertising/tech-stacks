#include <algorithm>
#include <array>
#include <cstring>
#include <iostream>


void array_iterator() {
  std::array<int, 5> test{ {2, 16, 88, 34, 50} };  // C++11 requires {{}}, C++14 not
  std::cout << "[array::print] ";
  for (const auto& elem: test) {
    std::cout << " " << elem;
  }
  std::cout << std::endl;

  std::array<int, 5> myarray = {2, 16, 88, 34, 50};
  // array::begin/end
  std::cout << "[array::begin/end] myarray containers: ";
  for (auto it = myarray.begin(); it != myarray.end(); ++it) {
    std::cout << ' ' << *it;
  }
  std::cout << std::endl; 

  // array::rbegin/rend (reverse)
  std::cout << "[array::rbegin/rend] myarray containers: ";
  for (auto it = myarray.rbegin(); it != myarray.rend(); ++it) {
    std::cout << ' ' << *it;
  }
  std::cout << std::endl;  
}

void array_capacity() {
  std::array<int, 5> myarray = {2, 16, 88, 34, 50};
  std::cout << "[array::capacity] size: " << myarray.size() 
    << ", sizeof(myarray): " << sizeof(myarray) 
    << ", max_size: " << myarray.max_size() 
    << ", empty: " << myarray.empty() << std::endl;
}

void array_element_access() {
  std::array<int, 5> myarray = {2, 16, 88, 34, 50};
  array_iterator();
  std::cout << "[array::at] at(2): " << myarray.at(2) << ", myarray[2]: " << myarray[2] << std::endl;
  std::cout << "[array::front/back] front: " << myarray.front() << ", back: " << myarray.back() << std::endl; 
  myarray.front() = 1000;
  std::cout << "[array::front] update front: " << myarray.front() << std::endl; 

  // array::data 
  const char* cstr = "Test";
  std::cout << "strlen(cstr): " << std::strlen(cstr) << std::endl;
  std::array<char, 5> charray;  // strlen(cstr) + '\0'
  std::memcpy(charray.data(), cstr, 5);
  std::cout << "[array::data] data: " << charray.data() << std::endl;
}

void array_sort() { 
  std::array<int, 5> myarray = {2, 16, 88, 34, 50};
  std::cout << "[sort] before: ";
  for (auto& item: myarray) {
    std::cout << ' ' << item;
  }
  std::cout << std::endl;

  std::sort(myarray.begin(), myarray.end());
  
  std::cout << "[sort] after: ";
  for (auto& item: myarray) {
    std::cout << ' ' << item;
  }
  std::cout << std::endl;
}

int main(int argc, char** argv) {
  array_iterator(); 
  //array_capacity();
  //array_element_access();
  //array_sort();
  return 0;
}

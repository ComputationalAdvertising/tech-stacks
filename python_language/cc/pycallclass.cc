#include <iostream>
using namespace std;

class PyCallLib {
  public:
    void display();
    int display(int a);
};

void PyCallLib::display() {
  std::cout << "[C++] PyCallLib::display() ..." << std::endl;
}

int PyCallLib::display(int a) {
  std::cout << "[C++] PyCallLib::display(int " << a << ") ..." << std::endl;
  return a + 1;
}

extern "C" {
  PyCallLib obj;
  void display() {
    obj.display();
  }

  int display_int(int a) {
    return obj.display(a);
  }
}

#include <tensorflow/core/platform/env.h>
#include <tensorflow/core/public/session.h>
#include <iostream>

using namespace std;
using namespace tensorflow;

int main(int argc, char** argv) {
  Session* session;
  Status status = NewSession(SessionOptions(), &session);
  if (! status.ok()) {
    cout << status.ToString() << "\n";
    return 1;
  }
  cout << "Session successfully created." << std::endl;
  return 0;
}

include "shared.thrift"

namespace cpp zy

struct Instance {
  1: i64 seq_id = 0,
  2: string line,
  3: binary data
}

# Define a service
service Predictor extends shared.SharedService {
  string ping(),
  Instance get_instance(1:Instance inst),
  double predict(1:Instance inst),
  void TestBinary(1:binary bin)
}

#include <Adder.h>

class MockAdder: public Adder {
public:
  MOCK_METHOD2(add, int(int, int));
};
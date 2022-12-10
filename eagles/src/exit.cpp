#include "bird.h"

class Exitter : public Bird {
 public:
  Exitter() { Initialize(); }
  ~Exitter() {}

  void Action() override { SendMessage(BIRD_CALL_MOTHER, -1); }
};

int main() {
  Exitter exitter;
  exitter.Action();
  return 0;
}

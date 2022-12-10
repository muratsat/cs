#pragma once
#include "bird.h"

class Eaglet : public Bird {
 public:
  Eaglet();
  ~Eaglet();

  void Action() override;

 private:
  void Eat();
};

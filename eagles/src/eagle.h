#pragma once
#include "bird.h"

class Eagle : public Bird {
 public:
  Eagle();
  Eagle(int n);
  ~Eagle();

  void Action() override;

 private:
  int n_food_ = 5;

  void FillBowl();
};

#include "eagle.h"

#include <stdio.h>

#include "bird.h"

Eagle::Eagle() { Initialize(); }
Eagle::Eagle(int n) : n_food_(n) { Initialize(); }
Eagle::~Eagle() { Uninitialize(); }

void Eagle::FillBowl() {
  printf("[Mother %d] filling the bowl\n", pid_);
  SendMessage(BIRD_FOOD_READY, n_food_);
}

void Eagle::Action() {
  printf("[Mother %d] started \n", pid_);
  FillBowl();

  while (true) {
    int food_left = ReceiveMessage(BIRD_CALL_MOTHER);
    if (food_left < 0) {
      break;
    }
    FillBowl();
  }

  printf("[Mother %d] done \n", pid_);
}

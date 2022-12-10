#include "eaglet.h"

#include <stdio.h>
#include <unistd.h>

#include "bird.h"

Eaglet::Eaglet() { Initialize(); }
Eaglet::~Eaglet() {}

void Eaglet::Eat() {
  // send message
  int food_left = ReceiveMessage(BIRD_FOOD_READY);
  printf("[Eaglet %d] food left: %d\n", pid_, food_left);

  if (food_left == 0) {
    printf("[Eaglet %d] calling mother\n", pid_);
    SendMessage(BIRD_CALL_MOTHER, 0);
  } else {
    SendMessage(BIRD_FOOD_READY, food_left - 1);
    printf("[Eaglet %d] ate, going to sleep\n", pid_);
  }
}

void Eaglet::Action() {
  printf("[Eaglet %d] started \n", pid_);
  unsigned int sleep_time = 3;
  while (true) {
    Eat();
    sleep(sleep_time);
  }
}

#include <stdio.h>
#include <unistd.h>

#include "eaglet.h"

int main() {
  fork();  // create a copy of the process
  Eaglet eaglet;
  eaglet.Action();

  return 0;
}

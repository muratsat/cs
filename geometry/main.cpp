#include <iostream>

#include "circle.hpp"
#include "line.hpp"
#include "point.hpp"
#include "ray.hpp"
#include "segment.hpp"
#include "shape.hpp"

bool Nand(bool x, bool y) { return !(x && y); }

int main() {
  Point center(0, 0);
  Circle circle(center, 3);

  Point a(-6, 2);
  Point b(6, 2);
  Segment ab(a, b);

  std::cout << circle.CrossesSegment(ab) << '\n';

  return 0;
}

/*
 9 . . . . . . . . .
 8 . . . . . d . . .
 7 . . . . . . . . .
 6 . . . c . . . . .
 5 . . . . . . . . .
 4 . . . b . . . . .
 3 . . . . . . . . .
 2 . a . . . . . . .
 1 . . . . . . . . .
   1 2 3 4 5 6 7 8 8

  Point a(2, 2);
  Point b(4, 4);
  Point c(4, 6);
  Point d(6, 8);
*/
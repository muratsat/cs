#pragma once
#include <cstdint>

#include "shape.hpp"
#include "vector.hpp"

class Point : public IShape {
 public:
  Point();
  Point(const Vector& v);
  Point(int64_t x, int64_t y);
  ~Point();

  // проверка, содержит ли фигура точку
  bool ContainsPoint(const Point& point) const override;

  // проверка, пересекает ли отрезок фигуру
  bool CrossesSegment(const Segment& segment) const override;

  // вернуть указатель на копию фигуры
  Point* Clone() const override;

  int64_t GetX() const;
  int64_t GetY() const;

  friend Vector operator-(const Point& first, const Point& second);
};

#pragma once
#include <cstdint>

#include "point.hpp"
#include "segment.hpp"
#include "shape.hpp"
#include "vector.hpp"

class Circle : public IShape {
 public:
  Circle();
  Circle(const Point& center, int64_t radius);
  ~Circle();

  // проверка, содержит ли фигура точку
  bool ContainsPoint(const Point& point) const override;

  // проверка, пересекает ли отрезок фигуру
  bool CrossesSegment(const Segment& segment) const override;

  // вернуть указатель на копию фигуры
  Circle* Clone() const override;

  Point GetCentre() const;
  int64_t GetRadius() const;

 private:
  int64_t radius_ = 0;
};

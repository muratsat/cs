#pragma once
#include <cstdint>

#include "point.hpp"
#include "shape.hpp"
#include "vector.hpp"

class Segment : public IShape {
 public:
  Segment();
  Segment(const Point& start, const Point& end);
  ~Segment();

  // проверка, содержит ли фигура точку
  bool ContainsPoint(const Point& point) const override;

  // проверка, пересекает ли отрезок фигуру
  bool CrossesSegment(const Segment& segment) const override;

  // вернуть указатель на копию фигуры
  Segment* Clone() const override;

  // get start of segment
  Point GetA() const;

  // get end of segment
  Point GetB() const;

 private:
  Vector direction_vector_;
};

#pragma once
#include <cstdint>

#include "point.hpp"
#include "shape.hpp"
#include "vector.hpp"

class Ray : public IShape {
 public:
  Ray();
  Ray(const Point& start, const Point& end);
  ~Ray();

  // проверка, содержит ли фигура точку
  bool ContainsPoint(const Point& point) const override;

  // проверка, пересекает ли отрезок фигуру
  bool CrossesSegment(const Segment& segment) const override;

  // вернуть указатель на копию фигуры
  Ray* Clone() const override;

  // get endpoint
  Point GetA() const;

  // get direction vector
  Vector GetDirection() const;

 private:
  Vector direction_vector_;
};

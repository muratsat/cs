#pragma once
#include <cstdint>

#include "point.hpp"
#include "shape.hpp"
#include "vector.hpp"

class Line : public IShape {
 public:
  Line();
  Line(const Point& start, const Point& end);
  ~Line();

  // проверка, содержит ли фигура точку
  bool ContainsPoint(const Point& point) const override;

  // проверка, пересекает ли отрезок фигуру
  bool CrossesSegment(const Segment& segment) const override;

  // вернуть указатель на копию фигуры
  Line* Clone() const override;

  // коэффициент A уравнения прямой Ax + By + C
  int64_t GetA() const;

  // коэффициент B уравнения прямой Ax + By + C
  int64_t GetB() const;

  // коэффициент C уравнения прямой Ax + By + C
  int64_t GetC() const;

 private:
  Vector direction_vector_;
};

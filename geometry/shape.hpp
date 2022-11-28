#pragma once
#include "vector.hpp"

class Point;

class Segment;

class IShape {
 public:
  IShape() {}
  virtual ~IShape() = default;

  // сдвиг фигуры на соответствующий вектор
  void Move(const Vector& shift) { base_ += shift; }

  // проверка, содержит ли фигура точку
  virtual bool ContainsPoint(const Point& point) const = 0;

  // проверка, пересекает ли отрезок фигуру
  virtual bool CrossesSegment(const Segment& segment) const = 0;

  // вернуть указатель на копию фигуры
  virtual IShape* Clone() const = 0;

 protected:
  Vector base_;
};

#include "point.hpp"

#include <cstdint>

#include "segment.hpp"

Point::Point() {}
Point::Point(const Vector& v) { base_ = v; }
Point::Point(int64_t x, int64_t y) { base_ = Vector(x, y); }
Point::~Point() {}

bool Point::ContainsPoint(const Point& point) const {
  return base_ == point.base_;
}

bool Point::CrossesSegment(const Segment& segment) const {
  const Point& p = *this;
  Vector va = segment.GetA() - p;
  Vector vb = segment.GetB() - p;
  return (va ^ vb) == 0 && (va * vb) <= 0;
}

Point* Point::Clone() const { return new Point(base_); }

int64_t Point::GetX() const { return base_.GetX(); }
int64_t Point::GetY() const { return base_.GetY(); }

Vector operator-(const Point& first, const Point& second) {
  return Vector(first.GetX() - second.GetX(), first.GetY() - second.GetY());
}

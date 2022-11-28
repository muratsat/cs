#include "line.hpp"

#include <cstdint>
#include <iostream>

#include "point.hpp"
#include "segment.hpp"
#include "shape.hpp"
#include "vector.hpp"

Line::Line() {}
Line::Line(const Point& start, const Point& end) {
  base_ = Vector(start.GetX(), start.GetY());
  direction_vector_ = end - start;
}
Line::~Line() {}

bool Line::ContainsPoint(const Point& point) const {
  Vector v = point - base_;
  return (v ^ direction_vector_) == 0;
}

bool Line::CrossesSegment(const Segment& segment) const {
  Point a = segment.GetA();
  Point b = segment.GetB();
  if (ContainsPoint(a) || ContainsPoint(b)) {
    return true;
  }

  const Vector& start = base_;
  const Vector& end = base_ + direction_vector_;

  int64_t cross_a = (end - a) ^ (start - a);
  int64_t cross_b = (end - b) ^ (start - b);

  // if orientations are different,
  // then they have opposite signs
  return cross_a * cross_b < 0;
}

Line* Line::Clone() const { return new Line(base_, base_ + direction_vector_); }

int64_t Line::GetA() const {
  Point end = base_ + direction_vector_;
  return base_.GetY() - end.GetY();
}

int64_t Line::GetB() const {
  Point end = base_ + direction_vector_;
  return end.GetX() - base_.GetX();
}

int64_t Line::GetC() const {
  Point end = base_ + direction_vector_;
  return base_.GetX() * end.GetY() - end.GetX() * base_.GetY();
}
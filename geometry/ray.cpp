#include "ray.hpp"

#include <cstdint>
#include <iostream>

#include "point.hpp"
#include "segment.hpp"
#include "shape.hpp"
#include "vector.hpp"

Ray::Ray() {}
Ray::Ray(const Point& start, const Point& end) {
  base_ = Vector(start.GetX(), start.GetY());
  direction_vector_ = end - start;
}
Ray::~Ray() {}

bool Ray::ContainsPoint(const Point& point) const {
  Vector v = point - base_;
  return (v ^ direction_vector_) == 0 && (v * direction_vector_) >= 0;
}

bool Ray::CrossesSegment(const Segment& segment) const {
  const Vector& d1 = direction_vector_;
  const Vector& d2 = segment.GetB() - segment.GetA();

  if ((d1 ^ d2) == 0) {
    // segments are collinear;
    return ContainsPoint(segment.GetA()) || ContainsPoint(segment.GetB());
  }

  const Vector& b1 = base_;
  const Vector& b2 = segment.GetA() - Point(0, 0);
  // b1 + d1 * s1 = b2 + d2 * s2;
  // if ray can be continued to intersect the segment,
  // then 0 <= s1 and 0 <= s2 <= 1

  double s1 = (double)((b2 - b1) ^ d2) / (double)(d1 ^ d2);
  double s2 = (double)((b1 - b2) ^ d1) / (double)(d2 ^ d1);

  return 0 <= s1 && 0 <= s2 && s2 <= 1;
  return false;
}

Ray* Ray::Clone() const { return new Ray(base_, base_ + direction_vector_); }

Point Ray::GetA() const { return base_; }

Vector Ray::GetDirection() const { return direction_vector_; }
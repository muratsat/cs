#include "segment.hpp"

#include <cstdint>
#include <iostream>

#include "point.hpp"
#include "shape.hpp"
#include "vector.hpp"

Segment::Segment() {}
Segment::Segment(const Point& start, const Point& end) {
  base_ = Vector(start.GetX(), start.GetY());
  direction_vector_ = end - start;
}
Segment::~Segment() {}

bool Segment::ContainsPoint(const Point& point) const {
  return point.CrossesSegment(*this);
}

bool Segment::CrossesSegment(const Segment& segment) const {
  const Vector& d1 = direction_vector_;
  const Vector& d2 = segment.direction_vector_;

  if ((d1 ^ d2) == 0) {
    // segments are collinear;
    bool cross = ContainsPoint(segment.GetA()) ||
                 ContainsPoint(segment.GetB()) ||
                 segment.ContainsPoint(GetA()) || segment.ContainsPoint(GetB());
    return cross;
  }

  const Vector& b1 = base_;
  const Vector& b2 = segment.base_;
  // b1 + d1 * s1 = b2 + d2 * s2;
  // if segments intersect,
  // then 0 <= s1 <= 1 and 0 <= s2 <= 1

  double s1 = (double)((b2 - b1) ^ d2) / (double)(d1 ^ d2);
  double s2 = (double)((b1 - b2) ^ d1) / (double)(d2 ^ d1);

  return 0 <= s1 && s1 <= 1 && 0 <= s2 && s2 <= 1;
}

Segment* Segment::Clone() const { return new Segment(GetA(), GetB()); }

// get start of segment
Point Segment::GetA() const { return base_; }

// get end of segment
Point Segment::GetB() const { return base_ + direction_vector_; }
#include "circle.hpp"

#include <cstdint>

#include "line.hpp"
#include "point.hpp"
#include "segment.hpp"

Circle::Circle() {}
Circle::Circle(const Point& center, int64_t radius) : radius_(radius) {
  base_ = Vector(center.GetX(), center.GetY());
}
Circle::~Circle() {}

static int64_t DistSquared(const Point& p1, const Point& p2) {
  Vector v = p2 - p1;
  return v.GetX() * v.GetX() + v.GetY() * v.GetY();
}

bool Circle::ContainsPoint(const Point& point) const {
  int64_t dist_squared = DistSquared(GetCentre(), point);
  return dist_squared <= radius_ * radius_;
}

// Circle crosses segment if
// the segment touches the circle
// or distance from center to segment is less than radius
// let O be the center of the square
// then H * AB = 2S,
// where H is distance from O to the segment AB
// and S is the area of triangle AOB
// if we square the expression, we will get:
// H^2 * AB^2 = 4S^2  ==>  H^2 = 4S^2 / AB^2
// we need H^2 <= R^2 or:
// (2S)^2 / AB^2 < R^2
// (2S)^2 <= R^2 * AB^2
// if the distance is less or equal to radius,
// then we check whether AB crosses the line
// that is perpendicular to AB and contains the center of the circle
bool Circle::CrossesSegment(const Segment& segment) const {
  Point a = segment.GetA();
  Point b = segment.GetB();
  Point o = GetCentre();
  int64_t oa_len = DistSquared(a, o);
  int64_t ob_len = DistSquared(b, o);
  int64_t r_sqr = GetRadius() * GetRadius();
  if (oa_len == r_sqr || ob_len == r_sqr) {
    return true;
  }
  bool is_a_inside = oa_len < r_sqr;
  bool is_b_inside = ob_len < r_sqr;
  if (is_a_inside && is_b_inside) {
    return false;
  }
  if (is_a_inside != is_b_inside) {
    return true;
  }
  Vector oa = a - o;
  Vector ob = b - o;
  int64_t double_area_squared = (oa ^ ob) * (oa ^ ob);
  Vector ab = b - a;
  int64_t ab_squared = ab.GetX() * ab.GetX() + ab.GetY() * ab.GetY();
  if (double_area_squared > r_sqr * ab_squared) {
    return false;
  }
  Line line_ab(a, b);
  Vector ab_normal_vector(line_ab.GetA(), line_ab.GetB());
  Line normal_line(base_, base_ + ab_normal_vector);
  return normal_line.CrossesSegment(segment);
}

Circle* Circle::Clone() const { return new Circle(base_, radius_); }

Point Circle::GetCentre() const { return base_; }

int64_t Circle::GetRadius() const { return radius_; }

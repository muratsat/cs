#pragma once
#include <cstdint>

// Класс Vector для вектора на плоскости
class Vector {
 public:
  // Конструктор по умолчанию (создает нулевой вектор)
  Vector() {}
  // Конструктор от двух целочисленных переменных
  // (создает вектор с соответствующими координатами)
  Vector(int64_t x, int64_t y) : x_(x), y_(y) {}
  ~Vector() {}

  // Оператор * для скалярного произведения
  int64_t operator*(const Vector& v) const { return x_ * v.x_ + y_ * v.y_; }

  // Оператор ^ для векторного произведения
  // this(x1, y1),  v(x2, y2)
  //  | x1 x2 |
  //  | y1 y2 |
  // det = x1 * y2 - y1 * x2;
  //
  int64_t operator^(const Vector& v) const { return x_ * v.y_ - y_ * v.x_; }

  // Операторы сложения/разности с другим вектором,
  // соответственно реализовать операторы += и -=
  Vector& operator+=(const Vector& v) {
    x_ += v.x_;
    y_ += v.y_;
    return *this;
  }

  Vector& operator-=(const Vector& v) {
    x_ -= v.x_;
    y_ -= v.y_;
    return *this;
  }

  friend Vector operator+(const Vector& left, const Vector& right) {
    Vector res = left;
    res += right;
    return res;
  }

  friend Vector operator-(const Vector& left, const Vector& right) {
    Vector res = left;
    res -= right;
    return res;
  }

  // Оператор умножения на число (сделать так, чтобы были допустимы как
  // умножение вектора на число, так и числа на вектор), реализовать оператор *=
  Vector& operator*=(int64_t scalar) {
    x_ *= scalar;
    y_ *= scalar;
    return *this;
  }

  friend Vector operator*(const Vector& v, int64_t scalar) {
    Vector res = v;
    res *= scalar;
    return res;
  }

  friend Vector operator*(int64_t scalar, const Vector& v) {
    Vector res = v;
    res *= scalar;
    return res;
  }

  // Унарный оператор минус для получения вектора в противоположном направлении
  Vector& operator-() {
    x_ = -x_;
    y_ = -y_;
    return *this;
  }
  Vector operator-() const { return Vector(-x_, -y_); }

  // Методы GetX() и GetY() для получения соответствующих координат
  int64_t GetX() const { return x_; }
  int64_t GetY() const { return y_; }

  bool operator==(const Vector& to_cmp) const {
    return (x_ == to_cmp.x_ && y_ == to_cmp.y_);
  }

 private:
  int64_t x_ = 0;
  int64_t y_ = 0;
};

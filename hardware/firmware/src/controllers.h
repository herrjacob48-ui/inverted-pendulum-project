#pragma once

class PositionLoop {
 public:
  float update(float x, float x_dot);
  void reset() { integral_ = 0.0f; }

 private:
  float integral_ = 0.0f;
};

class AnglePid {
 public:
  float update(float angle, float angular_velocity, float target_angle);
  void reset() { integral_ = 0.0f; }

 private:
  float integral_ = 0.0f;
};

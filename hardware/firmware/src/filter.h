#pragma once

class Ema {
 public:
  explicit constexpr Ema(float alpha) : alpha_(alpha) {}

  float update(float sample) {
    value_ = alpha_ * sample + (1.0f - alpha_) * value_;
    return value_;
  }

 private:
  float alpha_;
  float value_ = 0.0f;
};

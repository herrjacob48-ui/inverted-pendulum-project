#pragma once

#include <Arduino.h>

namespace cfg {

// Pins
constexpr int ENCODER_A_PIN = 26;
constexpr int ENCODER_B_PIN = 27;
constexpr int STEP_PIN = 5;
constexpr int DIR_PIN = 18;

// Control loop timing
constexpr unsigned long LOOP_PERIOD_US = 20000;
constexpr float LOOP_DT_S = 0.02f;

// Encoder and sign conventions
constexpr float TICKS_PER_REV = 1200.0f;
constexpr float RADIANS_PER_TICK = (2.0f * PI) / TICKS_PER_REV;
constexpr float ANGLE_SIGN = -1.0f;
constexpr float VELOCITY_SIGN = -1.0f;

// Stepper drive
constexpr float STEPS_PER_METER = 4000.0f;
constexpr float FULL_THROTTLE_HZ = 9500.0f;
constexpr float MIN_SPEED_HZ = 450.0f;
constexpr float MAX_ACCEL_HZ = 950.0f;
constexpr float MIN_STEP_RATE_HZ = 50.0f;
constexpr float THROTTLE_DEADBAND = 0.02f;

// Velocity filters (exponential moving average)
constexpr float THETA_DOT_ALPHA = 0.25f;
constexpr float X_DOT_ALPHA = 0.20f;

// Inner loop: angle PID
constexpr float ANGLE_KP = 13.0f;
constexpr float ANGLE_KI = 0.0f;
constexpr float ANGLE_KD = 0.04f;
constexpr float ANGLE_INTEGRAL_LIMIT = 4.0f;

// Outer loop: position to target angle
constexpr float POS_KP = 0.04f;
constexpr float POS_KI = 0.01f;
constexpr float POS_KD = 0.1f;
constexpr float POS_INTEGRAL_ZONE_M = 0.15f;
constexpr float POS_INTEGRAL_LIMIT = 0.2f;
constexpr double MAX_TARGET_ANGLE_RAD = 3.0 * DEG_TO_RAD;

// Safety limits
constexpr double MAX_TILT_RAD = 30.0 * DEG_TO_RAD;
constexpr float TRACK_LIMIT_M = 0.50f;

// Telemetry
constexpr int TELEMETRY_DIVIDER = 5;

}  // namespace cfg

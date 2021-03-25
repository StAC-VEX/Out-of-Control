#pragma once
#include "vex.h" 

namespace Syntech {
class Devices {
public:
  static controller _controller;
  static brain _brain;
  static competition comp;
  static inertial sensor;
  static motor leftMotor;
  static motor rightMotor;
  static motor intakeMotor;
};};

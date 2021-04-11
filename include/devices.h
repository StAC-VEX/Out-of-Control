#pragma once
#include "vex.h" 

/**
 * The file for the class that holds all of the devices. Motors, sensors, controller, etc.
 * 
 * @author Bailey Moir
 */

namespace Syntech {
class Devices {
public:
  static controller _controller;
  static brain _brain;
  static competition comp;
  static inertial sensor;
  static motor leftMotor;
  static motor rightMotor;
  static motor leftIntakeMotor;
  static motor rightIntakeMotor;
};};

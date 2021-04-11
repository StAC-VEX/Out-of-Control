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
  static distance distanceSensor;
  static motor leftBMotor;
  static motor leftFMotor;
  static motor rightBMotor;
  static motor rightFMotor;
  static motor leftIntakeMotor;
  static motor rightIntakeMotor;
};};

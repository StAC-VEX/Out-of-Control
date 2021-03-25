/**
 * The starting off point of the program.
 * 
 * @author Bailey Moir
 */

#include "vex.h"
#include <cstdlib>
#include "devices.h"
#include "auton.h"

using namespace Syntech;
using namespace vex;

void vexcodeInit() {
  Devices::sensor.calibrate();  
}

 void auton() {
  waitUntil(!Devices::sensor.isCalibrating());
    
  Auton::move(100);
}

void control() {
  Devices::leftMotor.setVelocity(720 * Devices::_controller.Axis3.value(), velocityUnits::dps);
  Devices::rightMotor.setVelocity(720 * Devices::_controller.Axis2.value(), velocityUnits::dps);
}  

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Devices::comp.autonomous(auton);
  Devices::comp.drivercontrol(control);
}
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

/**
 * Initalises the devices (that need to be initalised).
 */
void vexcodeInit() {
  Devices::sensor.calibrate();  
}

/**
 * The code that runs for the autunomous.
 */
void auton() {
  waitUntil(!Devices::sensor.isCalibrating());
    
  Auton::move(100);
}

/**
 * The code that loops for user control.
 */
void control() {
  Devices::leftMotor.setVelocity(720 * Devices::_controller.Axis3.value(), velocityUnits::dps);
  Devices::rightMotor.setVelocity(720 * Devices::_controller.Axis2.value(), velocityUnits::dps);
}  

/**
 * The origin of the main thread.
 */
int main() {
  vexcodeInit();

  Devices::comp.autonomous(auton);
  Devices::comp.drivercontrol(control);
}
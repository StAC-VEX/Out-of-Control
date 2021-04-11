#include "vex.h"
#include <cstdlib>
#include "devices.h"
#include "auton.h"

using namespace Syntech;
using namespace vex;

/**
 * The starting off point of the program.
 * 
 * @author Bailey Moir
 */

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
    
  /*
  * Pick up purple
  * Pick up oranges
  * Put purple on top
  * Dump orange ones, then go to opposite and do the same thing.
  */ 
  startIntake(720);
  moveTime(1500, 720);
  stopIntake();
  //Collected first purple cube,
  move(-(60.69 - distanceToFront));
  turn(-90);
  moveTimeDistance(60.69 - distanceToFront, 720);
  intake(500, 720);
  move(-cubeWidth);
  moveSideWays(-31.845);
  moveTimeDistance(cubeWidth, 720);
  intake(500, 720);
  move(-cubeWidth);
  moveSideWays(-31.845);
  moveTimeDistance(cubeWidth, 720);
  intakeUntil(720, []() { return Devices::distanceSensor.isObjectDetected(); });
  // Collected all orange cubes.
  moveTime(100, 720);
  move(-(121.38 - distanceToFront));
  turn(45);
  move(-64.37);
  intake(1500, 720);
  // Purple cube deposited.
  move(64.37);
  turn(45);
  move(262.76);
  turn(90);
  startIntake(-720);
  move(-80.69);
  stopIntake();
  // Orange cubes deposited.
  turn(90);
  startIntake(720);
  moveTimeDistance(161.725 - cubeWidth, 720);
  stopIntake();
  // Next purple cube collected.
  move(-60.69);
  turn(90);
  moveTimeDistance(60.69 - distanceToFront, 720);
  intake(500, 720);
  move(-cubeWidth);
  moveSideWays(31.845);
  moveTimeDistance(cubeWidth, 720);
  intake(500, 720);
  move(-cubeWidth);
  moveSideWays(31.845);
  moveTimeDistance(cubeWidth, 720);
  intakeUntil(720, []() { return Devices::distanceSensor.isObjectDetected(); });
  // Collected all green cubes.
  moveTime(100, 720);
  move(-(121.38 - distanceToFront));
  turn(-45);
  move(-64.37);
  intake(1500, 720);
  // Last purple cube deposited.
  move(64.37);
  turn(-45);
  move(262.76);
  turn(-90);
  startIntake(-720);
  moveTime(5000, -720);
  stopIntake();
  //Everything deposited.

}

/**
 * The code that loops for user control.
 */
void control() {
  Devices::leftBMotor.setVelocity(720 * Devices::_controller.Axis3.value(), velocityUnits::dps);
  Devices::leftFMotor.setVelocity(720 * Devices::_controller.Axis3.value(), velocityUnits::dps);
  Devices::rightBMotor.setVelocity(720 * Devices::_controller.Axis2.value(), velocityUnits::dps);
  Devices::rightFMotor.setVelocity(720 * Devices::_controller.Axis2.value(), velocityUnits::dps);
}  

/**
 * The origin of the main thread.
 */
int main() {
  vexcodeInit();

  Devices::comp.autonomous(auton);
  Devices::comp.drivercontrol(control);
}
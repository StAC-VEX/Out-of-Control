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
  //waitUntil(!Devices::sensor.isCalibrating());
  move(tileSize - depth / 2 - cubeWidth, 3);
  turn(-90, 3);
  moveTimeDistance(tileSize - depth / 2, 720);
  claw(2000, -720);
  moveTime(100, 360);
  turn(-90, 3);
  claw(2000, 720);
  move(-cubeWidth, 3);
  turn(-90, 3);
  move(10, 3);
  turn(180, 3);
  moveTimeDistance(depth + 10, 360);
  /*claw(2000, -720);
  // Picked up left most orange cube.
  moveTimeDistance(cubeWidth * 1.5, 360);
  move(-(-depth / 2 + tileSize + width / 2 + 2), 1); // 2 is just an arbitrary margin to make sure that the robot doesn't undershoot and hit the middle wall.
  turn(90, 1);
  moveTimeDistance(tileSize * 3.5, 2);
  claw(1000, -720);  
  // Dropped off first orange.
  moveTimeDistance(cubeWidth * 1.5, 360);
  move(-(-depth / 2 + tileSize / 2 + cubeWidth / 2), 1);
  moveTimeDistance(-depth / 2 + tileSize + width / 2 + 2, 360);
  claw(2000, 720);
  // Picked up right green cube.
  moveTimeDistance(cubeWidth * 1.5, 360);
  move(-(-depth / 2 + tileSize + width / 2 + 2), 1); // 2 is just an arbitrary margin to make sure that the robot doesn't undershoot and hit the middle wall.
  turn(-90, 1);
  moveTimeDistance(tileSize * 3.5, 2);
  claw(1000, -720);  
  // Dropped off first green cube.
  moveTimeDistance(cubeWidth * 1.5, 360);
  move(-(tileSize - depth / 2), 1);
  turn(90, 1);
  moveTimeDistance(-depth / 2 + tileSize + width / 2 + 2, 360);
  claw(2000, 720);
  // Picked up middle orange cubemoveTimeDistance(cubeWidth * 1.5, 360);
  move(-(-depth / 2 + tileSize + width / 2 + 2), 1); // 2 is just an arbitrary margin to make sure that the robot doesn't undershoot and hit the middle wall.
  turn(90, 1);
  moveTimeDistance(tileSize * 2, 2);
  turn(-90, 1);
  move(width / 2 + 2 + width / 2, 1);
  turn(90, 1);
  move(tileSize, 1);
  claw(1000, -360);*/
}

/**
 * The code that loops for user control.
 */
void control() {
  while (true) {
    Devices::_controller.ButtonA.pressed(auton);
    Devices::armMotor.spin(fwd, 360 * ((int) Devices::_controller.ButtonL2.pressing() - (int)Devices::_controller.ButtonL1.pressing()), dps);
    Devices::clawMotor.spin(fwd, 360 * ((int) Devices::_controller.ButtonR2.pressing() - (int)Devices::_controller.ButtonR1.pressing()), dps);

    Devices::leftBMotor.spin(fwd, 360 * Devices::_controller.Axis3.value(), dps);
    Devices::leftFMotor.spin(fwd, 360 * Devices::_controller.Axis3.value(), dps);
    Devices::rightBMotor.spin(fwd, 360 * Devices::_controller.Axis2.value(), dps);
    Devices::rightFMotor.spin(fwd, 360 * Devices::_controller.Axis2.value(), dps);
    if (360 * ((int) Devices::_controller.ButtonL2.pressing() - (int)Devices::_controller.ButtonL1.pressing()) == 0) Devices::armMotor.stop(hold);
    if (360 * ((int) Devices::_controller.ButtonR2.pressing() - (int)Devices::_controller.ButtonR1.pressing()) == 0) Devices::clawMotor.stop(hold);
  }
}  

/**
 * The origin of the main thread.
 */
int main() {
  vexcodeInit();

  Devices::comp.autonomous(auton);
  Devices::comp.drivercontrol(control);
}
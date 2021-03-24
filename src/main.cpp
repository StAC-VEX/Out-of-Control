#include "vex.h"
using namespace vex;

//Temporary ports, until actual robot is started.
controller _controller = controller();
brain _brain = brain();
competition comp = competition();
inertial sensor = inertial(PORT1);
motor leftMotor = motor(PORT1);
motor rightMotor = motor(PORT1);

void vexcodeInit() {
  sensor.calibrate();  
}

class Auton { 
public:
  void turn(int degrees) {

  }
  void move(int distance) {

  }
  void move(int time) {

  }
  void intake(motor* motors, int time) {

  }
};

void auton() {
  waitUntil(!sensor.isCalibrating());
}

void control() {
  leftMotor.setVelocity(720 * _controller.Axis3.value(), velocityUnits::dps);
  rightMotor.setVelocity(720 * _controller.Axis2.value(), velocityUnits::dps);
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  comp.autonomous(auton);
  comp.drivercontrol(control);
}

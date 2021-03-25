/**
 * The starting off point of the program.
 * 
 * @author Bailey Moir
 */

#include "vex.h"
#include <cstdlib>
using namespace vex;

//Temporary ports, until actual robot is started.
controller _controller = controller();
brain _brain = brain();
competition comp = competition();
inertial sensor = inertial(PORT1);
motor leftMotor = motor(PORT1);
motor rightMotor = motor(PORT1);
motor intakeMotor = motor(PORT1);

void vexcodeInit() {
  sensor.calibrate();  
}

/**
 * The class that contains all of the autonomous functions.
 */
class Auton { 
public:
  /**
   * Turns the robot a specified amount.
   * 
   * @param degrees The amount of degress the robot will turn.
   */
  void turn(int degrees) {
    sensor.rotation();
    P(2, 60, 1, degrees, []() { return sensor.rotation(); }, [](int speed) {
      leftMotor.spin(directionType::fwd, speed, velocityUnits::dps);
      rightMotor.spin(directionType::rev, speed, velocityUnits::dps);
    });
  }

  /**
   * Moves the robot for a specificed distance.
   * 
   * @param move How far you want the robot to move and what direction (positive is forward, negative is backwards).
   */
  void move(int distance) {
    //5 = wheelRadius
    leftMotor.resetRotation();
    P(5, 60, 1, distance, []() { return ((3.14159 * 5) / 360 * leftMotor.rotation(rotationUnits::deg)); }, [](int speed) { 
      leftMotor.spin(directionType::fwd, speed, velocityUnits::dps);
      rightMotor.spin(directionType::fwd, speed, velocityUnits::dps);
    });
  }

  /**
   * Moves the robot for a specified amount of time at a specified speed.
   * 
   * @param time The miliseconds (amount of time) that you want the robot to move forward.  
   * @param _dps The amount of degrees per second you want the robot to move (positive is forward, negative is backwards).
   */
  void move(int time, int _dps) {
    leftMotor.spin(fwd, _dps, dps);
    rightMotor.spin(fwd, _dps, dps);
    wait(time, msec);
    leftMotor.stop(coast);    
    rightMotor.stop(coast);
  }

  /**
   * Intakes the specified motors for a specified amount of time at a specified speed.
   *
   * @param time The miliseconds (amount of time) to spin the motors for.
   * @param _dps The degrees per second to spin the motors at.
   * @param motors The list of motors to spin.
   */
  void intake(int time, int _dps) {
    motor motors[] = {intakeMotor};

    for (motor _motor : motors) {
      _motor.spin(fwd, _dps, dps);      
    }

    wait(time, msec);
    
    for (motor _motor : motors) {
      _motor.stop(coast);
    }
  }
private:

  void P(int min, int max, float margin, int desired, double(*independent)(), void(*loop)(int error)) {
    leftMotor.resetRotation();
    rightMotor.resetRotation();

    double error = desired - independent();
    double previousError = 0;
    const double maxAcceleration = 0.03;
    while (!(independent() < desired + margin && independent() > desired - margin)) {
      // Gets the previous error
      error = desired - independent();
      double speed = error;

      if (fabs(error - previousError) > maxAcceleration) {
        //If accelerating
        if (speed - previousError > 0) speed = (previousError - maxAcceleration);
        else speed = previousError + maxAcceleration;
      }

      // Caps the error.
      if (speed > max) speed = max;
      if (speed < -max) speed = -max;
      if (speed < min && error > 0) speed = min;
      if (speed > -min && speed < 0) speed = -min;

      loop(speed);

      wait(20, msec);
      // How far the motor still needs to go.
      previousError = desired - error;
    }
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

#include "auton.h"

using namespace Syntech;

void Syntech::turn(const int degrees, const float efficiency) {
	/*Devices::sensor.resetRotation();
	P(2.0, 1, 60, 0.5, degrees, []() { 
		return Devices::sensor.rotation(); 
	}, [](int speed, float efficiency) {
		Devices::leftBMotor.spin(directionType::fwd, speed * efficiency, velocityUnits::dps);
		Devices::leftFMotor.spin(directionType::fwd, speed * efficiency, velocityUnits::dps);
		Devices::rightBMotor.spin(directionType::rev, speed * efficiency, velocityUnits::dps);
		Devices::rightFMotor.spin(directionType::rev, speed * efficiency, velocityUnits::dps);
	});*/
  Devices::leftBMotor.resetRotation();
	P(efficiency, 90, 360, 0.5, degrees, []() { 
		return (3.14159 * wheelDiameter * (Devices::leftBMotor.rotation(rotationUnits::deg) / 360)) / (3.14159 * turnDiameter) * 360;
	}, [](double speed) {
    Devices::_brain.Screen.newLine();
    Devices::_brain.Screen.print(speed);
		Devices::leftBMotor.spin(directionType::fwd, speed, velocityUnits::dps);
		Devices::leftFMotor.spin(directionType::fwd, speed, velocityUnits::dps);
		Devices::rightBMotor.spin(directionType::rev, speed, velocityUnits::dps);
		Devices::rightFMotor.spin(directionType::rev, speed, velocityUnits::dps);
	}, []{
		Devices::leftBMotor.stop(coast);
		Devices::leftFMotor.stop(coast);
		Devices::rightBMotor.stop(coast);
		Devices::rightFMotor.stop(coast);
  });
}

void Syntech::move(float distance, float efficiency) {
	Devices::leftBMotor.resetRotation();
	P(efficiency * 10, 10, 720, 0.5, distance, []() { 
		// C		= πd
		// Length	= πd * degrees / 360
		return 3.14159 * wheelDiameter * (Devices::leftBMotor.rotation(rotationUnits::deg) / 360);
	}, [](double speed) {
		Devices::leftBMotor.spin(directionType::fwd, speed, velocityUnits::dps);
		Devices::leftFMotor.spin(directionType::fwd, speed, velocityUnits::dps);
		Devices::rightBMotor.spin(directionType::fwd, speed, velocityUnits::dps);
		Devices::rightFMotor.spin(directionType::fwd, speed, velocityUnits::dps);
	}, []{
		Devices::leftBMotor.stop(coast);
		Devices::leftFMotor.stop(coast);
		Devices::rightBMotor.stop(coast);
		Devices::rightFMotor.stop(coast);
  });
}

void Syntech::moveTime(int time, int _dps) {
	Devices::leftBMotor.spin(fwd, _dps, dps);
	Devices::leftFMotor.spin(fwd, _dps, dps);
	Devices::rightFMotor.spin(fwd, _dps, dps);
	Devices::rightBMotor.spin(fwd, _dps, dps);

	wait(time, msec);
	
	Devices::leftBMotor.stop(coast);    
	Devices::leftFMotor.stop(coast);    
	Devices::rightBMotor.stop(coast);
	Devices::rightFMotor.stop(coast);
}

void Syntech::moveTimeDistance(float roughDistance, int _dps) {
	Devices::leftBMotor.spin(fwd, _dps, dps);
	Devices::leftFMotor.spin(fwd, _dps, dps);
	Devices::rightBMotor.spin(fwd, _dps, dps);
	Devices::rightFMotor.spin(fwd, _dps, dps);

	// distance		= πd * degrees / 360
	// degrees		= (360 * distance) / πd 
	// degrees/_dps	= s
	// s			= (360 * distance) / πd * _dps
	wait((360 * roughDistance) / (3.14159 * wheelDiameter * _dps) + 0.3, sec);

	Devices::leftBMotor.stop(coast);    
	Devices::leftFMotor.stop(coast);    
	Devices::rightBMotor.stop(coast);
	Devices::rightFMotor.stop(coast);

}

void claw(int _dps) {
	Devices::clawMotor.spin(fwd, _dps, dps); 
}

void stopClaw() {
	Devices::clawMotor.stop(coast);
}

void Syntech::claw(int time, int _dps) {
	Devices::clawMotor.spin(fwd, _dps, dps); 

	wait(time, msec);

	Devices::clawMotor.stop(coast);
}

void arm(int _dps) {
	Devices::armMotor.spin(fwd, _dps, dps); 
}

void stopArm() {
	Devices::armMotor.stop(coast);
}

void Syntech::arm(int time, int _dps) {
	arm(_dps);

	wait(time, msec);

  stopArm();
}

void Syntech::P(const float efficiency, const int min, const int max, const float margin, const float desired, double(*independent)(), void(*loop)(double error), void(*stop)()) {
	while (!(desired - independent() < margin / 2 && desired - independent() > -margin / 2)) {
    // Gets the previous error
    double error = (desired - independent()) * efficiency;

    // Caps the error.
    if (error > max) error = max;
    if (error < -max) error = -max;
    if (error < min && error > 0) error = min;
    if (error > -min && error < 0) error = -min;

    loop(error);

    wait(20, msec);
	}
  stop();  
}
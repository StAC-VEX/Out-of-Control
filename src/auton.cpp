#include "auton.h"

using namespace Syntech;

motor intakeMotors[] = {Devices::leftIntakeMotor, Devices::rightIntakeMotor};

void Syntech::turn(int degrees) {
	Devices::sensor.rotation();
	P(2, 60, 1, degrees, []() { 
		return Devices::sensor.rotation(); 
	}, [](int speed) {
		Devices::leftBMotor.spin(directionType::fwd, speed, velocityUnits::dps);
		Devices::leftFMotor.spin(directionType::fwd, speed, velocityUnits::dps);
		Devices::rightBMotor.spin(directionType::rev, speed, velocityUnits::dps);
		Devices::rightFMotor.spin(directionType::rev, speed, velocityUnits::dps);
	});
}

void Syntech::move(float distance) {
	Devices::leftBMotor.resetRotation();
	P(5, 60, 1, distance, []() { 
		// C		= πd
		// Length	= πd * degrees / 360
		return 3.14159 * wheelDiameter * (Devices::leftBMotor.rotation(rotationUnits::deg) / 360);
	}, [](int speed) { 
		Devices::leftBMotor.spin(directionType::fwd, speed, velocityUnits::dps);
		Devices::leftFMotor.spin(directionType::fwd, speed, velocityUnits::dps);
		Devices::rightBMotor.spin(directionType::fwd, speed, velocityUnits::dps);
		Devices::rightFMotor.spin(directionType::fwd, speed, velocityUnits::dps);
	});
}

void Syntech::moveSideWays(float distance) {
	// A lot of this function is subject to change.
	Devices::leftBMotor.resetRotation();
	P(5, 60, 1, distance, []() { 
		// C		= πd
		// Length	= πd * degrees / 360
		return 3.14159 * wheelDiameter * (Devices::leftBMotor.rotation(rotationUnits::deg) / 360);
	}, [](int speed) { 
		Devices::leftBMotor.spin(directionType::fwd, speed, velocityUnits::dps);
		Devices::leftFMotor.spin(directionType::rev, speed, velocityUnits::dps);
		Devices::rightBMotor.spin(directionType::fwd, speed, velocityUnits::dps);
		Devices::rightFMotor.spin(directionType::rev, speed, velocityUnits::dps);
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

void Syntech::intake(int time, int _dps) {
	for (motor _motor : intakeMotors) {
		_motor.spin(fwd, _dps, dps);      
	}

	wait(time, msec);

	for (motor _motor : intakeMotors) {
		_motor.stop(coast);
	}
}

void Syntech::intakeUntil(int _dps, bool(*check)()) {
	for (motor _motor : intakeMotors) {
		_motor.spin(fwd, _dps, dps);      
	}

	waitUntil(check());

	for (motor _motor : intakeMotors) {
		_motor.stop(coast);
	}
}

void Syntech::startIntake(int _dps) {
	for (motor _motor : intakeMotors) {
		_motor.spin(fwd, _dps, dps);      
	}
}

void Syntech::stopIntake() {
	for (motor _motor : intakeMotors) {
		_motor.stop(coast);
	}
}

void Syntech::P(int min, int max, float margin, float desired, double(*independent)(), void(*loop)(int error)) {
	double error = desired - independent();
	double previousError = 0;
	const double maxAcceleration = 0.03;
	const float kP = 1;
	while (!(independent() < desired + margin && independent() > desired - margin)) {
		// Gets the previous error
		error = desired - independent();
		double speed = error * kP;

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
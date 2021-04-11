#include "devices.h"

namespace Syntech {
  controller Devices::_controller = controller();
  brain Devices::_brain = brain();
  competition Devices::comp = competition();
  inertial Devices::sensor = inertial(PORT1);
  motor Devices::leftBMotor = motor(PORT1);
  motor Devices::leftFMotor = motor(PORT1);
  motor Devices::rightBMotor = motor(PORT1);
  motor Devices::rightFMotor = motor(PORT1);
  motor Devices::leftIntakeMotor = motor(PORT1);
  motor Devices::rightIntakeMotor = motor(PORT1);
};
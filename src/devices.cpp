#include "devices.h"

namespace Syntech {
  controller Devices::_controller = controller();
  brain Devices::_brain = brain();
  competition Devices::comp = competition();
  inertial Devices::sensor = inertial(PORT1);
  motor Devices::leftMotor = motor(PORT1);
  motor Devices::rightMotor = motor(PORT1);
  motor Devices::leftIntakeMotor = motor(PORT1);
  motor Devices::rightIntakeMotor = motor(PORT1);
};
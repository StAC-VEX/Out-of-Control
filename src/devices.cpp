#include "devices.h"

namespace Syntech {
  controller Devices::_controller = controller();
  brain Devices::_brain = brain();
  competition Devices::comp = competition();
  inertial Devices::sensor = inertial(PORT20);
  motor Devices::leftBMotor = motor(PORT9);
  motor Devices::leftFMotor = motor(PORT8);
  motor Devices::rightBMotor = motor(PORT1, true);
  motor Devices::rightFMotor = motor(PORT7, true);
  motor Devices::clawMotor = motor(PORT10, false);
  motor Devices::armMotor = motor(PORT3, true);
};
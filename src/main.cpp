#include "vex.h"
using namespace vex;

controller _controller = controller();
brain _brain = brain();
competition comp = competition();

void vexcodeInit() {
  
}

void auton() {

}

void control() {

}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  comp.autonomous(auton);
  comp.drivercontrol(control);
}

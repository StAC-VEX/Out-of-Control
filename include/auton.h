#pragma once
#include "devices.h"

namespace Syntech {
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
    static void turn(int degrees); 

    /**
    * Moves the robot for a specificed distance.
    * 
    * @param move How far you want the robot to move and what direction (positive is forward, negative is backwards).
    */
    static void move(int distance); 

    /**
    * Moves the robot for a specified amount of time at a specified speed.
    * 
    * @param time The miliseconds (amount of time) that you want the robot to move forward.  
    * @param _dps The amount of degrees per second you want the robot to move (positive is forward, negative is backwards).
    */
    static void move(int time, int _dps); 

    /**
    * Intakes the specified motors for a specified amount of time at a specified speed.
    *
    * @param time The miliseconds (amount of time) to spin the motors for.
    * @param _dps The degrees per second to spin the motors at.
    * @param motors The list of motors to spin.
    */
    static void intake(int time, int _dps); 
  private:
    /**
    * The proportional function. Everything is in the same unit.
    * 
    * @param min The minimum speed that the loop can send.
    * @param max The maximum speed that the loop can send.
    * @param margin The margin of error.
    * @param desired Where the independent variable should be when the proportional ends.
    * @param independent The variable that is changing over time.
    * @param loop What is looped every time that affects 'indepedent'
    */
    static void P(int min, int max, float margin, int desired, double(*independent)(), void(*loop)(int error)); 
  };
};
#pragma once
#include "devices.h"

/**
 * The class that contains all of the autonomous functions.
 * 
 * @author Bailey Moir
 */

namespace Syntech {
class Auton { 
public:
  /**
   * @brief  Turns the robot a specified amount.
   * @param  degrees: The amount of degress the robot will turn.
   * @retval None
   */
  static void turn(int degrees); 

  /**
   * @brief  Moves the robot for a specificed distance.
   * @param  distance: How far you want the robot to move and what direction (positive is forward, negative is backwards).
   * @retval None
   */
  static void move(int distance); 

  /**
   * @brief  Moves the robot for a specified amount of time at a specified speed.
   * @param  time: The miliseconds (amount of time) that you want the robot to move forward.  
   * @param  _dps: The amount of degrees per second you want the robot to move (positive is forward, negative is backwards).
   * @retval None
   */
  static void move(int time, int _dps); 

  /**
   * @brief  Intakes the specified motors for a specified amount of time at a specified speed.
   * @param  time: The miliseconds (amount of time) to spin the motors for.
   * @param  _dps: The degrees per second to spin the motors at.
   * @retval None
   */
  static void intake(int time, int _dps); 
private:
  /**
   * @brief  The proportional function. Everything is in the same unit.
   * @param  min: The minimum speed that the loop can send.
   * @param  max: The maximum speed that the loop can send.
   * @param  margin: The margin of error.
   * @param  desired: Where the independent variable should be when the proportional ends.
   * @param  independent: The variable that is changing over time.
   * @param  loop: What is looped every time that affects 'indepedent'
   * @retval None
   */
  static void P(int min, int max, float margin, int desired, double(*independent)(), void(*loop)(int error)); 
};};
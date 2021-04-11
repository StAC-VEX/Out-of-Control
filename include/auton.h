#pragma once
#include "devices.h"

/**
 * Contains all of the autonomous functions.
 * 
 * @author Bailey Moir
 */

namespace Syntech {
  /**
   * @brief  Turns the robot a specified amount.
   * @param  degrees: The amount of degress the robot will turn.
   * @retval None
   */
  void turn(int degrees); 

  /**
   * @brief  Moves the robot for a specificed distance.
   * @param  distance: How far you want the robot to move and what direction (positive is forward, negative is backwards).
   * @retval None
   */
  void move(int distance); 

  /**
   * @brief  Moves the robot for a specified amount of time at a specified speed.
   * @param  time: The miliseconds (amount of time) that you want the robot to move forward.  
   * @param  _dps: The amount of degrees per second you want the robot to move (positive is forward, negative is backwards).
   * @retval None
   */
  void move(int time, int _dps); 

  /**
   * @brief  Intakes for a specified amount of time at a specified speed.
   * @param  time: The miliseconds (amount of time) to spin the intakes for.
   * @param  _dps: The degrees per second to spin the intakes at.
   * @retval None
   */
  void intake(int time, int _dps); 

  /**
   * @brief  Starts to intake forever, until the motors are told to do otherwise.
   * @param  _dps: The degrees per second to spin the intakes at.
   * @retval None
   */
  void startIntake(int _dps);

  /**
   * @brief  Stops intaking. Not nescessary for the 'intake(int time, int _dps)' function.
   * @retval None
   */
  void stopIntake();

  /**
   * @brief  The proportional and intergral function. Everything is in the same unit.
   * @param  min: The minimum speed that the loop can send.
   * @param  max: The maximum speed that the loop can send.
   * @param  margin: The margin of error.
   * @param  desired: Where the independent variable should be when the proportional ends.
   * @param  independent: The variable that is changing over time.
   * @param  loop: What is looped every time that affects 'indepedent'
   * @retval None
   */
  void PI(int min, int max, float margin, int desired, double(*independent)(), void(*loop)(int error)); 
};
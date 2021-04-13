#pragma once
#include "devices.h"

/**
 * Contains all of the autonomous functions.
 * 
 * @author Bailey Moir
 */

namespace Syntech {
  const float distanceToFront = 0;
  const float wheelDiameter = 0;
  const float cubeWidth = 13.97;

  /**
   * @brief  Turns the robot a specified amount.
   * @param  degrees: The amount of degress the robot will turn.
   * @retval None
   */
  void turn(int degrees); 

  /**
   * @brief  Moves the robot for a specificed distance.
   * @param  distance: Centimeters. How far you want the robot to move and what direction (positive is forward, negative is backwards).
   * @retval None
   */
  void move(float distance); 

  /**
   * @brief  Moves the robot sideways for a specificed distance.
   * @param  distance: Centimeters. How far you want the robot to move and what direction (positive is right, negative is left).
   * @retval None
   */
  void moveSideWays(float distance);

  /**
   * @brief  Moves the robot based an amount of time, no P, I, or D, based on an estimated distance.
   * @param  roughDistance: Centimeters. The estimated distance the robot should travel. 
   * @param  _dps: The amount of degrees per second you want the robot to move. MUST BE POSITIVE.
   * @retval None
   */
  void moveTimeDistance(float roughDistance, int _dps); 

  /**
   * @brief  Moves the robot for a specified amount of time at a specified speed.
   * @param  time: The miliseconds (amount of time) that you want the robot to move forward.  
   * @param  _dps: The amount of degrees per second you want the robot to move (positive is forward, negative is backwards).
   * @retval None
   */
  void moveTime(int time, int _dps); 

  /**
   * @brief  Intakes for a specified amount of time at a specified speed.
   * @param  time: The miliseconds (amount of time) to spin the intakes for.
   * @param  _dps: The degrees per second to spin the intakes at.
   * @retval None
   */
  void intake(int time, int _dps);

  /**
   * @brief  Intakes at a specified speed until the boolean function specified returns true.
   * @param  _dps: The degrees per second to spin the intakes at.
   * @param  check: The function that returns the boolean value of whether to stop intaking or not.
   * @retval None
   */
  void intakeUntil(int _dps, bool(*check)());

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
  void P(int min, int max, float margin, float desired, double(*independent)(), void(*loop)(int error)); 
};
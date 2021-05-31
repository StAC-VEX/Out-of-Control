#pragma once
#include "vex.h"

namespace Syntech { class Time {
public:
	static double deltaTime;
	static long last_time;

	static vex::timer m_timer;

	/**
	 * Initiates the timer.
	 */
	static void init();

	/**
	 * Gets the system current time in milliseconds.
	 * @retval The system current time in milliseconds.
	 */
	static long getTime();

	/**
	 * Updates the delta time variable. To be run every frame.
	 */
	static void update();
};}
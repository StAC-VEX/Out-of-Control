#include "_time.h"
#include "vex.h"

namespace Syntech {
		void Time::init() {
			timer = vex::timer();
		}

		long Time::getTime() {
			return timer.system();
		}

		void Time::update() {
			long timeSec = getTime() * 1000;
			long time = getTime();
			deltaTime = ((time - last_time) / (float) 1000000);

			last_time = getTime();
		}
}
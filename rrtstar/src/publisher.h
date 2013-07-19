
#ifndef _PUBLISHER_H
#define _PUBLISHER_H

#include <bot_core/bot_core.h>
#include <lcm/lcm.h>
#include <lcmtypes/lcmtypes.h>

#include "region.h"

using namespace std;

template<class Planner, class System>
	class Publisher {
		lcm_t *lcm;

	public:
		Publisher();
		~Publisher();
		
		int publishTree (Planner& planner, System& system);
		int publishTraj (Planner& planner, System& system);
		int publishEnvironment (Region& regionOperating, Region& regionGoal, list<Region*>& obstacles);
	};

#endif

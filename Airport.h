#ifndef AIRPORT_H
#define AIRPORT_H

#include <mutex>
#include <random>
#include <condition_variable>
#include "Runways.h"

class Airport {
public:
	Airport();
	void reserveRunway(Runways::RunwayNumber runway);
	void releaseRunway(Runways::RunwayNumber runway);

private:
	static const int MAX_RIDE_TIME = 100; // Maximum time the airplane will on the runway
	static const int MAX_WAIT_TIME = 100; // Maximum time between landings/takeoffs

    mutex runwaysMutex;
    mutex mtx_sec;
    condition_variable section[Runways::NUM_RUNWAYS];
	bool sect[Runways::NUM_RUNWAYS];
};

#endif
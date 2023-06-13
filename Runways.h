#ifndef RUNWAYS_H
#define RUNWAYS_H

#include <iostream>
#include <string>
#include <mutex>
#include <vector>

using namespace std;

class Runways {
public:
	static const int NUM_RUNWAYS = 6;     // Number of runways
	static const int NUM_AIRPLANES = 20;   // Number of airplanes
	enum RunwayNumber {RUNWAY_1, RUNWAY_2, RUNWAY_3, RUNWAY_4, RUNWAY_5, RUNWAY_6};
};

#endif
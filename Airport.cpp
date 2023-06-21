#include <iostream>
#include <thread>
#include <condition_variable>
#include "Airport.h"
#include "ncurses.h"

using namespace std;

Airport::Airport() {
    for(int i = 0; i < Runways::NUM_RUNWAYS; i++)
    {
        sect[i]=false;
    }
}

void Airport::reserveRunway(Runways::RunwayNumber runway)
{
    unique_lock<mutex> ulk(mtx_sec);
    while(sect[runway + 1]) section[runway].wait(ulk);
    sect[runway] = true;

    // obtain a seed from the system clock:
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);

    // Ride for a random number of milliseconds
    uniform_int_distribution<int> rideTimeDistribution(1, MAX_RIDE_TIME);
    int rideTime = rideTimeDistribution(generator);
    this_thread::sleep_for(chrono::milliseconds(rideTime));
}

void Airport::releaseRunway(Runways::RunwayNumber runway){
    unique_lock<mutex> ulk(mtx_sec);
    section[runway].notify_one();
    sect[runway] = false;

    // obtain a seed from the system clock:
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);

    // Wait for a random number of milliseconds before requesting the next landing
    uniform_int_distribution<int> waitTimeDistribution(1, MAX_WAIT_TIME);
    int waitTime = waitTimeDistribution(generator);
    this_thread::sleep_for(chrono::milliseconds(waitTime));
}

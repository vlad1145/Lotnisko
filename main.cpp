#include <iostream>
#include <vector>
#include <thread>
#include "Airport.h"
#include "Airplane.h"
#include "Runways.h"
#include "ncurses.h"

using namespace std;

void init() {
    initscr();
    curs_set(0);
    refresh();
    start_color();
    init_pair(0, COLOR_RED, COLOR_BLACK);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_BLACK);
}

void start(Airplane* airplanes) {
    airplanes->land_takeoff();
}

int main() {
    init();
    Airport airport;
    vector<thread> airplane_threads; // Airplane wątki

    // Tworzymy i urachamiamy wątki
    for (int i = 0; i < Runways::NUM_AIRPLANES; i++) {
        auto *airplanes = new Airplane(i, &airport);
        airplane_threads.emplace_back([airplanes](){start(airplanes);});
    }

    for (auto &threads : airplane_threads) {
        if (threads.joinable())
            threads.join();
    }

    endwin();
    return 0;
}
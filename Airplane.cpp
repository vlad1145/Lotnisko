#include <thread>
#include <random>
#include <chrono>
#include <algorithm>
#include "ncurses.h"
#include "Airplane.h"
using namespace std;

string planeStatus[Runways::NUM_AIRPLANES] = {};
mutex draw;
mutex draw2;
mutex draw3;

void Airplane::draw_rectangle(int y1, int x1, int y2, int x2) {
    mvhline(y1, x1, 0, x2 - x1);
    mvhline(y2, x1, 0, x2 - x1);
    mvvline(y1, x1, 0, y2 - y1);
    mvvline(y1, x2, 0, y2 - y1);
    mvaddch(y1, x1, ACS_ULCORNER);
    mvaddch(y2, x1, ACS_LLCORNER);
    mvaddch(y1, x2, ACS_URCORNER);
    mvaddch(y2, x2, ACS_LRCORNER);
}

 void Airplane::Display() {
    draw.lock();
    erase();
    getmaxyx(stdscr, terminal_y, terminal_x);
    refresh();
    //draw static
    mvprintw(0, terminal_x-70, "Airport-Threads");
    mvprintw(terminal_y-1, 0, "Vladyslav Pikul 256624");
    for (int i=0; i < Runways::NUM_AIRPLANES; i++) {
        draw_rectangle(2+k, terminal_y+10, 5+k,terminal_x-10);
        k += 4;
        if(k>20) {k=0;}
    }

    for (int i=0; i < Runways::NUM_AIRPLANES; i++) {
        mvprintw(i + 3, 0, "Airplane %d ", i + 1);
        mvprintw(i + 3, 13, planeStatus[i].c_str());
    }

  switch (runwayToUse) {
        case 0:
            current_y = 3;
            break;
        case 1:
            current_y = 7;
            break;
        case 2:
            current_y = 11;
            break;
        case 3:
            current_y = 15;
            break;
        case 4:
            current_y = 20;
            break;
        case 5:
            current_y = 23;
            break;
    }

    if (drawStatus == 0){
        mvprintw(current_y, current_x, "----T");
    }

    if (drawStatus == 1){
        mvprintw(current_y, current_x, "L----");
    }

    refresh();
    draw.unlock();
}

void Airplane::land_takeoff() {
	random_device rd;
	default_random_engine generator(rd());
	uniform_int_distribution<int> runwayNumber(Runways::RUNWAY_1, Runways::RUNWAY_6);
    planeStatus[airplaneNum] = "AIR";
   for(int i=0; i < Runways::NUM_AIRPLANES;i++) {
        if (i % 2 == 0)
        {
            landed.push_back(i);
            planeStatus[i] = "LANDED";
        }
    }

	while (true) {
    Display();
        airplaneNum = rand() % (Runways::NUM_AIRPLANES );
        if (count(landed.begin(), landed.end(), airplaneNum)) {
            draw2.lock();
            drawStatus = 0;
           runwayToUse = Runways::RunwayNumber(runwayNumber(generator));


           current_x = 0;
           while(current_x < terminal_x -20) {
               current_x += 10;
                Display();
               this_thread::sleep_for(chrono::milliseconds(50));
               if (current_x < terminal_x - 150) {
                   current_x = 45;
               }
               if (current_x > terminal_x -10) {
                   current_x = 45;
               }
           }

            Display();

            airport->reserveRunway(runwayToUse);
            airport->releaseRunway(runwayToUse);
            landed.erase(remove(landed.begin(), landed.end(), airplaneNum), landed.end());
            planeStatus[airplaneNum] = "TAKE OFF";
            draw2.unlock();
        }
        else {
            draw3.lock();
            drawStatus = 1;
            runwayToUse = Runways::RunwayNumber(runwayNumber(generator));
            while(current_x < terminal_x -20) {
                current_x += 10;
                Display();
                this_thread::sleep_for(chrono::milliseconds(50));
                if (current_x < terminal_x - 150) {
                    current_x = 45;
                }

                if (current_x > terminal_x -10) {
                    current_x = 45;
                }
            }
            airport->reserveRunway(runwayToUse);
            airport->releaseRunway(runwayToUse);
            landed.push_back(airplaneNum);
            planeStatus[airplaneNum] = "LANDING";
            draw3.unlock();
        }
		this_thread::sleep_for(chrono::milliseconds(1000));
	}
}

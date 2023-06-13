#ifndef AIRPLANE_H
#define AIRPLANE_H

#include "Airport.h"
#include "Runways.h"

class Airplane {
public:
	int airplaneNum;
	Airport* airport;
    static void draw_rectangle(int y1, int x1, int y2, int x2);
	Airplane(int side_num, Airport* ap) {
		airplaneNum = side_num;
		airport = ap;
	};
    int drawStatus;
    [[noreturn]] void land_takeoff();
    void Display();

private:
	int k = 0, terminal_x = 0, terminal_y=0;
    int current_y = 200, current_x;
    vector<int> landed;
    Runways::RunwayNumber runwayToUse; // Random runway
};
#endif
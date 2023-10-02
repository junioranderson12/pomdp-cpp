#include "grid-world-agent.hpp"

#include <cstdlib>
#include <ctime>
#include <algorithm>

#include "grid-world-simulator.hpp"
#include "grid-world-state.hpp"

#define MAX_X 3
#define MAX_Y 2
//#define RAND_MAX 32767
GridWorldAgent::GridWorldAgent(int x, int y) : x(x), y(y)
{
}

GridWorldAgent::~GridWorldAgent()
{
}

void GridWorldAgent::actionModel(int actionID){

    // Available actions: 0(up), 1(down), 2(left), 3(right)
    if ((float)std::rand() /(float)RAND_MAX > 0.8){
        actionID = std::rand()%4;
    }
    int x_prev = x;
    int y_prev = y;
    switch (actionID) {
    case 0:
        y = std::min(y + 1, MAX_Y);
        break;
    case 1:
        y = std::max(y - 1, 0);
        break;
    case 2:
        x = std::max(x - 1, 0);
        break;
    case 3:
        x = std::min(x + 1, MAX_X);
        break;
    }
    if ((x == 1) && (y == 1)){
        x = x_prev;
        y = y_prev;
    }
}

int GridWorldAgent::get_x() const{
    return x;
}

int GridWorldAgent::get_y() const{
    return y;
}

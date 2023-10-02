
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <memory>

#include "grid-world-agent.hpp"
#include "grid-world-observation.hpp"
#include "grid-world-state.hpp"
#include "grid-world-model.hpp"

GridWorldModel::GridWorldModel()
{
}

GridWorldModel::~GridWorldModel()
{
}

float GridWorldModel::makeReward(const State &state, int actionID) const{
    GridWorldState const &gridWorldState = static_cast<GridWorldState const &>(state);
    if (!(is_terminal(gridWorldState))){
        return -0.1;
    }
    if (gridWorldState.agents[0].get_y() == 2){
        return 1.0;
    }
    return -1.0;
}

float GridWorldModel::makeReward(const State &state) const{
    GridWorldState const &gridWorldState = static_cast<GridWorldState const &>(state);
    //	std::cout << "x:" << gridWorldState.agents[0].get_y() << " y:" << gridWorldState.agents[0].get_y() << std::endl;
    if (!(is_terminal(gridWorldState))){
        return -0.1;
    }

    if (gridWorldState.agents[0].get_y() == 2){
        return 1.0;
    }

    return -1.0;
}

std::unique_ptr<State> GridWorldModel::makeNextState(const State &state, int actionID) const{

    GridWorldState const &gridWorldState = static_cast<GridWorldState const &>(state);
    // Available actions: 0(up), 1(down), 2(left), 3(right)

    if ((float)std::rand() /(float)RAND_MAX > 0.8){
        switch (actionID) {
        case 0:
            if ((float)std::rand() /(float)RAND_MAX > 0.5)
                actionID = 2;
            else
                actionID = 3;
            break;
        case 1:
            if ((float)std::rand() /(float)RAND_MAX > 0.5)
                actionID = 2;
            else
                actionID = 3;
            break;
        case 2:
            if ((float)std::rand() /(float)RAND_MAX > 0.5)
                actionID = 0;
            else
                actionID = 1;
            break;
        case 3:
            if ((float)std::rand() /(float)RAND_MAX > 0.5)
                actionID = 0;
            else
                actionID = 1;
            break;
        }
    }

    int x = gridWorldState.agents[0].get_x();
    int y = gridWorldState.agents[0].get_y();

    switch (actionID) {
    case 0:
        y = std::min(y + 1, MAX_Y);
        //			std::cout << "1: " << y << std::endl;
        break;
    case 1:
        y = std::max(y - 1, 0);
        //			std::cout << "2: " << y << std::endl;
        break;
    case 2:
        x = std::max(x - 1, 0);
        //			std::cout << "3: " << x << std::endl;
        break;
    case 3:
        x = std::min(x + 1, MAX_X);
        //			std::cout << "4: " << x << std::endl;
        break;
    }

    if ((x == 1) && (y == 1)){
        x = gridWorldState.agents[0].get_x();
        y = gridWorldState.agents[0].get_y();
    }
    //	std::cout << "Next state: " << x << y << std::endl;
    // Create an updated agent

    GridWorldAgent agent(x, y);
    std::vector<GridWorldAgent> agents{agent};

    //Create the next state which will belong to the child node

    std::unique_ptr<State> nextStatePtr(new GridWorldState(agents));
    return nextStatePtr;
}

std::unique_ptr<Observation> GridWorldModel::makeObservation(const State &nextState) const{
    GridWorldState const &gridWorldNextState = static_cast<GridWorldState const &>(nextState);
    std::unique_ptr<Observation> obsPtr(new GridWorldObservation(gridWorldNextState));
    return obsPtr;
}

unsigned int GridWorldModel::getObservationId(Observation &observation){
    GridWorldObservation const &gridWorldObservation = static_cast<GridWorldObservation const &>(observation);
    return gridWorldObservation.get_observation_id();
}

bool GridWorldModel::is_terminal(const State &state) const{
    GridWorldState const &gridWorldState = static_cast<GridWorldState const &>(state);
    if ((gridWorldState.agents[0].get_x() == 3) && (gridWorldState.agents[0].get_y() != 0)){
        return true;
    }
    return false;
}

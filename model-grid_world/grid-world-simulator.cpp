#include "grid-world-state.hpp"
#include "grid-world-simulator.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

GridWorldSimulator::GridWorldSimulator(GridWorldState state) : state(state)
{
}

GridWorldSimulator::~GridWorldSimulator()
{
}

void GridWorldSimulator::makeNextState(int actionID){
    state.agents[0].actionModel(actionID);
}

GridWorldObservation GridWorldSimulator::makeObservation(const GridWorldState &state) const{
    return GridWorldObservation(state);
}

int GridWorldSimulator::chooseAction(){
    //Pick a random action
    //	 std::srand(std::time(nullptr));
    //	 float randNumber = float(std::rand())/float(RAND_MAX);
    //	 std::cout << std::rand()%4 << std::endl;
    return state.agents[0].availableActions[std::rand()%4];
}

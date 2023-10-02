#ifndef GRIDWORLDSIMULATOR_HPP
#define GRIDWORLDSIMULATOR_HPP

#include "grid-world-observation.hpp"
#include "grid-world-state.hpp"
#include "../model-abstract/simulator.hpp"

class GridWorldSimulator : public Simulator
{
public:
    GridWorldSimulator(GridWorldState state);
    ~GridWorldSimulator();

    void makeNextState(int actionID);
    GridWorldObservation makeObservation(const GridWorldState &state) const;
    int chooseAction();
private:
    GridWorldState state;
};

#endif // GRIDWORLDSIMULATOR_HPP

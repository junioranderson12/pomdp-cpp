#ifndef GRIDWORLDSTATE_HPP
#define GRIDWORLDSTATE_HPP

#include <vector>
#include <memory>

#include "grid-world-agent.hpp"
#include "../model-abstract/state.hpp"

class GridWorldState : public State
{
public:
    GridWorldState(std::vector<GridWorldAgent> agents);
    ~GridWorldState();
    std::vector<GridWorldAgent> agents;
    //	std::vector<std::unique_ptr<Agent>> get_agents() const;
};

#endif // GRIDWORLDSTATE_HPP

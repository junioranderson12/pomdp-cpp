#include "grid-world-state.hpp"

#include <vector>
#include <memory>


GridWorldState::GridWorldState(std::vector<GridWorldAgent> agents) : agents(agents)
{
}

GridWorldState::~GridWorldState()
{
}

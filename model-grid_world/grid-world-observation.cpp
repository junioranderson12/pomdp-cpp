
#include "grid-world-agent.hpp"
#include "grid-world-state.hpp"
#include "grid-world-observation.hpp"

GridWorldObservation::GridWorldObservation(const GridWorldState &state)
{

    if ((state.agents[0].get_x() == 2) || ((state.agents[0].get_x() == 3) and (state.agents[0].get_y() == 1))){
        observationId = 1;
    }
    else{
        observationId = 0;
    }

}

GridWorldObservation::~GridWorldObservation()
{
}

unsigned int GridWorldObservation::get_observation_id() const{
    return observationId;
}

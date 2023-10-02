#ifndef GRIDWORLDOBSERVATION_HPP
#define GRIDWORLDOBSERVATION_HPP


#include "grid-world-state.hpp"
#include "../model-abstract/observation.hpp"

class GridWorldObservation : public Observation
{
public:
    GridWorldObservation(const GridWorldState &state);
    ~GridWorldObservation();
    unsigned int get_observation_id() const;

private:
    unsigned int observationId;
};

#endif // GRIDWORLDOBSERVATION_HPP

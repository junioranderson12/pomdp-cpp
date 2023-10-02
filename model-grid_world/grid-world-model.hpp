#ifndef GRIDWORLDMODEL_HPP
#define GRIDWORLDMODEL_HPP

#include <memory>

#include "grid-world-observation.hpp"
#include "grid-world-state.hpp"
#include "../model-abstract/model.hpp"
#define MAX_X 3
#define MAX_Y 2
#define SIGMA 1.0
class GridWorldModel : public Model
{
public:
    GridWorldModel();
    ~GridWorldModel();
    virtual float makeReward(const State &state, int actionID) const override;
    virtual float makeReward(const State &state) const override;
    virtual std::unique_ptr<State> makeNextState(const State &state, int actionID) const override;
    virtual std::unique_ptr<Observation> makeObservation(const State &nextState) const override;

    unsigned int getObservationId(Observation& observation);
    bool is_terminal(const State &state) const;

    int availableActions[4] = {0, 1, 2, 3};


};

#endif // GRIDWORLDMODEL_HPP

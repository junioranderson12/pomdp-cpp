#ifndef MODEL_HPP
#define MODEL_HPP

#include <memory>
//#include "ObsContinuous.hpp"
#include "observation.hpp"
#include "state.hpp"

class Model
{
public:
    Model();
    virtual ~Model();

    virtual float makeReward(const State &state, int actionID) const = 0;
    virtual float makeReward(const State &state) const = 0;
    virtual std::unique_ptr<State> makeNextState(const State &state, int actionID) const = 0;
    virtual std::unique_ptr<Observation> makeObservation(const State &nextState) const = 0;
//    std::unique_ptr<ObsContinuous> makeObsContinuous(const State &nextState, unsigned int obsId) const;
    virtual bool is_terminal(const State &state) const = 0;
//    float makeWeight(const State &nextState, const ObsContinuous &observation);
//    float pdf(float mu, float sigma, float x);
};

#endif // MODEL_HPP

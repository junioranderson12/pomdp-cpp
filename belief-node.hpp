#ifndef BELIEFNODE_HPP
#define BELIEFNODE_HPP

#include <array>
#include <map>
#include <tuple>
#include <numeric>
#include <random>
#include <memory>

//#include "model-abstract/ObsContinuous.hpp"
#include "model-abstract/state.hpp"
#define ACTION_SIZE 4
#define MAX_PARTICLES 100

class BeliefNode
{
public:
    BeliefNode(BeliefNode* parentNodePtr);
    //	BeliefNode(const BeliefNode&) = delete;
    //	BeliefNode& operator=(const BeliefNode&) = delete;
    ~BeliefNode() = default;

    BeliefNode* parentNodePtr;
    std::vector< std::unique_ptr<State> > belief;
    std::array<int, ACTION_SIZE> actionsEpisodes;
    std::array<float, ACTION_SIZE> actionsValues;
    std::array<float, ACTION_SIZE> QValues;


    //	std::vector<int> nonUsedActions;
    float value = 0;
    int numberOfEpisodes;
    std::map<int, std::map<int, BeliefNode*>> childMap;

    static int nodeId;

    bool is_child(int actionId, int obsId) const;
    void associate_particle(int actionId);
    void associate_particle();
    BeliefNode* addChild(BeliefNode* currentNode, int actionId, unsigned int obsId);
    BeliefNode* getChild(BeliefNode* currentNode, int actionId, unsigned int obsId);

    //POMCPOW only
//    std::array<int, ACTION_SIZE> hao{};
//    std::array<std::vector<int>, ACTION_SIZE> Mhao;
//    std::array<std::map<unsigned int, ObsContinuous>, ACTION_SIZE> obsMap;
//    std::vector<float> weights;
//    std::default_random_engine generator;

    //POMCPOW methods
//    int get_likely_obs(int actionId);
//    void update_pomcpow_vars(int actionId, int obsId);
//    void set_pocmpow_vars(int actionId);
//    void add_observation(int actionId, unsigned int obsId, ObsContinuous& observation);
//    void update_belief(std::unique_ptr<State> nextStatePtr, float weight);
//    State* sample_state();

};

#endif // BELIEFNODE_HPP

#ifndef BELIEFTREE_HPP
#define BELIEFTREE_HPP

#include <memory>
#include "belief-node.hpp"
#include "model-abstract/model.hpp"
#define MAX_DEPTH 8

template < class ConcreteModel >
//requires (std::derived_from < TipoConcretoModelo, Modelo >)
class BeliefTree
{
public:
    BeliefTree(BeliefNode *rootNodePtr);
    ~BeliefTree();
    const float gamma = 0.95;
    const float c = 200;
    BeliefNode *rootNodePtr = nullptr;
    std::unique_ptr<ConcreteModel> model;
    void samplingEpisode();
    int UCBSelection(const BeliefNode &node);
    void updateAffectedNodesQValues(BeliefNode* nodePtr, std::vector<std::tuple<int, float>> &episode);


};

#endif // BELIEFTREE_HPP

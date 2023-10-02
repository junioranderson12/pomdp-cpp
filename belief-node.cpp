#include "belief-node.hpp"
#include <iostream>

BeliefNode::BeliefNode(BeliefNode* parentNodePtr) : parentNodePtr(parentNodePtr)
{
    //	nonUsedActions = std::vector<int>(ACTION_SIZE);
    //	std::iota(nonUsedActions.begin(), nonUsedActions.end(), 0);
    actionsEpisodes.fill(0);
    actionsValues.fill(0);
    QValues.fill(-10);
    numberOfEpisodes = 0;
    nodeId += 1;
}

//BeliefNode::~BeliefNode()
//{
//}

int BeliefNode::nodeId = 0;

bool BeliefNode::is_child(int actionId, int obsId) const{
    auto it1 = childMap.find(actionId);
    if (it1 == childMap.end()){
        return false;
    }
    auto it2 = it1->second.find(obsId);
    if (it2 == it1->second.end()){
        return false;
    }
    return true;
}

void BeliefNode::associate_particle(int actionId){
    actionsEpisodes[actionId] += 1;
    numberOfEpisodes += 1;
}

void BeliefNode::associate_particle(){
    numberOfEpisodes += 1;
}

BeliefNode* BeliefNode::addChild(BeliefNode* currentNode, int actionId, unsigned int obsId){
    BeliefNode* childNode(new BeliefNode(currentNode));

    //Add child to parent node
    auto iter = childMap.find(actionId);
    //Check if action has already been explored
    if (iter == childMap.end()){
        std::map<int, BeliefNode*> obsMap;
        obsMap.insert({obsId, childNode});
        childMap.insert({actionId, obsMap});
    }
    else{
        iter->second.insert({obsId, childNode});
    }

    iter = childMap.find(actionId);
    auto iter2 = iter->second.find(obsId);
    //	BeliefNode* childNodePtr = &iter2->second;
    return iter2->second;
}

BeliefNode* BeliefNode::getChild(BeliefNode* currentNode, int actionId, unsigned int obsId){
    auto iter1 = currentNode->childMap.find(actionId);
    auto iter2 = (iter1->second).find(obsId);
    //	BeliefNode* childNodePtr = &iter2->second;
    return iter2->second;
}

//int BeliefNode::get_likely_obs(int actionId){
//    std::discrete_distribution<int> distribution(Mhao[actionId].begin(), Mhao[actionId].end());
//    return distribution(generator);
//}

//void BeliefNode::update_pomcpow_vars(int actionId, int obsId){
//    Mhao[actionId][obsId] += 1;
//}

//void BeliefNode::set_pocmpow_vars(int actionId){
//    hao[actionId] += 1;
//    Mhao[actionId].push_back(1);
//}

//void BeliefNode::add_observation(int actionId, unsigned int obsId, ObsContinuous& observation){
//    obsMap[actionId].insert({obsId, observation});
//}

//void BeliefNode::update_belief(std::unique_ptr<State> nextStatePtr, float weight){
//    if (weights.size() < MAX_PARTICLES){
//        belief.push_back(std::move(nextStatePtr));
//        weights.push_back(weight);
//    }
//}

//State* BeliefNode::sample_state(){
//    std::discrete_distribution<int> distribution(weights.begin(), weights.end());
//    return belief[distribution(generator)].get();
//}

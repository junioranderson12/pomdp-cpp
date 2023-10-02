#include "belief-tree.hpp"

#include <cmath>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <iostream>

template < class ConcreteModel >
BeliefTree<ConcreteModel>::BeliefTree(BeliefNode *rootNodePtr) : rootNodePtr(rootNodePtr), model(new ConcreteModel())
{

}

template < class ConcreteModel >
BeliefTree<ConcreteModel>::~BeliefTree()
{
}

template < class ConcreteModel >
void BeliefTree<ConcreteModel>::updateAffectedNodesQValues(BeliefNode* nodePtr, std::vector<std::tuple<int, float>> &episode){

    float tmpValue = 0.;

    //Note that the root value is not updated, since it does not affect the policy
    for (int i=(episode.size()-1); i > 0; i--){

        //Update node value
        nodePtr->value += std::get<1>(episode[i]) * std::pow(gamma, i);
        tmpValue += nodePtr->value/nodePtr->numberOfEpisodes;

        //Parent node
        BeliefNode* parentNodePtr = nodePtr->parentNodePtr;

        //Action value to be updated
        int actionId = std::get<0>(episode[i-1]);

        parentNodePtr->actionsValues[actionId] += tmpValue;
        parentNodePtr->QValues[actionId] = parentNodePtr->actionsValues[actionId]/parentNodePtr->actionsEpisodes[actionId];

        //Change the current node by its parent
        nodePtr = parentNodePtr;
    }

}

template < class ConcreteModel >
int BeliefTree<ConcreteModel>::UCBSelection(const BeliefNode &node){
    std::array<float, ACTION_SIZE> Q_aUCB;
    for (int i=0; i < ACTION_SIZE; i++){
        float bonus = c * std::sqrt(std::log(node.numberOfEpisodes+1)/(node.actionsEpisodes[i]+1e-15));
        Q_aUCB[i] = node.QValues[i] + bonus;
    }
    float *max = std::max_element(std::begin(Q_aUCB), std::end(Q_aUCB));
    return max - std::begin(Q_aUCB);
}

template < class ConcreteModel >
void BeliefTree<ConcreteModel>::samplingEpisode(){
    //	for (int i=0; i < ACTION_SIZE; i++){
    //		std::cout << rootNodePtr->QValues[i] << " ";
    //	}
    //	std::cout << std::endl;
    //	for (int i=0; i < ACTION_SIZE; i++){
    //		std::cout << rootNodePtr->actionsEpisodes[i] << " ";
    //	}
    //	std::cout << std::endl;

    //Sample a state s from the initial belief b0
    State* state0Ptr = (rootNodePtr->belief[std::rand()%(rootNodePtr->belief.size())]).get();

    BeliefNode* currentNode = rootNodePtr;

    //Create the episode
    std::vector<std::tuple<int, float>> episode;

    //Stop criteria
    bool isDoneModeUCB = true;
    bool isNotTerminalState = true;

    //Tree depth
    int particleDepth = 0;

    //Expand tree until find a leaf node
    while((particleDepth < MAX_DEPTH) && isDoneModeUCB && isNotTerminalState){
        //Check if all action has been tried at the current node
        int sumActions = 0;
        sumActions = std::accumulate(currentNode->actionsEpisodes.begin(), currentNode->actionsEpisodes.end(), sumActions);
        if (sumActions < ACTION_SIZE){
            isDoneModeUCB = false;
            //		if (currentNode->nonUsedActions.size() > 0){
            //			actionId = currentNode->nonUsedActions[std::rand()%ACTION_SIZE];
            //			//Remove the actionId element
            //			new_end = std::remove(currentNode->nonUsedActions.begin(),
            //									currentNode->nonUsedActions.end(), actionId);
        }
        int actionId = UCBSelection(*currentNode);

        //Call generative model
        float reward = model->makeReward(*state0Ptr, actionId);
        std::unique_ptr<State> nextStatePtr = model->makeNextState(*state0Ptr, actionId);
        std::unique_ptr<Observation> observationPtr = model->makeObservation(*nextStatePtr);
        unsigned int obsId = model->getObservationId(*observationPtr);

        //Make nextState the current state for next iteration
        state0Ptr = nextStatePtr.get();

        //Associate particle
        currentNode->associate_particle(actionId);

        //Create tuple (action, reward) and add it to episode. Useful in computing node values
        episode.push_back(std::make_tuple(actionId, reward));

        //Check if node exists
        if (currentNode->is_child(actionId, obsId)){
            //Choose the child node according to action and observation
            currentNode = currentNode->getChild(currentNode, actionId, obsId);
        }
        else{
            //Create a new node, since the path action->observation does not exist yet
            currentNode = currentNode->addChild(currentNode, actionId, obsId);

        }

        //Check if nextState is terminal
        isNotTerminalState = !(model->is_terminal(*nextStatePtr));

        //Update belief and particle depth
        currentNode->belief.push_back(std::move(nextStatePtr));

        particleDepth += 1;
    }

    //Associate particle
    currentNode->associate_particle();

    float reward;
    if (!isDoneModeUCB){
        //TODO: put some heuristic here instead of simple reward function
        reward = model->makeReward(*state0Ptr);
    }
    else{
        reward = model->makeReward(*state0Ptr);
    }

    episode.push_back(std::make_tuple(0, reward));

    //Finnaly, update node values and Q_values
    updateAffectedNodesQValues(currentNode, episode);
}

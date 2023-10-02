#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <memory>
#include <iostream>

#include "model-grid_world/grid-world-agent.hpp"
#include "model-grid_world/grid-world-observation.hpp"
#include "model-grid_world/grid-world-simulator.hpp"
#include "model-grid_world/grid-world-state.hpp"
#include "model-grid_world/grid-world-model.hpp"
#include "belief-tree.hpp"
#include "belief-tree.cpp"
//#include "POMCPOW.hpp"
//#include "POMCPOW.cpp"

int main()
{
    //	std::unique_ptr<int> P1(new int(5));
    //	int a = 3;
    //	int *P2;
    //	std::cout << &P1 << std::endl;
    //	std::cout << &P2 << std::endl;
    //	std::cout << &a << std::endl;

    //	GridWorldAgent agent(2, 1);
    //	std::vector<GridWorldAgent> agents{agent};
    //	GridWorldState state(agents);
    //	std::cout << "x:" << state.agents[0].get_x() << std::endl;
    //	GridWorldSimulator simulator(state);
    //	GridWorldObservation obs = simulator.makeObservation(state);
    std::cout << "here" << std::endl;
    std::srand(std::time(nullptr));
    auto start = std::chrono::high_resolution_clock::now();

    //	int actionID;
    //	while(!(state.is_terminal())){
    ////	for(int i=0; i<100; i++){
    //		actionID = std::rand()%4;
    //		std::cout << agent.get_x() << "," << agent.get_y() << "," << obs.get_observation_id() << std::endl;
    //		simulator.makeNextState(actionID);
    //		obs = simulator.makeObservation(state);
    //	}

    BeliefNode rootNode(nullptr);

    for (int x=0; x<4; x++){
        for (int y=0; y<3; y++){
            if (!(((x == 1) && (y == 1)) || ((x == 3) && (y == 2)) || ((x == 3) && (y == 1)))){
                GridWorldAgent agent(x, y);
                std::cout << "x:" << x << " y:" << y << std::endl;
                std::vector<GridWorldAgent> agents{agent};
                std::unique_ptr<State> statePtr(new GridWorldState(agents));
                rootNode.belief.push_back(std::move(statePtr));

            }
        }
    }

    BeliefTree<GridWorldModel> tree(&rootNode);
//    POMCPOW<GridWorldModel> tree(&rootNode);

    for(int i=0; i<60000; i++){
        tree.samplingEpisode();

    }
    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";
    return 0;
}

#ifndef GRIDWORLDAGENT_HPP
#define GRIDWORLDAGENT_HPP


class GridWorldAgent
{
public:
    GridWorldAgent(int x, int y);
    ~GridWorldAgent();
    int get_x() const;
    int get_y() const;
    void actionModel(int actionID);
    int availableActions[4] = {0, 1, 2, 3};
private:
    int x;
    int y;

};

#endif // GRIDWORLDAGENT_HPP

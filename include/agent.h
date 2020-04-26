#pragma once

#include <SFML/Graphics.hpp>
#include <queue>
#include <unordered_set>

#include "action.h"
#include "state_machine.h"

class Agent {
public:
    Agent(float x, float y);

    void update(float dt);
    void draw(sf::RenderTarget& target);

    std::unordered_set<Action*> availableActions;
    std::unordered_set<std::string> state;
    std::unordered_set<std::string> goal;

private:
    float x;
    float y;

    sf::Sprite sprite;
    StateMachine stateMachine;
    std::queue<Action*> currentActions;

    static void idleState(Agent* agent, float dt);
    static void moveState(Agent* agent, float dt);
    static void performActionState(Agent* agent, float dt);
};

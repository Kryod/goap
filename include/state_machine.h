#pragma once

#include <functional>
#include <stack>

class Agent; // Forward declaration for State

class StateMachine {
private:
    typedef std::function<void(Agent*, float)> State;

public:
    void update(Agent* agent, float dt);
    void pop();
    void push(State state);

private:
    std::stack<State> stack;
};

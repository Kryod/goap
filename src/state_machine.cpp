#include "state_machine.h"

void StateMachine::update(Agent* agent, float dt) {
    if (!this->stack.empty()) {
        this->stack.top()(agent, dt);
    }
}

void StateMachine::pop() { this->stack.pop(); }

void StateMachine::push(StateMachine::State state) { this->stack.push(state); }

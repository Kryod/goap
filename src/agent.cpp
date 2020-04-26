#include "agent.h"
#include "planner.h"
#include "texture_loader.h"
#include "world.h"

void Agent::idleState(Agent* agent, float dt) {
    World* world = World::instance;
    std::unordered_set<std::string> state(agent->state);
    const std::unordered_set<std::string>& worldState = world->getState();
    state.insert(worldState.begin(), worldState.end());

    std::queue<Action*> plan =
        Planner::plan(agent, agent->availableActions, state, agent->goal);
    if (!plan.empty()) {
        agent->currentActions = plan;

        agent->stateMachine.pop(); // Remove the idle state
        agent->stateMachine.push(&performActionState);
    }
}

void Agent::moveState(Agent* agent, float dt) {
    Action* action = agent->currentActions.front();
    if (action->target != nullptr) {
        sf::Vector2f moveTarget = static_cast<sf::Vector2f>(
            action->target->getPos() * Map::TILE_SIZE);
        // TODO: move towards target
        agent->stateMachine.pop();
    } else {
        agent->stateMachine.pop(); // Move
        agent->stateMachine.pop(); // Perform
        agent->stateMachine.push(&idleState);
    }
}

void Agent::performActionState(Agent* agent, float dt) {
    if (agent->currentActions.empty()) {
        // No plan
        agent->stateMachine.pop();
        agent->stateMachine.push(&idleState);
        return;
    }

    Action* action = agent->currentActions.front();
    if (action->isDone()) {
        // The action is done, remove it so we can perform the next one
        agent->currentActions.pop();
    }

    if (!agent->currentActions.empty()) {
        action = agent->currentActions.front();
        if (action->isInRange()) {
            if (action->perform()) {
                // Successfully performed
                agent->stateMachine.pop();
                agent->stateMachine.push(&idleState);
            }
        } else {
            // Get closer
            agent->stateMachine.push(&moveState);
        }
    } else {
        // No actions left, start planning again
        agent->stateMachine.pop();
        agent->stateMachine.push(&idleState);
    }
}

Agent::Agent(float x, float y)
    : x(x),
      y(y),
      sprite(*TextureLoader::instance().get("unit/medievalUnit_24")) {

    this->stateMachine.push(&idleState);
}

void Agent::update(float dt) { this->stateMachine.update(this, dt); }

void Agent::draw(sf::RenderTarget& target) {
    this->sprite.setPosition(this->x, this->y);
    target.draw(this->sprite);
}

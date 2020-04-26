#include "agent.h"
#include "map.h"
#include "texture_loader.h"

void Agent::idleState(Agent* agent, float dt) {}

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

void Agent::performActionState(Agent* agent, float dt) {}

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

#include "agent.h"
#include "map.h"
#include "texture_loader.h"
#include <cmath>

void Agent::idleState(Agent* agent, float dt) {}

sf::Vector2f normalize(const sf::Vector2f& source) {
    float length = sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
        return sf::Vector2f(source.x / length, source.y / length);
    else
        return source;
}

void Agent::moveState(Agent* agent, float dt) {
    Action* action = agent->currentActions.front();
    if (action->target != nullptr) {
        sf::Vector2f moveTarget = static_cast<sf::Vector2f>(
            action->target->getPos() * Map::TILE_SIZE);
        moveTarget.x += 0.5 * Map::TILE_SIZE;
        moveTarget.y += 0.5 * Map::TILE_SIZE;
        sf::Vector2f pos(agent->x, agent->y);
        sf::Vector2f vec = normalize(moveTarget - pos) * dt * 0.25f;
        agent->x = agent->x + vec.x;
        agent->y = agent->y + vec.y;
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

    this->sprite.setOrigin(Map::TILE_SIZE / 2.0f, Map::TILE_SIZE / 2.0f);
    this->stateMachine.push(&idleState);
}

void Agent::update(float dt) { this->stateMachine.update(this, dt); }

void Agent::draw(sf::RenderTarget& target) {
    this->sprite.setPosition(this->x, this->y);
    target.draw(this->sprite);
}

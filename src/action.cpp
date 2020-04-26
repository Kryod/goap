#include "action.h"
#include "m_assert.h"

Action::Action(const float cost, const std::string& name) : name(name), target(nullptr), inRange(false) {
    this->setCost(cost);
}

float Action::getCost() const { return this->cost; }

void Action::setCost(const float cost) {
    M_ASSERT(cost >= 0.0f, "Cost cannot be negative");

    this->cost = cost;
}

void Action::addPrecondition(const std::string& precondition) {
    this->preconditions.insert(precondition);
}

void Action::removePrecondition(const std::string& precondition) {
    this->preconditions.erase(precondition);
}

bool Action::hasPrecondition(const std::string& precondition) const {
    return this->preconditions.find(precondition) != this->preconditions.end();
}

const std::unordered_set<std::string>& Action::getPreconditions() const {
    return this->preconditions;
}

void Action::addEffect(const std::string& effect) {
    this->effects.insert(effect);
}

void Action::removeEffect(const std::string& effect) {
    this->effects.erase(effect);
}

bool Action::hasEffect(const std::string& effect) const {
    return this->effects.find(effect) != this->effects.end();
}

const std::unordered_set<std::string>& Action::getEffects() const {
    return this->effects;
}

bool Action::isInRange() const {
    return this->inRange;
}

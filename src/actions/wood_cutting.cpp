#include "actions/wood_cutting.h"
#include "world.h"

WoodCutting::WoodCutting(const float cost, const std::string& name)
    : Action(cost, name) {}

bool WoodCutting::checkCondition(Agent* agent) {
    return World::instance->findItem(Item::Tool) != nullptr &&
           World::instance->findItem(Item::ChoppingBlock) != nullptr;
}

bool WoodCutting::perform() { return true; }

bool WoodCutting::isDone() { return false; }

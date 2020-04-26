#include "actions/wood_cutting.h"
#include "world.h"

WoodCutting::WoodCutting(const float cost, const std::string& name)
    : Action(cost, name) {}

bool WoodCutting::checkCondition() const {
    return World::instance->findItem(Item::Tool) != nullptr &&
           World::instance->findItem(Item::WoodLog) != nullptr;
}

bool WoodCutting::perform() { return true; }

bool WoodCutting::isDone() { return false; }

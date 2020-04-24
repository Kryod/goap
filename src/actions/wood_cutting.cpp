#include "actions/wood_cutting.h"
#include "world.h"

bool WoodCutting::checkCondition() const {
    return World::instance->findItem(Item::Tool) != nullptr &&
           World::instance->findItem(Item::WoodLog) != nullptr;
}

bool WoodCutting::perform() { return true; }

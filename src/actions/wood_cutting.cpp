#include "actions/wood_cutting.h"
#include "world.h"

WoodCutting::WoodCutting(const float cost, const std::string& name)
    : Action(cost, name) {}

bool WoodCutting::checkCondition(Agent* agent) {

    ItemStack* closestChoppingBlock =
        World::instance->getNearestItemStack(Item::ChoppingBlock, agent->getPos());
    this->target = closestChoppingBlock;
    return World::instance->findItem(Item::Tool) != nullptr &&
           closestChoppingBlock != nullptr;
}

bool WoodCutting::perform(float dt) { return true; }

bool WoodCutting::isDone() { return false; }

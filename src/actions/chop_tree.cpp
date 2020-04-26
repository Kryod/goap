#include "actions/chop_tree.h"
#include "world.h"

ChopTree::ChopTree(const float cost, const std::string& name)
    : Action(cost, name) {}

bool ChopTree::checkCondition(Agent* agent) {
    ItemStack* closestTree =
        World::instance->getNearestItemStack(Item::Tree, agent->getPos());
    this->target = closestTree;
    return closestTree != nullptr &&
           World::instance->findItem(Item::Tool) != nullptr;
}

bool ChopTree::perform() { return true; }

bool ChopTree::isDone() { return false; }

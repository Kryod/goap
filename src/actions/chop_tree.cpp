#include "actions/chop_tree.h"
#include "world.h"

ChopTree::ChopTree(const float cost, const std::string& name)
    : Action(cost, name) {
    this->t = 0.0f;
    this->workDuration = 1000.0f; 
}

bool ChopTree::checkCondition(Agent* agent) {
    ItemStack* closestTree =
        World::instance->getNearestItemStack(Item::Tree, agent->getPos());
    this->target = closestTree;
    return closestTree != nullptr &&
           World::instance->findItem(Item::Tool) != nullptr;
}

bool ChopTree::perform(float dt) {
    this->t += dt;
    return true;
}

bool ChopTree::isDone() {
    bool done = this->t >= this->workDuration;
    if (done) {
        this->t = 0.0f;
        this->target = nullptr;
    }
    return done;
}

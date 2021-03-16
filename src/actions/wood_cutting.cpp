#include "actions/wood_cutting.h"
#include "world.h"

WoodCutting::WoodCutting(const float cost, const std::string& name)
    : Action(cost, name) {
    this->t = 0.0f;
    this->workDuration = 1000.0f; 
}

bool WoodCutting::checkCondition(Agent* agent) {

    ItemStack* closestChoppingBlock =
        World::instance->getNearestItemStack(Item::ChoppingBlock, agent->getPos());
    this->target = closestChoppingBlock;
    return World::instance->findItem(Item::Tool) != nullptr &&
           closestChoppingBlock != nullptr;
}

bool WoodCutting::perform(float dt) { 
    this->t += dt;
    return true;
}

bool WoodCutting::isDone() {
    bool done = this->t >= this->workDuration;
    if (done) {
        this->t = 0.0f;
        this->target = nullptr;
    }
    return done;
}

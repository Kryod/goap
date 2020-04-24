#include "actions/bundle_sticks.h"
#include "world.h"

BundleSticks::BundleSticks(const float cost, const std::string& name)
    : Action(cost, name) {}

bool BundleSticks::checkCondition() const {
    return World::instance->findItem(Item::WoodStick) != nullptr;
}

bool BundleSticks::perform() { return true; }

#include "actions/bundle_sticks.h"
#include "world.h"

bool BundleSticks::checkCondition() const {
    return World::instance->findItem(Item::WoodStick) != nullptr;
}

bool BundleSticks::perform() { return true; }

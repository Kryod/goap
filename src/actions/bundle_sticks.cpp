#include "actions/bundle_sticks.h"
#include "world.h"

BundleSticks::BundleSticks(const float cost, const std::string& name)
    : Action(cost, name) {}

bool BundleSticks::checkCondition(Agent* agent) {
    return true;
}

bool BundleSticks::perform() { return true; }

bool BundleSticks::isDone() { return false; }

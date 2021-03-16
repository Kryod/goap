#include "actions/bundle_sticks.h"
#include "world.h"

BundleSticks::BundleSticks(const float cost, const std::string& name)
    : Action(cost, name) {
    this->t = 0.0f;
    this->workDuration = 1000.0f; 
}

bool BundleSticks::checkCondition(Agent* agent) {
    return true;
}

bool BundleSticks::perform(float dt) { 
    this->t += dt;
    return true;
}

bool BundleSticks::isDone() {
    bool done = this->t >= this->workDuration;
    if (done) {
        this->t = 0.0f;
        this->target = nullptr;
    }
    return done;
}

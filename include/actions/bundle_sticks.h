#pragma once

#include "action.h"
#include "agent.h"

class BundleSticks : public Action {
public:
    BundleSticks(const float cost, const std::string& name);

    bool checkCondition(Agent* agent) override;
    bool perform(float dt) override;
    bool isDone() override;
};

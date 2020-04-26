#pragma once

#include "action.h"
#include "agent.h"

class ChopTree : public Action {
public:
    ChopTree(const float cost, const std::string& name);

    bool checkCondition(Agent* agent) override;
    bool perform() override;
    bool isDone() override;
};

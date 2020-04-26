#pragma once

#include "action.h"
#include "agent.h"

class WoodCutting : public Action {
public:
    WoodCutting(const float cost, const std::string& name);

    bool checkCondition(Agent* agent) override;
    bool perform() override;
    bool isDone() override;
};

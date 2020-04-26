#pragma once

#include "action.h"

class WoodCutting : public Action {
public:
    WoodCutting(const float cost, const std::string& name);

    bool checkCondition() const override;
    bool perform() override;
    bool isDone() override;
};

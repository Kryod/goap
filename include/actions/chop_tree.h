#pragma once

#include "action.h"

class ChopTree : public Action {
public:
    ChopTree(const float cost, const std::string& name);

    bool checkCondition() const override;
    bool perform() override;
    bool isDone() override;
};

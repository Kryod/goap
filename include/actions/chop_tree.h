#pragma once

#include "action.h"

class ChopTree : public Action {
public:
    using Action::Action;

    bool checkCondition() const override;
    bool perform() override;
};

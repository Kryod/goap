#pragma once

#include "action.h"

class BundleSticks : public Action {
public:
    using Action::Action;

    bool checkCondition() const override;
    bool perform() override;
};

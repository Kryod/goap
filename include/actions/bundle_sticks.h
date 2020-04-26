#pragma once

#include "action.h"

class BundleSticks : public Action {
public:
    BundleSticks(const float cost, const std::string& name);

    bool checkCondition() const override;
    bool perform() override;
    bool isDone() override;
};

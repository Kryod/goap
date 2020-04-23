#pragma once

#include <unordered_set>

class Action {
public:
    Action(const float cost);

    float getCost() const;
    void setCost(const float cost);

    void addPrecondition(const std::string &precondition);
    void removePrecondition(const std::string &precondition);
    bool hasPrecondition(const std::string &precondition) const;

    void addEffect(const std::string &effect);
    void removeEffect(const std::string &effect);
    bool hasEffect(const std::string &effect) const;

private:
    std::unordered_set<std::string> preconditions;
    std::unordered_set<std::string> effects;
    float cost;
};

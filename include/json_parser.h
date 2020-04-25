#pragma once

#include <unordered_set>

#include "action.h"
#include "json.h"
#include "world.h"

using json = nlohmann::json;

class JsonParser {
public:
    void loadFile(const std::string& filename);
    void loadWorld() const;
    std::unordered_set<Action*> loadActions() const;

private:
    void fillEffectsAndConditions(Action* action,
                                  const json& action_json) const;
    void loadItems(World* world) const;
    json j;
};

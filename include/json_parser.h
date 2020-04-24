#pragma once

#include <unordered_set>

#include "json.h"
#include "world.h"
#include "action.h"

using json = nlohmann::json;

class JsonParser {
public:
    void loadFile(const std::string& filename);
    void loadWorld();
    std::unordered_set<Action*> loadActions();
private:
    void fillEffectsAndConditions(Action* action, json& action_json);
    void loadItems(World* world);
    json j;
};
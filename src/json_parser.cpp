#include "json_parser.h"
#include "actions.h"
#include <fstream>
#include <iostream>

void JsonParser::loadFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "An error occured while opening file: " << filename
                  << std::endl;
    }
    file >> this->j;
}

void JsonParser::loadWorld() {
    json json_map = this->j["world"]["map"];
    Map map(json_map["width"], json_map["height"], json_map["data"]);
    World::instance = new World(map);
}

void JsonParser::fillEffectsAndConditions(Action* action, json& action_json) {
    for (json& condition : action_json["preconditions"]) {
        action->addPrecondition(condition);
    }

    for (json& effect : action_json["effects"]) {
        action->addEffect(effect);
    }
}

std::unordered_set<Action*> JsonParser::loadActions() {
    std::unordered_set<Action*> actions;
    for (json& action : this->j["actions"]) {
        if (action["name"] == "chop_tree") {
            ChopTree* ac = new ChopTree(action["cost"], action["name"]);
            this->fillEffectsAndConditions(ac, action);
            actions.emplace(ac);
        }
        if (action["name"] == "wood_cutting") {
            WoodCutting* ac = new WoodCutting(action["cost"], action["name"]);
            this->fillEffectsAndConditions(ac, action);
            actions.emplace(ac);
        }
        if (action["name"] == "bundle_sticks") {
            BundleSticks* ac = new BundleSticks(action["cost"], action["name"]);
            this->fillEffectsAndConditions(ac, action);
            actions.emplace(ac);
        }
    }
    return actions;
}

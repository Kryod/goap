#include <fstream>
#include <iostream>

#include "actions.h"
#include "json_parser.h"

void JsonParser::loadFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "An error occured while opening file: " << filename
                  << std::endl;
    }
    file >> this->j;
}

void JsonParser::loadWorld() const {
    json json_map = this->j["world"]["map"];
    Map map(json_map["width"], json_map["height"], json_map["data"]);
    World* world = new World(map);
    loadItems(world);
    World::instance = world;
}

void JsonParser::fillEffectsAndConditions(Action* action,
                                          const json& action_json) const {
    for (const json& condition : action_json["preconditions"]) {
        action->addPrecondition(condition);
    }

    for (const json& effect : action_json["effects"]) {
        action->addEffect(effect);
    }
}

std::unordered_set<Action*> JsonParser::loadActions() const {
    std::unordered_set<Action*> actions;
    Action* a = nullptr;

    for (const json& action : this->j["actions"]) {
        if (action["name"] == "chop_tree") {
            a = new ChopTree(action["cost"], action["name"]);
        }
        if (action["name"] == "wood_cutting") {
            a = new WoodCutting(action["cost"], action["name"]);
        }
        if (action["name"] == "bundle_sticks") {
            a = new BundleSticks(action["cost"], action["name"]);
        }

        if (action != nullptr) {
            this->fillEffectsAndConditions(a, action);
            actions.emplace(a);
        }
    }
    return actions;
}

void JsonParser::loadItems(World* world) const {

    for (json itemStack : this->j["world"]["itemStacks"]) {
        if (world->itemTypes.find(itemStack["type"]) != world->itemTypes.end()) {
            world->addItemStack(ItemStack(world->itemTypes[itemStack["type"]],
                                          itemStack["x"], itemStack["y"]));
        } else {
            std::cerr << "Item type \"" << itemStack["type"]
                      << "\" not found for item stack" << std::endl;
        }
    }
}

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
    for (const json& action : this->j["actions"]) {
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

void JsonParser::loadItems(World* world) const {
    for (json itemStack : this->j["world"]["itemStacks"]) {
        if (itemStack["type"] == "tool") {
            world->addItemStack(
                ItemStack(Item::Tool, itemStack["x"], itemStack["y"]));
        }
        if (itemStack["type"] == "tree") {
            world->addItemStack(
                ItemStack(Item::Tree, itemStack["x"], itemStack["y"]));
        }
        if (itemStack["type"] == "woodlog") {
            world->addItemStack(
                ItemStack(Item::WoodLog, itemStack["x"], itemStack["y"]));
        }
        if (itemStack["type"] == "woodsticks") {
            world->addItemStack(
                ItemStack(Item::WoodStick, itemStack["x"], itemStack["y"]));
        }
    }
}

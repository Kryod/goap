#include <iostream>

#include "actions.h"
#include "planner.h"
#include "world.h"
#include "json_parser.h"

void cleanActions(std::unordered_set<Action*> actions) {
    for (Action* action: actions) {
        delete action;
    }
}

int main() {
    JsonParser j;

    j.loadFile("conf.json");
    j.loadWorld();

    World* world = World::instance;

    std::unordered_set<Action*> actions = j.loadActions();
    std::unordered_set<std::string> state { "has_tool", "chopping_block_available", "tree_available" };
    std::unordered_set<std::string> goals { "has_firewood" };
    std::queue<Action*> plan = Planner::plan(nullptr, actions, state, goals);

    if (plan.empty()) {
        std::cout << "No plan found";
    } else {
        std::cout << "Plan: ";
    }
    while (!plan.empty()) {
        Action* a = plan.front();
        std::cout << a->name;

        plan.pop();

        if (!plan.empty()) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;

    cleanActions(actions);
    delete world;
    World::instance = nullptr;
    return 0;
}

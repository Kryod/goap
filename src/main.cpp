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
    /*Map map(10, 10,
            "111110111111110000111111100011111111111111111111111111112111111222"
            "2222111111211111111121111111112111");
    World world(map);
    World::instance = &world;*/
    JsonParser j;

    j.loadFile("conf.json");
    j.loadWorld();

    World* world = World::instance;

    world->addItemStack(ItemStack(Item::Tool, 7, 3));
    world->addItemStack(ItemStack(Item::Tree, 2, 7));
    world->addItemStack(ItemStack(Item::WoodLog, 2, 8));

    world->addItemStack(ItemStack(Item::WoodStick, 4, 5));

    /*ChopTree chopTree(7.0f, "chop_tree");
    chopTree.addPrecondition("has_tool");
    chopTree.addPrecondition("tree_available");
    chopTree.addEffect("has_wood_logs");
    chopTree.addEffect("has_sticks");

    WoodCutting woodcutting(2.0f, "wood_cutting");
    woodcutting.addPrecondition("has_tool");
    woodcutting.addPrecondition("has_wood_logs");
    woodcutting.addPrecondition("chopping_block_available");
    woodcutting.addEffect("has_firewood");

    BundleSticks bundleSticks(8.0f, "bundle_sticks");
    bundleSticks.addPrecondition("has_sticks");
    bundleSticks.addEffect("has_firewood");

    std::unordered_set<Action*> actions { &chopTree, &woodcutting,
                                          &bundleSticks };*/

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
    return 0;
}

#include <iostream>
#include "action.h"
#include "world.h"

int main() {
    World world;

    Action chopTree(7.0f);
    chopTree.addPrecondition("has_tool");
    chopTree.addPrecondition("tree_available");
    chopTree.addEffect("has_wood_logs");
    chopTree.addEffect("has_sticks");

    Action woodcutting(2.0f);
    woodcutting.addPrecondition("has_tool");
    woodcutting.addPrecondition("has_wood_logs");
    woodcutting.addPrecondition("chopping_block_available");
    woodcutting.addEffect("has_firewood");

    Action bundleSticks(8.0f);
    bundleSticks.addPrecondition("has_sticks");
    bundleSticks.addEffect("has_firewood");

    return 0;
}

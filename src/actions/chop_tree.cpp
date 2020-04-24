#include "world.h"
#include "actions/chop_tree.h"

bool ChopTree::checkCondition() const {
    return World::instance->findItem(Item::Tool) != nullptr &&
           World::instance->findItem(Item::Tree) != nullptr;
}

bool ChopTree::perform() {
    return true;
}

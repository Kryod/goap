#include "actions/chop_tree.h"
#include "world.h"

ChopTree::ChopTree(const float cost, const std::string& name)
    : Action(cost, name) {}

bool ChopTree::checkCondition() const {
    return World::instance->findItem(Item::Tool) != nullptr &&
           World::instance->findItem(Item::Tree) != nullptr;
}

bool ChopTree::perform() { return true; }

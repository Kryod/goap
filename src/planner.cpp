#include <algorithm>

#include "planner.h"

std::queue<Action*>
Planner::plan(Agent* agent, std::unordered_set<Action*> actions,
              const std::unordered_set<std::string>& state,
              const std::unordered_set<std::string>& goals) {

    std::queue<Action*> queue;

    if (Planner::containsAll(goals, state)) {
        // Goal is already achieved
        return queue;
    }

    std::unordered_set<Action*> usableActions;
    for (Action* a : actions) {
        if (a->checkCondition(agent)) {
            usableActions.insert(a);
        }
    }

    std::vector<std::shared_ptr<Node>> leaves;
    auto root = std::shared_ptr<Node>(new Node(nullptr, 0.0f, state, nullptr));
    bool success = Planner::buildGraph(root, leaves, actions, goals);

    if (!success) {
        return queue;
    }

    std::shared_ptr<Node> cheapest = nullptr;
    for (const std::shared_ptr<Node>& leaf : leaves) {
        if (cheapest == nullptr || leaf->totalCost < cheapest->totalCost) {
            cheapest = leaf;
        }
    }

    std::shared_ptr<Node> n = cheapest;
    std::vector<Action*>
        tempVec; // We first store the actions in a vector and then in the
                 // queue, since we go from the leaves to the root, the queue
                 // would be reversed otherwise
    while (n != nullptr) {
        if (n->action != nullptr) {
            tempVec.insert(tempVec.begin(), n->action);
        }
        n = n->parent;
    }

    for (Action* a : tempVec) {
        queue.push(a);
    }

    return queue;
}

bool Planner::buildGraph(std::shared_ptr<Node> parent,
                         std::vector<std::shared_ptr<Node>>& leaves,
                         const std::unordered_set<Action*>& actions,
                         const std::unordered_set<std::string>& goals) {
    bool foundOne = false;

    for (Action* action : actions) {
        if (Planner::containsAll(action->getPreconditions(), parent->state)) {
            std::unordered_set<std::string> currentState(parent->state);
            currentState.insert(action->getEffects().begin(),
                                action->getEffects().end());

            auto node = std::shared_ptr<Node>(
                new Node(parent, parent->totalCost + action->getCost(),
                         currentState, action));

            if (Planner::containsAll(goals, currentState)) {
                leaves.push_back(node);
                foundOne = true;
            } else {
                std::unordered_set<Action*> subset(actions);
                subset.erase(action);
                bool found = Planner::buildGraph(node, leaves, subset, goals);
                if (found) {
                    foundOne = true;
                }
            }
        }
    }

    return foundOne;
}

bool Planner::containsAll(const std::unordered_set<std::string>& items,
                          const std::unordered_set<std::string>& state) {
    for (const std::string& value : items) {
        if (state.find(value) == state.end()) {
            return false;
        }
    }

    return true;
}

Planner::Node::Node(std::shared_ptr<Node> parent, float totalCost,
                    const std::unordered_set<std::string>& state,
                    Action* action)
    : parent(parent), totalCost(totalCost), state(state), action(action) {}

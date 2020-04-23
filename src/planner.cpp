#include "planner.h"

std::queue<Action*>
Planner::plan(void* agent, std::unordered_set<Action*> actions,
              const std::unordered_set<std::string>& state,
              const std::unordered_set<std::string>& goals) {

    std::queue<Action*> queue;

    std::unordered_set<Action*> usableActions;
    for (Action* a : actions) {
        // if (a.checkPrecondition(agent)) {
        usableActions.insert(a);
        // }
    }

    std::vector<Node> leaves;
    Node start(nullptr, 0.0f, state, nullptr);
    bool success = Planner::buildGraph(start, leaves, usableActions, goals);

    if (!success) {
        return queue;
    }

    Node* cheapest = nullptr;
    for (Node& leaf : leaves) {
        if (cheapest == nullptr || leaf.totalCost < cheapest->totalCost) {
            cheapest = &leaf;
        }
    }

    Node* n = cheapest;
    while (n != nullptr) {
        if (n->action != nullptr) {
            queue.emplace(n->action);
        }
        n = n->parent;
    }

    return queue;
}

bool Planner::buildGraph(const Node& parent, std::vector<Node>& leaves,
                         const std::unordered_set<Action*>& actions,
                         const std::unordered_set<std::string>& goals) {
    bool foundOne = false;

    for (Action* action : actions) {
        /*if (Planner::containsAll(action->getPreconditions(), parent.state)) {
            std::unordered_set<std::string> currentState =
                populate(parent.state, action->getEffects());
            Node node(&parent, parent.totalCost + action.getCost(),
                      currentState, action);

            if (Planner::containsAll(goals, currentState)) {
                leaves.push_back(std::move(node));
                foundOne = true;
            } else {
                std::unordered_set<Action> subset =
                    actionSubset(actions, action);
                bool found = Planner::buildGraph(node, leaves, subset, goals);
                if (found) {
                    foundOne = true;
                }
            }
        }*/
    }

    return foundOne;
}

Planner::Node::Node(Node* parent, float totalCost,
                    const std::unordered_set<std::string>& state,
                    Action* action)
    : parent(parent), totalCost(totalCost), state(state), action(action) {}

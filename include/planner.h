#pragma once

#include <memory>
#include <queue>
#include <unordered_set>

#include "action.h"

class Planner {
public:
    static std::queue<Action*>
    plan(void* agent, std::unordered_set<Action*> actions,
         const std::unordered_set<std::string>& state,
         const std::unordered_set<std::string>& goals);

private:
    class Node {
    public:
        Node(Node* parent, float totalCost,
             const std::unordered_set<std::string>& state, Action* action);

        Node* parent;
        float totalCost;
        std::unordered_set<std::string> state;
        Action* action;
    };

    static bool buildGraph(const Node& parent, std::vector<Node>& leaves,
                           const std::unordered_set<Action*>& actions,
                           const std::unordered_set<std::string>& goals);
};
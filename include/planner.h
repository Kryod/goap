#pragma once

#include <memory>
#include <queue>
#include <unordered_set>

#include "action.h"

class Planner {
public:
    /**
     * ### Brief
     * Plan what sequence of actions can fulfill the passed `goals`
     *
     * ### Param
     * **agent** the agent that would perform the actions
     * **actions** a list of available actions
     * **state** an initial state
     * **goals** a set of goals to achieve
     *
     * ### Return
     * A `std::queue` of `Action*`s to perform in order to achieve the `goals` state
     */
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

    static bool buildGraph(Node& parent, std::vector<Node>& leaves,
                           const std::unordered_set<Action*>& actions,
                           const std::unordered_set<std::string>& goals);
    static bool containsAll(const std::unordered_set<std::string>& items,
                            const std::unordered_set<std::string>& state);
};

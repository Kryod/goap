#pragma once

#include <memory>
#include <queue>
#include <unordered_set>

#include "action.h"
#include "agent.h"

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
     * A `std::queue` of `Action*`s to perform in order to achieve the `goals`
     * state
     */
    static std::queue<Action*>
    plan(Agent* agent, std::unordered_set<Action*> actions,
         const std::unordered_set<std::string>& state,
         const std::unordered_set<std::string>& goals);

private:
    class Node {
    public:
        Node(std::shared_ptr<Node> parent, float totalCost,
             const std::unordered_set<std::string>& state, Action* action);

        std::shared_ptr<Node> parent;
        float totalCost;
        std::unordered_set<std::string> state;
        Action* action;
    };

    /**
     * ### Brief
     * Recursively builds a graph with possible paths to fulfill the `goals`
     *
     * ### Param
     * **parent** the graph's root
     * **leaves** a vector of leaves that will be populated
     * **actions** a set of usable actions
     * **goals** a set of goals to achieve
     *
     * ### Return
     * True if at least one solution was found
     */
    static bool buildGraph(std::shared_ptr<Node> parent,
                           std::vector<std::shared_ptr<Node>>& leaves,
                           const std::unordered_set<Action*>& actions,
                           const std::unordered_set<std::string>& goals);
    /**
     * ### Brief
     * Checks if all items from `items` are contained in the `state`
     * 
     * ### Param
     * **items** a set of items
     * **state** a set of states
     *
     * ### Return
     * True if `state` contains all items from `items`
     */
    static bool containsAll(const std::unordered_set<std::string>& items,
                            const std::unordered_set<std::string>& state);
};

#pragma once

#include <unordered_set>

/**
 * Representation of an action,
 * can possess conditions to be able to run,
 * and effects can be received from exec
 */
class Action {
public:
    /**
     * ### Brief
     * Instanciate an Action
     *
     * ### Param
     * **cost** The cost of the action
     *
     * ### Return
     * An instance of Action
     */
    Action(const float cost);

    /**
     * ### Brief
     * Get the cost of an action
     *
     * ### Return
     * The cost of the action
     */
    float getCost() const;

    /**
     * ### Brief
     * Set the cost of an action
     *
     * ### Param
     * **cost** The new cost of the action
     */
    void setCost(const float cost);

    /**
     * ### Brief
     * Adds a condition to preventing the completion of the action if not
     * fulfilled
     *
     * ### Param
     * **precondition** The condition that is required
     */
    void addPrecondition(const std::string& precondition);

    /**
     * ### Brief
     * Remove a condition on the action
     *
     * ### Param
     * **precondition** The condition that will be removed
     */
    void removePrecondition(const std::string& precondition);

    /**
     * ### Brief
     * Verify the presence of a condition on the action
     *
     * ### Param
     * **precondition** The name of the condition to check
     *
     * ### Return
     * True if the condition is on the action, False otherwise
     */
    bool hasPrecondition(const std::string& precondition) const;

    /**
     * ### Brief
     * Get the set of preconditions required to perform the action
     *
     * ### Return
     * A reference to the `std::unordered_set` of the action's preconditions
     */
    const std::unordered_set<std::string>& getPreconditions() const;

    /**
     * ### Brief
     * Adds an effect being the result of completing the action
     *
     * ### Param
     * **effect** The effect that will be granted
     */
    void addEffect(const std::string& effect);

    /**
     * ### Brief
     * Remove an effect of the action
     *
     * ### Param
     * **effect** The effect that will be removed
     */
    void removeEffect(const std::string& effect);

    /**
     * ### Brief
     * Verify the presence of an effect on the action
     *
     * ### Param
     * **precondition** The name of the effect to check
     *
     * ### Return
     * True if the effect is on the action, False otherwise
     */
    bool hasEffect(const std::string& effect) const;

    /**
     * ### Brief
     * Get the set of effects resulting from the action
     *
     * ### Return
     * A reference to the `std::unordered_set` of the action's effects
     */
    const std::unordered_set<std::string>& getEffects() const;

private:
    // List of conditions on the Action
    std::unordered_set<std::string> preconditions;

    // List of effects that will be active once the Action is done
    std::unordered_set<std::string> effects;

    float cost; // The cost of the action
};

#include <SFML/Window.hpp>
#include <iostream>

#include "actions.h"
#include "json_parser.h"
#include "planner.h"
#include "world.h"

void cleanActions(std::unordered_set<Action*> actions) {
    for (Action* action : actions) {
        delete action;
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Goal Oriented Action Planning");
    sf::View view(sf::FloatRect(0.0f, 0.0f, window.getSize().x, window.getSize().y));
    window.setView(view);
    window.setVerticalSyncEnabled(true);
    sf::Vector2i lastMousePos;
    const float zoomFactor = 1.25f;

    JsonParser j;

    j.loadFile("conf.json");
    j.loadWorld();

    World* world = World::instance;

    std::unordered_set<Action*> actions = j.loadActions();
    std::unordered_set<std::string> state { "has_tool",
                                            "chopping_block_available",
                                            "tree_available" };
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

    sf::Event event;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition();
            sf::Vector2i deltaMousePos = lastMousePos - mousePos;

            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape ||
                    event.key.code == sf::Keyboard::Q) {
                    window.close();
                }
            }
            if (event.type == sf::Event::MouseMoved) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
                    view.move(deltaMousePos.x, deltaMousePos.y);
                    window.setView(view);
                }
            }
            if (event.type == sf::Event::MouseWheelScrolled) {
                view.zoom(event.mouseWheelScroll.delta < 0.0f ? zoomFactor : 1.0f / zoomFactor);
                window.setView(view);
            }

            lastMousePos = mousePos;
        }

        window.clear(sf::Color(32, 32, 32));

        world->getMap().draw(window);

        window.display();
    }

    cleanActions(actions);
    delete world;
    World::instance = nullptr;
    return 0;
}

#include <SFML/Window.hpp>
#include <iostream>

#include "actions.h"
#include "agent.h"
#include "json_parser.h"
#include "planner.h"
#include "ui.h"
#include "world.h"

void cleanActions(std::unordered_set<Action*> actions) {
    for (Action* action : actions) {
        delete action;
    }
}

int main() {
    // SFML stuff
    sf::RenderWindow window(sf::VideoMode(800, 600),
                            "Goal Oriented Action Planning");
    sf::View view(
        sf::FloatRect(0.0f, 0.0f, window.getSize().x, window.getSize().y));
    window.setView(view);
    window.setVerticalSyncEnabled(true);
    sf::View uiView(
        sf::FloatRect(0.0f, 0.0f, window.getSize().x, window.getSize().y));
    sf::Vector2i lastMousePos;
    const float ZOOM_STEP = 1.25f;
    float zoomFactor = 1.0f;

    // JSON parsing
    JsonParser j;
    j.loadFile("conf.json");
    j.loadWorld();

    // Game initialisation
    World* world = World::instance;
    std::unordered_set<Action*> actions = j.loadActions();
    std::unordered_set<std::string> state = world->getState();
    std::unordered_set<std::string> goals { "has_firewood" };
    Agent agent(8.5f * Map::TILE_SIZE, 7.5f * Map::TILE_SIZE);
    agent.goal = { "has_firewood" };
    agent.availableActions = actions;
    Ui ui;

    for (auto &s : state) {
        std::cout << "- " << s << std::endl;
    }

    std::queue<Action*> plan = Planner::plan(&agent, actions, state, goals);

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

    // Game loop
    sf::Event event;
    sf::Clock clock;
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
                    sf::Vector2f delta =
                        static_cast<sf::Vector2f>(deltaMousePos);
                    delta *= zoomFactor; // pan faster/slower according to zoom
                    view.move(delta);
                }
            }

            if (event.type == sf::Event::MouseWheelScrolled) {
                if ((event.mouseWheelScroll.delta < 0.0f && // scroll down
                     zoomFactor < 4.0f) || // can still zoom out
                    (event.mouseWheelScroll.delta > 0.0f && // scroll up
                     zoomFactor > 0.35f)) {                 // can still zoom in
                    float delta = event.mouseWheelScroll.delta < 0.0f
                                      ? ZOOM_STEP
                                      : 1.0f / ZOOM_STEP;
                    zoomFactor *= delta;
                    view.zoom(delta);
                }
            }

            lastMousePos = mousePos;
        }

        float dt = clock.getElapsedTime().asSeconds();

        agent.update(dt);

        window.clear(sf::Color(32, 32, 32));

        window.setView(view);
        world->draw(window);
        agent.draw(window);

        window.setView(uiView);
        ui.draw(window, uiView);

        window.display();
    }

    cleanActions(actions);
    delete world;
    World::instance = nullptr;
    return 0;
}

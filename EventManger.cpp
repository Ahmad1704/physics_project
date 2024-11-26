#include "EventManger.h"


EventManger::EventManger(sf::RenderWindow& window, sf::View& view, float& zoomLevel, bool& isRunning, SolarSystem& solarSystem, sf::Font& font)
        : window(window), view(view), zoomLevel(zoomLevel), isRunning(isRunning), solarSystem(solarSystem), font(font) {}

    void EventManger::handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                handleKeyboardEvent(event.key.code);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                handleMouseClick();
            }

            if (event.type == sf::Event::MouseWheelScrolled) {
                handleMouseScroll(event.mouseWheelScroll.delta);
            }
        }
    }

    void EventManger::handleKeyboardEvent(sf::Keyboard::Key key) {
        if (key == sf::Keyboard::Enter) {
            isRunning = true;
        }
        else if (key == sf::Keyboard::P) {
            isRunning = false;
        }
        else if (key == sf::Keyboard::R) {
            resetView();
        }
    }

    void EventManger::handleMouseClick() {
        sf::Vector2i mouseScreenPosition = sf::Mouse::getPosition(window);
        sf::Vector2f mouseWorldPosition = window.mapPixelToCoords(mouseScreenPosition, view);
        sf::Vector2i intVector(static_cast<int>(mouseWorldPosition.x), static_cast<int>(mouseWorldPosition.y));
        b2Vec2 planetPosition = Convert::pixelsToMeters(intVector);
        solarSystem.createPlanet(planetPosition);
    }

    void EventManger::handleMouseScroll(float delta) {
        if (delta > 0) {
            zoomLevel *= 0.9f;
            view.zoom(0.9f);
            Renderer::stars.clear();
        }
        else if (delta < 0) {
            zoomLevel *= 1.1f;
            view.zoom(1.1f);
            Renderer::stars.clear();
        }
    }

    void EventManger::resetView() {
        view = sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
        zoomLevel = 1.0f;
        Renderer::stars.clear();
    }

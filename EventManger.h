#pragma once
#include<SFML/Graphics.hpp>
#include"SolarSystem.h"
#include"Renderer.h"
class EventManger
{
private:
    sf::RenderWindow& window;
    sf::View& view;
    float& zoomLevel;
    bool& isRunning;
    SolarSystem& solarSystem;
    sf::Font& font;

public:


    EventManger(sf::RenderWindow& window, sf::View& view, float& zoomLevel, bool& isRunning, SolarSystem& solarSystem, sf::Font& font);
    void handleEvents();

    void handleKeyboardEvent(sf::Keyboard::Key key);

    void handleMouseClick();

    void handleMouseScroll(float delta);

    void resetView();

};


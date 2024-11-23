#pragma once
#include<iostream>
#include<box2d/box2d.h>
#include<SFML/Graphics.hpp>
#include<vector>
#include"Sun.h"
#include"Planet.h"

class Renderer : Convert {

public:
    static float randomFloat(float min, float max);
    
    static sf::Vector2f randomVector2f(float minX, float maxX, float minY, float maxY);
    
    static std::vector<sf::CircleShape> stars;

    static std::vector<sf::CircleShape> generateStarryBackground(int numberOfStars, sf::Vector2u windowSize);
    
    static void drawstars(sf::RenderWindow& window, sf::View view);

    static void drawSun(sf::RenderWindow& window, Sun& sun);

    static void drawPlanet(sf::RenderWindow& window, Planet& planet);

    static void drawTrail(sf::RenderWindow& window, const Planet& planet); 
};







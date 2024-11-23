#pragma once
#include<box2d/box2d.h>
#include<SFML/Graphics.hpp>
#include<vector>
#include "Convert.h"

#define PI 3.14159265358979323846f

class Planet :Convert {
public:
    b2Body* body;
    float radius;
    float mass;
    std::vector<sf::Vector2f> trail;

    std::vector<std::pair<sf::Vector2f, float>> craters;

    sf::Color color = sf::Color(rand() * 255, rand() * 255, rand() * 255);

    Planet(b2World& world, float x, float y, float radius, float mass, float initialVelocityX, float initialVelocityY);
        

    sf::Vector2f getPosition();
    void generateCraters();


    void applyGravitationalForce(const b2Vec2& force); 

    void updateTrail(); 
};


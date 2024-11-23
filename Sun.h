#pragma once
#include"Convert.h"
#include<box2d/box2d.h>

class Sun :Convert{
public:
    b2Body* body;
    float radius;
    float mass;

    Sun(b2World& world, float x, float y, float radius, float mass);
        

    sf::Vector2f getPosition(); 
};

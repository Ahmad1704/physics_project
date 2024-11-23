#pragma once
#include<iostream>
#include<box2d/box2d.h>
#include<SFML/Graphics.hpp>
#include<vector>
#include"Sun.h"
#include"Planet.h"

class SolarSystem {
private:
    b2World& world;
    Sun* sun;
    std::vector<Planet*> planets;

public:

    SolarSystem(b2World& world);

    void createSun(float x, float y, float radius, float mass);

    Sun* getSun() const;
        

    void calculateSunGravity(); 

    void calculatePlanetGravity(); 

    void Update(float timeStep); 

    void createPlanet(b2Vec2 position); 

    std::vector<Planet*>& getPlanets(); 
  

    void removePlanet(Planet* planet); 

    ~SolarSystem(); 
};

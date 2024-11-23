#pragma once
#include<box2d/box2d.h>
#include "SolarSystem.h"
#include"Sun.h"

class CollisionListener : public b2ContactListener {
private:
    SolarSystem& solarSystem;
    Sun& sun;

public:
    CollisionListener(SolarSystem& solarSystem, Sun& sun);
        

        void BeginContact(b2Contact* contact) override; 
};
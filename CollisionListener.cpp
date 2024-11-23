#include "CollisionListener.h"

CollisionListener::CollisionListener(SolarSystem& solarSystem, Sun& sun)
	: solarSystem(solarSystem), sun(sun) {}

void CollisionListener::BeginContact(b2Contact* contact)
{
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();

    Sun* sunPtr = nullptr;
    Planet* planetPtr = nullptr;

    if (bodyA->GetUserData().pointer == reinterpret_cast<uintptr_t>(&sun)) {
        sunPtr = &sun;
        planetPtr = reinterpret_cast<Planet*>(bodyB->GetUserData().pointer);
    }
    else if (bodyB->GetUserData().pointer == reinterpret_cast<uintptr_t>(&sun)) {
        sunPtr = &sun;
        planetPtr = reinterpret_cast<Planet*>(bodyA->GetUserData().pointer);
    }

    if (sunPtr && planetPtr) {
        std::cout << "Planet collided with the Sun! Destroying the planet." << std::endl;
        solarSystem.removePlanet(planetPtr);
    }
}

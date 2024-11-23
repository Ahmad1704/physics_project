#include "SolarSystem.h"

SolarSystem::SolarSystem(b2World& world)
     : world(world), sun(nullptr) {}


void SolarSystem::createSun(float x, float y, float radius, float mass) {
    if (sun) {
        std::cout << "Sun already exists!" << std::endl;
        return;
    }
    sun = new Sun(world, x, y, radius, mass);
}

Sun* SolarSystem::getSun() const { return sun; }


void SolarSystem::calculateSunGravity()
{
    const float G = 5.0f;


    for (Planet* planet : planets) {
        if (planet == nullptr) continue;

        b2Vec2 distanceVec = sun->body->GetPosition() - planet->body->GetPosition();
        float distance = distanceVec.Length();

        if (distance == 0) continue;


        float forceMagnitude = (G * sun->mass * planet->mass) / (distance * distance);
        b2Vec2 forceVec = forceMagnitude * b2Vec2(distanceVec.x / distance, distanceVec.y / distance);


        planet->applyGravitationalForce(forceVec);
    }
}

void SolarSystem::calculatePlanetGravity()
{
    const float G = 1.0f;

    for (size_t i = 0; i < planets.size(); ++i) {
        for (size_t j = i + 1; j < planets.size(); ++j) {
            Planet* planetA = planets[i];
            Planet* planetB = planets[j];

            b2Vec2 distanceVec = planetB->body->GetPosition() - planetA->body->GetPosition();
            float distance = distanceVec.Length();

            if (distance == 0) continue;

            float forceMagnitude = (G * planetA->mass * planetB->mass) / (distance * distance);
            b2Vec2 forceVec = forceMagnitude * b2Vec2(distanceVec.x / distance, distanceVec.y / distance);


            planetA->applyGravitationalForce(forceVec);
            planetB->applyGravitationalForce(-forceVec);
        }
    }
}

void SolarSystem::Update(float timeStep)
{
    calculateSunGravity();
    calculatePlanetGravity();
    world.Step(timeStep, 8, 3);

    for (Planet* planet : planets) {
        planet->updateTrail();
    }
}

void SolarSystem::createPlanet(b2Vec2 position)
{
    const float G = 0.01f;
    float minDistance = 15.0f;
    for (Planet* planet : planets) {
        b2Vec2 planetPosition = planet->body->GetPosition();
        float distance = (planetPosition - position).Length();
        if (distance < minDistance) {
            std::cout << "Planet too close to another planet, skipping creation." << std::endl;
            return;
        }
    }

    b2Vec2 distanceVec = position - sun->body->GetPosition();
    float distance = distanceVec.Length();
    float velocityMagnitude = std::sqrt(G * sun->mass / distance) * 2.0f;

    b2Vec2 tangentialVelocity(-distanceVec.y, distanceVec.x);
    tangentialVelocity.Normalize();
    tangentialVelocity *= velocityMagnitude;

    Planet* newPlanet = new Planet(world, position.x, position.y, 5.0f, 1.0f, tangentialVelocity.x, tangentialVelocity.y);
    newPlanet->generateCraters();

    planets.push_back(newPlanet);
}

std::vector<Planet*>& SolarSystem::getPlanets()
{
    return planets;
}

void SolarSystem::removePlanet(Planet* planet)
{
    auto it = std::find(planets.begin(), planets.end(), planet);
    if (it != planets.end()) {
        delete* it;
        planets.erase(it);
    }
}

SolarSystem::~SolarSystem()
{
    if (sun) {
        delete sun;
    }
    for (Planet* planet : planets) {
        delete planet;
    }
}


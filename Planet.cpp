#include "Planet.h"

Planet::Planet(b2World& world, float x, float y, float radius, float mass, float initialVelocityX, float initialVelocityY)
    : radius(radius), mass(mass) {
    b2BodyDef bodyDef;
    bodyDef.position.Set(x, y);
    bodyDef.type = b2_dynamicBody;
    body = world.CreateBody(&bodyDef);

    b2CircleShape shape;
    shape.m_radius = radius;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    body->CreateFixture(&fixtureDef);

    body->SetLinearVelocity(b2Vec2(initialVelocityX, initialVelocityY));

    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
}

sf::Vector2f Planet::getPosition() 
{
    return metersToPixels(body->GetPosition());
}

void Planet::generateCraters() {
    craters.clear();  // Clear any previous craters
    for (int i = 0; i < 10; ++i) { // Generate 5 craters (can adjust number)
        float craterRadius = rand() % 2 ; // Random crater size
        float angle = rand() % 360;
        float distanceFromCenter = rand() % static_cast<int>(radius * PIXELS_PER_METER - 2 * craterRadius);
        sf::Vector2f craterPosition(
            cos(angle * PI / 180) * distanceFromCenter,  
            sin(angle * PI / 180) * distanceFromCenter
        );
            craters.push_back({ craterPosition, craterRadius });
    }
}


void Planet::applyGravitationalForce(const b2Vec2& force)
{
    body->ApplyForceToCenter(force, true);
}

void Planet::updateTrail()
{
    trail.push_back(getPosition());
    if (trail.size() > 1500) {
        trail.erase(trail.begin());
    }
}

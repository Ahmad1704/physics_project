#include "Sun.h"

Sun::Sun(b2World& world, float x, float y, float radius, float mass)
    : radius(radius), mass(mass) 
{
    b2BodyDef bodyDef;
    bodyDef.position.Set(x, y);
    bodyDef.type = b2_staticBody;
    body = world.CreateBody(&bodyDef);

    b2CircleShape shape;
    shape.m_radius = radius;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    body->CreateFixture(&fixtureDef);

    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
}

sf::Vector2f Sun::getPosition()
{
    return metersToPixels(body->GetPosition());
}

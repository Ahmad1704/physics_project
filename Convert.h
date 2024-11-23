#pragma once
#include<box2d/box2d.h>
#include<SFML/Graphics.hpp>
class Convert
{
public:
    static float PIXELS_PER_METER ;
    static sf::Vector2f metersToPixels(const b2Vec2& meters);
    static b2Vec2 pixelsToMeters(const sf::Vector2i& pixelPos);
};


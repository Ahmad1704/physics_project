#include "Renderer.h"
std::vector<sf::CircleShape> Renderer::stars;

sf::Vector2u operator * (const sf::Vector2u& lhs, const sf::Vector2u& rhs) {
    return sf::Vector2u(lhs.x * rhs.x, lhs.y * rhs.y);
}

float Renderer::randomFloat(float min, float max) {
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

// Function to generate a random sf::Vector2f with negative values
sf::Vector2f Renderer::randomVector2f(float minX, float maxX, float minY, float maxY) {
    float x = randomFloat(minX, maxX);
    float y = randomFloat(minY, maxY);
    return sf::Vector2f(x, y);
}


std::vector<sf::CircleShape> Renderer::generateStarryBackground(int numberOfStars, sf::Vector2u windowSize)
{

    if (stars.empty()) {
        for (int i = 0; i < numberOfStars; ++i) {
            sf::CircleShape star(1.0f);
            star.setPosition(randomVector2f(0, windowSize.x,0, windowSize.y));
            star.setFillColor(sf::Color::White);
            stars.push_back(star);
        }
    }
    return stars;
}

void Renderer::drawstars(sf::RenderWindow& window , sf::View view) 
{
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f currentViewSize = view.getSize();
    sf::Vector2u temp(static_cast<unsigned int > (view.getSize().x)/ (window.getSize().x/2),
                      static_cast<unsigned int> (view.getSize().y) / (window.getSize().y/2));

    auto stars = generateStarryBackground(500,window.getSize()*temp);

    for (const auto& star : stars) {
        sf::Vector2f starPosition = star.getPosition();

        // Offset star positions to handle negative space (zoom or pan effect)
        sf::Vector2f offsetPosition = starPosition + (viewCenter - currentViewSize / 2.0f);


        sf::CircleShape starCopy = star;
        starCopy.setPosition(offsetPosition);
        window.draw(starCopy);
    }
}

void Renderer::drawSun(sf::RenderWindow& window, Sun& sun)
{
    
    sf::CircleShape sunGlow(sun.radius *PIXELS_PER_METER * 1.5f);  
    sunGlow.setFillColor(sf::Color(255, 255, 0, 50));  
    sunGlow.setOrigin(sunGlow.getRadius(), sunGlow.getRadius());
    sf::Vector2f position = sun.getPosition();
    sunGlow.setPosition(position);
    window.draw(sunGlow);

    
    sf::CircleShape sunShape(sun.radius * PIXELS_PER_METER);
    sunShape.setOrigin(sunShape.getRadius(), sunShape.getRadius());
    sunShape.setPosition(position);
    sunShape.setFillColor(sf::Color::Yellow);
    window.draw(sunShape);
}

void Renderer::drawPlanet(sf::RenderWindow& window,  Planet& planet) {
    // Create the main planet shape
    sf::CircleShape planetShape(planet.radius * PIXELS_PER_METER);
    planetShape.setOrigin(planetShape.getRadius(), planetShape.getRadius());
    planetShape.setPosition(planet.getPosition());

    // Color for the planet (a base color, you can customize it)
    planetShape.setFillColor(sf::Color(planet.color.r, planet.color.b, planet.color.g, 50));  // A blue-ish color for the planet

    // Draw the planet's surface (basic layer)
    window.draw(planetShape);

    // Create atmosphere (optional, if you want a glow effect around the planet)
    sf::CircleShape atmosphere(planet.radius * PIXELS_PER_METER * 1.1f); // Slightly larger
    atmosphere.setOrigin(atmosphere.getRadius(), atmosphere.getRadius());
    atmosphere.setPosition(planet.getPosition());
    atmosphere.setFillColor(sf::Color(planet.color.r, planet.color.b, planet.color.g, 80)); // Semi-transparent blue atmosphere
    window.draw(atmosphere);

    // Add craters or surface features
   
    for (const auto& crater : planet.craters) {
        sf::CircleShape craterShape(crater.second);
        craterShape.setFillColor(sf::Color(planet.color.r, planet.color.b, planet.color.g, 100));
        craterShape.setOutlineColor(sf::Color(sf::Color::Black));
        craterShape.setOutlineThickness(1);
        craterShape.setPosition(planet.getPosition() + crater.first); 
        window.draw(craterShape);
    }


   
    //Example: Adding rings around the planet
    sf::CircleShape ring(planet.radius * PIXELS_PER_METER * 1.1f); 
    ring.setOrigin(ring.getRadius(), ring.getRadius());
    ring.setPosition(planet.getPosition());
    ring.setFillColor(sf::Color(planet.color.r, planet.color.b, planet.color.g, 150)); 
    ring.setOutlineColor(sf::Color::Black);  
    ring.setOutlineThickness(2);  
    window.draw(ring);
}

void Renderer::drawTrail(sf::RenderWindow& window, const Planet& planet)
{

    if (planet.trail.size() > 10) {
        sf::VertexArray trail(sf::LinesStrip);

        // Start from the 10th point (index 10)
        for (size_t i = 10; i < planet.trail.size(); ++i) {
            trail.append(sf::Vertex(planet.trail[i], planet.color));
        }

        window.draw(trail);
    }
}


#include <iostream>
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "Sun.h"
#include "SolarSystem.h"
#include "Renderer.h"
#include "CollisionListener.h"
#include "Convert.h"

float WINDOW_WIDTH = 1200;
float WINDOW_HEIGHT = 800;
int main(){
sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Solar System Simulation");
window.setFramerateLimit(60);

b2Vec2 gravity(0.0f, 0.0f);
b2World world(gravity);

SolarSystem solarSystem(world);
float centerX = WINDOW_WIDTH / 8.0f;
float centerY = WINDOW_HEIGHT / 8.0f;

solarSystem.createSun(centerX, centerY, 10.0f, 500.0f);

CollisionListener collisionListener(solarSystem, *solarSystem.getSun());
world.SetContactListener(&collisionListener);

sf::View view(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
float zoomLevel = 1.0f;  

while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            b2Vec2 planetPosition = Convert::pixelsToMeters(mousePosition);
            solarSystem.createPlanet(planetPosition);
        }

        if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.delta > 0) {  
                zoomLevel *= 0.9f;
                view.zoom(0.9f);
                Renderer::stars.clear();
            }
            else if (event.mouseWheelScroll.delta < 0) {  
                zoomLevel *= 1.1f;
                view.zoom(1.1f);
                Renderer::stars.clear();
            }
        }

      
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
            view = sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
            zoomLevel = 1.0f;
            Renderer::stars.clear();
        }
    }

    solarSystem.Update(10.0f / 60.0f);

    window.clear(sf::Color::Black);

    window.setView(view);
    Renderer::drawstars(window,view);
    Renderer::drawSun(window,  *solarSystem.getSun());

    for (Planet* planet : solarSystem.getPlanets()) {
        Renderer::drawPlanet(window, *planet);
        Renderer::drawTrail(window, *planet);
    }

    window.display();
}

return 0;
}
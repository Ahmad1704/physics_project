#include <iostream>
#include <box2d/box2d.h>
#include <SFML/Graphics.hpp>
#include "Sun.h"
#include "SolarSystem.h"
#include "Renderer.h"
#include "CollisionListener.h"
#include "Convert.h"
#include "EventManger.h"
#include"AudioManager.h"


float WINDOW_WIDTH = 1200;
float WINDOW_HEIGHT = 800;
bool isRunning = true; 


int main(){
sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Solar System Simulation");
window.setFramerateLimit(60);

b2Vec2 gravity(0.0f, 0.0f);
b2World world(gravity);

SolarSystem solarSystem(world);

solarSystem.createSun(WINDOW_WIDTH /8.0f, WINDOW_HEIGHT / 8.0f, 10.0f, 500.0f);

CollisionListener collisionListener(solarSystem, *solarSystem.getSun());
world.SetContactListener(&collisionListener);

sf::View view(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));
float zoomLevel = 1.0f;  

sf::Font font;
if (!font.loadFromFile("Externel/arial.ttf")) { 
    std::cerr << "Error loading font!" << std::endl;
   return -1;
}
AudioManager audioManager;

EventManger EventManager(window,view,zoomLevel,isRunning, solarSystem, font);

while (window.isOpen()) {
    EventManager.handleEvents();

    audioManager.playBackgroundMusic();
    if (isRunning) {
        solarSystem.Update(10.0f / 60.0f);
    }  

    window.clear(sf::Color::Black);

    window.setView(view);
    Renderer::drawstars(window,view);
    Renderer::drawSun(window,  *solarSystem.getSun());

    for (Planet* planet : solarSystem.getPlanets()) {
        Renderer::drawPlanet(window, *planet);
        Renderer::drawTrail(window, *planet);
    }
    Renderer::displayInstructions(window, font,view,isRunning);
    window.display();
}
audioManager.stopBackgroundMusic();
return 0;
}
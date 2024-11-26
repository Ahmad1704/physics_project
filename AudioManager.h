#pragma once
#include<iostream>
#include<SFML/Audio.hpp>
class AudioManager
{
private:
   /* sf::SoundBuffer startBuffer, pauseBuffer, resetBuffer;
    sf::Sound startSound, pauseSound, resetSound;*/
    sf::Music backgroundMusic;

public:
    AudioManager();
    void playStartSound();
    void playPauseSound();
    void playResetSound();
    void playBackgroundMusic();
    void stopBackgroundMusic();

};


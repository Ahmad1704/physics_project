#include "AudioManager.h"

AudioManager::AudioManager() {
        /*if (!startBuffer.loadFromFile("start_simulation.wav") ||
            !pauseBuffer.loadFromFile("pause_simulation.wav") ||
            !resetBuffer.loadFromFile("reset_simulation.wav")) {
            std::cout << "Error loading sound files!" << std::endl;
        }*/

       /* startSound.setBuffer(startBuffer);
        pauseSound.setBuffer(pauseBuffer);
        resetSound.setBuffer(resetBuffer);*/

    if (!backgroundMusic.openFromFile("Externel/milky-way-ambient-space-music-1395.mp3")) {
        std::cerr << "Error loading background music!" << std::endl;
    }
    backgroundMusic.setLoop(true); // Loop the music continuously
}

    /*void AudioManager::playStartSound() { startSound.play(); }
    void AudioManager::playPauseSound() { pauseSound.play(); }
    void AudioManager::playResetSound() { resetSound.play(); }*/

void AudioManager::playBackgroundMusic() {
    if (backgroundMusic.getStatus() != sf::Music::Playing) {
        backgroundMusic.play();
    }
}
    void AudioManager::stopBackgroundMusic() { backgroundMusic.stop(); }



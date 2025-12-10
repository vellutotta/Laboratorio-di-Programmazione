#include "Timer.h"
#include <iostream>
#include <algorithm>
using namespace std;
using namespace sf;



Timer::Timer(float totalDuration)
    : progress(0), running(false), duration(totalDuration) {}

void Timer::addObserver(Observer* observer) {
    observers.push_back(observer);
}

void Timer::removeObserver(Observer* observer) {
    for (auto it = observers.begin(); it != observers.end(); it++) {
        if (*it == observer) {
            observers.erase(it);
            break;
        }
    }
}

void Timer::notify() {
    for (Observer* observer : observers) {
        observer->update(progress);
    }
}

void Timer::start() {
    if (running) return;

    running = true;
    progress = 0;

    workerThread = thread([this]() {
        auto startTime = chrono::steady_clock::now();  //salva l'ora d'inizio

        while (running && progress < 100.0f) {
            auto currentTime = chrono::steady_clock::now();
            auto elapsed = chrono::duration_cast<chrono::milliseconds>(currentTime - startTime);

            
            progress = (elapsed.count() / (duration * 1000.0f)) * 100.0f;
            if (progress > 100.0f) progress = 100.0f;

            notify();
            this_thread::sleep_for(chrono::milliseconds(16)); // ~60 FPS
        }

        // Se timer interrotto prima di 100 forza notifica
        if (progress < 100.0f) {
            progress = 100.0f;
            notify();
        }
    });
}

void Timer::stop() {
    running = false;                             //ciclo thread si interrompe
    if (workerThread.joinable()) {
        workerThread.join();                    //aspetta che thread finisce
    }
}

float Timer::getProgress() const {
    return progress;
}

Timer::~Timer() {
    stop();
}



SFMLProgressBar::SFMLProgressBar(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height), currentProgress(0) {

    background.setSize(Vector2f(width, height));
    background.setPosition(x, y);
    background.setFillColor(Color::Black);
    background.setOutlineThickness(2);
    background.setOutlineColor(Color::Blue);

    progressFill.setSize(Vector2f(0, height - 4));
    progressFill.setPosition(x + 2, y + 2);
    progressFill.setFillColor(Color::Cyan);
}

void SFMLProgressBar::update(float progress) {
    currentProgress = progress;
    float fillWidth = (progress / 100.0f) * (width - 4);
    progressFill.setSize(Vector2f(fillWidth, height - 4));
}

void SFMLProgressBar::draw(RenderWindow& window) {
    window.draw(background);
    window.draw(progressFill);
}


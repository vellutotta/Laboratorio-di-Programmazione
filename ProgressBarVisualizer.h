#pragma once

#include "Observer.h"
#include <SFML/Graphics.hpp>
#include <string>

class ProgressBarVisualizer : public IObserver {
private:
    sf::RenderWindow* window;
    sf::RectangleShape backgroundBar;
    sf::RectangleShape progressBar;
    sf::Font font;
    sf::Text statusText;
    sf::Text progressText;
    float currentProgress = 0.0f;
    std::string currentStatus = "";

    static const float BAR_WIDTH;
    static const float BAR_HEIGHT;
    static const float BAR_X;
    static const float BAR_Y;

public:
    ProgressBarVisualizer(sf::RenderWindow* renderWindow);
    ~ProgressBarVisualizer();

    // IObserver interface
    void update(float progress, const std::string& status) override;

    // Rendering methods
    void render();
    void setupUI();
};
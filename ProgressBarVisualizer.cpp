#include "ProgressBarVisualizer.h"
#include <iostream>
#include <sstream>
#include <iomanip>

// Static member definitions
const float ProgressBarVisualizer::BAR_WIDTH = 400.0f;
const float ProgressBarVisualizer::BAR_HEIGHT = 30.0f;
const float ProgressBarVisualizer::BAR_X = 100.0f;
const float ProgressBarVisualizer::BAR_Y = 200.0f;

ProgressBarVisualizer::ProgressBarVisualizer(sf::RenderWindow* renderWindow)
    : window(renderWindow) {
    setupUI();
}

ProgressBarVisualizer::~ProgressBarVisualizer() {
    // Destructor
}

void ProgressBarVisualizer::setupUI() {
    // Load default font (SFML's built-in font)
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        // If system font is not available, try to continue without it
        std::cout << "Warning: Could not load font, text may not display properly" << std::endl;
    }

    // Setup background bar
    backgroundBar.setSize(sf::Vector2f(BAR_WIDTH, BAR_HEIGHT));
    backgroundBar.setPosition(BAR_X, BAR_Y);
    backgroundBar.setFillColor(sf::Color(80, 80, 80));
    backgroundBar.setOutlineColor(sf::Color::White);
    backgroundBar.setOutlineThickness(2.0f);

    // Setup progress bar
    progressBar.setSize(sf::Vector2f(0.0f, BAR_HEIGHT));
    progressBar.setPosition(BAR_X, BAR_Y);
    progressBar.setFillColor(sf::Color::Green);

    // Setup status text
    statusText.setFont(font);
    statusText.setCharacterSize(16);
    statusText.setFillColor(sf::Color::White);
    statusText.setPosition(BAR_X, BAR_Y - 30);

    // Setup progress text
    progressText.setFont(font);
    progressText.setCharacterSize(20);
    progressText.setFillColor(sf::Color::White);
    progressText.setPosition(BAR_X + BAR_WIDTH/2 - 30, BAR_Y + 5);
}

void ProgressBarVisualizer::update(float progress, const std::string& status) {
    currentProgress = progress;
    currentStatus = status;

    // Update progress bar width
    float progressWidth = BAR_WIDTH * currentProgress;
    progressBar.setSize(sf::Vector2f(progressWidth, BAR_HEIGHT));

    // Update status text
    statusText.setString(currentStatus);

    // Update progress percentage text
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(1) << (currentProgress * 100.0f) << "%";
    progressText.setString(oss.str());

    std::cout << "Progress: " << (currentProgress * 100.0f) << "% - " << currentStatus << std::endl;
}

void ProgressBarVisualizer::render() {
    if (window) {
        window->draw(backgroundBar);
        window->draw(progressBar);
        window->draw(statusText);
        window->draw(progressText);
    }
}
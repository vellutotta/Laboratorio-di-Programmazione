#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include "ResourceLoader.h"
#include "ProgressBarVisualizer.h"

int main() {
    // Create SFML window
    sf::RenderWindow window(sf::VideoMode(600, 400), "Progress Bar Demo - Observer Pattern");
    window.setFramerateLimit(60);

    // Create resource loader and progress bar visualizer
    ResourceLoader loader;
    ProgressBarVisualizer visualizer(&window);

    // Attach visualizer as observer to the loader
    loader.attach(&visualizer);

    // Add some dummy resources to load
    loader.addResource("resource1.txt");
    loader.addResource("resource2.dat");
    loader.addResource("resource3.bin");
    loader.addResource("resource4.cfg");
    loader.addResource("resource5.xml");

    // Start loading in a separate thread
    std::thread loadingThread([&loader]() {
        loader.loadResources();
    });

    // Main application loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        // Clear window with dark background
        window.clear(sf::Color(30, 30, 30));

        // Render progress bar
        visualizer.render();

        // Display instructions
        sf::Font font;
        sf::Text instructionText;
        if (font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
            instructionText.setFont(font);
            instructionText.setCharacterSize(14);
            instructionText.setFillColor(sf::Color::Yellow);
            instructionText.setPosition(50, 50);
            instructionText.setString("Resource Loading Progress Demo\nPress ESC to exit\n\nObserver Pattern Implementation:\n- ResourceLoader notifies ProgressBarVisualizer\n- Real-time progress updates");
            window.draw(instructionText);
        }

        window.display();

        // Check if loading is complete and exit after a short delay
        if (!loader.getLoadingStatus() && loadingThread.joinable()) {
            // Wait a bit to show 100% completion
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            break;
        }
    }

    // Clean up
    if (loadingThread.joinable()) {
        loadingThread.join();
    }

    std::cout << "Application finished." << std::endl;
    return 0;
}
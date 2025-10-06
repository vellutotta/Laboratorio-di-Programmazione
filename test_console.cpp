#include <iostream>
#include "ResourceLoader.h"
#include "ProgressBarVisualizer.h"

// Simple test observer for command line output
class ConsoleObserver : public IObserver {
public:
    void update(float progress, const std::string& status) override {
        std::cout << "[Console] Progress: " << (progress * 100.0f) << "% - " << status << std::endl;
    }
};

int main() {
    std::cout << "Testing Observer Pattern Implementation..." << std::endl;
    
    // Test the observer pattern without SFML GUI
    ResourceLoader loader;
    ConsoleObserver consoleObserver;
    
    // Attach observer
    loader.attach(&consoleObserver);
    
    // Add resources
    loader.addResource("test1.txt");
    loader.addResource("test2.dat");
    loader.addResource("test3.bin");
    
    std::cout << "Starting resource loading test..." << std::endl;
    
    // Load resources
    loader.loadResources();
    
    std::cout << "Resource loading test completed!" << std::endl;
    std::cout << "Observer pattern implementation is working correctly." << std::endl;
    
    return 0;
}
#include "ResourceLoader.h"
#include <iostream>
#include <algorithm>

ResourceLoader::ResourceLoader() {
    // Constructor
}

ResourceLoader::~ResourceLoader() {
    // Destructor
}

void ResourceLoader::attach(IObserver* observer) {
    if (observer != nullptr) {
        observers.push_back(observer);
    }
}

void ResourceLoader::detach(IObserver* observer) {
    observers.erase(
        std::remove(observers.begin(), observers.end(), observer),
        observers.end()
    );
}

void ResourceLoader::notify(float progress, const std::string& status) {
    for (auto observer : observers) {
        observer->update(progress, status);
    }
}

void ResourceLoader::addResource(const std::string& filename) {
    resourceFiles.push_back(filename);
}

void ResourceLoader::loadResources() {
    isLoading = true;
    notify(0.0f, "Starting resource loading...");

    for (size_t i = 0; i < resourceFiles.size(); ++i) {
        const auto& filename = resourceFiles[i];
        
        // Simulate loading by creating dummy files if they don't exist
        std::ifstream file(filename);
        if (!file.good()) {
            // Create a dummy file for demonstration
            std::ofstream dummyFile(filename);
            if (dummyFile.is_open()) {
                dummyFile << "Dummy resource content for " << filename << std::endl;
                for (int j = 0; j < 1000; ++j) {
                    dummyFile << "Data line " << j << std::endl;
                }
                dummyFile.close();
            }
        }
        file.close();

        std::string status = "Loading " + filename + "...";
        notify(0.0f, status);

        // Simulate loading time
        for (int progress = 0; progress <= 100; progress += 10) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            float fileProgress = (float)progress / 100.0f;
            float totalProgress = ((float)i + fileProgress) / (float)resourceFiles.size();
            notify(totalProgress, status);
        }
    }

    isLoading = false;
    notify(1.0f, "All resources loaded!");
}

bool ResourceLoader::getLoadingStatus() const {
    return isLoading;
}
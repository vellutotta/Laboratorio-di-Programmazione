#pragma once

#include "Observer.h"
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>

class ResourceLoader : public ISubject {
private:
    std::vector<IObserver*> observers;
    std::vector<std::string> resourceFiles;
    bool isLoading = false;

public:
    ResourceLoader();
    ~ResourceLoader();

    // ISubject interface
    void attach(IObserver* observer) override;
    void detach(IObserver* observer) override;
    void notify(float progress, const std::string& status) override;

    // Resource loading methods
    void addResource(const std::string& filename);
    void loadResources();
    bool getLoadingStatus() const;
};
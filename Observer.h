#pragma once
#include <string>

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void update(float progress, const std::string& status) = 0;
};

class ISubject {
public:
    virtual ~ISubject() = default;
    virtual void attach(IObserver* observer) = 0;
    virtual void detach(IObserver* observer) = 0;
    virtual void notify(float progress, const std::string& status) = 0;
};
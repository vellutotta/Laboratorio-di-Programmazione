
#ifndef TIMER_HPP
#define TIMER_HPP

#include <SFML/Graphics.hpp>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;
using namespace sf;

class Observer;


class Subject {
public:
    virtual void addObserver(Observer* observer) = 0;
    virtual void removeObserver(Observer* observer) = 0;
    virtual void notify() = 0;
    virtual ~Subject() {}
};


class Observer {
public:
    virtual void update(float progress) = 0;
    virtual void draw(RenderWindow& window) = 0;
    virtual ~Observer() {}
};


class Timer : public Subject {
private:
    vector<Observer*> observers;
    float progress;
    bool running;
    float duration;
    thread workerThread;

public:
    explicit Timer(float totalDuration);

    void addObserver(Observer* observer) override;
    void removeObserver(Observer* observer) override;
    void notify() override;

    void start();
    void stop();

    float getProgress() const;

    ~Timer();
};


class SFMLProgressBar : public Observer {
private:
    RectangleShape background;
    RectangleShape progressFill;
    float x, y, width, height;
    float currentProgress;

public:
    SFMLProgressBar(float x, float y, float width, float height);

    void update(float progress) override;
    void draw(RenderWindow& window) override;
};

#endif // TIMER_HPP

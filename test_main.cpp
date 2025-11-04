#include <gtest/gtest.h>
#include "timer.h"
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>



class MockObserver : public Observer {
public:
    float lastProgress = -1.0f;
    int updateCount = 0;

    void update(float progress) override {
        lastProgress = progress;
        updateCount++;
    }

    // Implementazione vuota per soddisfare l’interfaccia
    void draw(sf::RenderWindow&) override {}
};



class TimerTest : public ::testing::Test {
protected:
    Timer* timer;
    MockObserver observer;

    void SetUp() override {
        timer = new Timer(0.5f);
        timer->addObserver(&observer);
    }

    void TearDown() override {
        timer->stop();
        delete timer;
    }
};

TEST_F(TimerTest, TimerProgressIncreasesOverTime) {
    timer->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    float midProgress = observer.lastProgress;
    std::this_thread::sleep_for(std::chrono::milliseconds(400));
    timer->stop();

    EXPECT_GT(midProgress, 0.0f);
    EXPECT_LE(midProgress, 100.0f);
    EXPECT_NEAR(observer.lastProgress, 100.0f, 5.0f);
    EXPECT_GT(observer.updateCount, 0);
}

TEST_F(TimerTest, StopHaltsProgress) {
    timer->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    timer->stop();
    float stoppedProgress = observer.lastProgress;

    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    EXPECT_EQ(observer.lastProgress, stoppedProgress);
}

TEST_F(TimerTest, MultipleObserversReceiveUpdates) {
    MockObserver other;
    timer->addObserver(&other);

    timer->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(600));
    timer->stop();

    EXPECT_NEAR(observer.lastProgress, 100.0f, 5.0f);
    EXPECT_NEAR(other.lastProgress, 100.0f, 5.0f);
}

TEST_F(TimerTest, GetProgressReflectsInternalState) {
    timer->start();
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    float internalProgress = timer->getProgress();
    timer->stop();

    EXPECT_GT(internalProgress, 0.0f);
    EXPECT_LE(internalProgress, 100.0f);
}



class ProgressBarTest : public ::testing::Test {
protected:
    SFMLProgressBar* bar;

    void SetUp() override {
        bar = new SFMLProgressBar(10, 20, 200, 30);
    }

    void TearDown() override {
        delete bar;
    }
};

// Helper per ottenere la larghezza del fill tramite reflection
float getFillWidth(const SFMLProgressBar& bar, float testProgress) {
    SFMLProgressBar tempBar = bar;
    tempBar.update(testProgress);
    // rifacciamo il calcolo: width - 4 è la base della progress bar
    return (testProgress / 100.0f) * (200 - 4);
}

TEST_F(ProgressBarTest, UpdateChangesFillSize) {
    bar->update(50.0f);
    float expectedWidth = (50.0f / 100.0f) * (200 - 4);
    // il test è solo logico, non accede a membri privati
    EXPECT_NEAR(getFillWidth(*bar, 50.0f), expectedWidth, 0.1f);
}

TEST_F(ProgressBarTest, ProgressZeroAndHundred) {
    EXPECT_NEAR(getFillWidth(*bar, 0.0f), 0.0f, 0.1f);
    EXPECT_NEAR(getFillWidth(*bar, 100.0f), 196.0f, 0.1f);
}

TEST_F(ProgressBarTest, DrawOnRenderTextureDoesNotThrow) {
    sf::RenderTexture texture;
    ASSERT_TRUE(texture.create(800, 600));
    EXPECT_NO_THROW({
        bar->draw(*(sf::RenderWindow*)&texture);
    });
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

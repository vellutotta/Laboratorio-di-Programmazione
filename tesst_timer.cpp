#include <gtest/gtest.h>
#include "timer.h"
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>





TEST(SFMLProgressBarTest, UpdateFunction) {
    SFMLProgressBar bar(0, 0, 200, 20);

    bar.update(50.0f);

    
    EXPECT_FLOAT_EQ(bar.currentProgress, 50.0f);

    
    float expectedWidth = 0.5f * (200 - 4);
    float actualWidth = bar.progressFill.getSize().x;

    EXPECT_NEAR(actualWidth, expectedWidth, 0.01f)
        << "La progress bar deve calcolare correttamente la nuova larghezza del fill.";
}



TEST(TimerTest, StopFunction) {
    Timer timer(0.2f);   // durata 200 ms

    timer.start();

    std::this_thread::sleep_for(std::chrono::milliseconds(80));

    timer.stop();

   
    EXPECT_GE(timer.getProgress(), 100.0f)
        << "Timer::stop() deve forzare progress a 100 se fermato prima del termine.";

    // Deve essere possibile richiamare stop() senza crash
    EXPECT_NO_THROW(timer.stop());
}


#include <gtest/gtest.h>
#include "timer.h"
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

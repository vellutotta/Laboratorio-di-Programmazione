cmake_minimum_required(VERSION 3.20)
project(untitled)

set(CMAKE_CXX_STANDARD 17)


set(SFML_DIR "C:/Users/carlo/CLionProjects/untitled/SFML-2.6.1/lib/cmake/SFML")


find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system)


add_executable(untitled main.cpp
        timer.cpp
        timer.h)


target_link_libraries(untitled
        sfml-graphics
        sfml-window
        sfml-system
)


target_include_directories(untitled PRIVATE "C:/Users/carlo/CLionProjects/untitled/SFML-2.6.1/include")


add_custom_command(TARGET untitled POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<$<CONFIG:Debug>:C:/Users/carlo/CLionProjects/untitled/SFML-2.6.1/bin/sfml-graphics-d-2.dll>$<$<CONFIG:Release>:C:/Users/carlo/CLionProjects/untitled/SFML-2.6.1/bin/sfml-graphics-2.dll>"
        $<TARGET_FILE_DIR:untitled>

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<$<CONFIG:Debug>:C:/Users/carlo/CLionProjects/untitled/SFML-2.6.1/bin/sfml-window-d-2.dll>$<$<CONFIG:Release>:C:/Users/carlo/CLionProjects/untitled/SFML-2.6.1/bin/sfml-window-2.dll>"
        $<TARGET_FILE_DIR:untitled>

        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<$<CONFIG:Debug>:C:/Users/carlo/CLionProjects/untitled/SFML-2.6.1/bin/sfml-system-d-2.dll>$<$<CONFIG:Release>:C:/Users/carlo/CLionProjects/untitled/SFML-2.6.1/bin/sfml-system-2.dll>"
        $<TARGET_FILE_DIR:untitled>
)






#Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)


add_executable(runTests tests/test_main.cpp timer.cpp  tests/tesst_timer.cpp
        )
target_link_libraries(runTests
        gtest_main
        sfml-graphics
        sfml-window
        sfml-system
)

target_include_directories(runTests PRIVATE "C:/Users/carlo/CLionProjects/untitled/SFML-2.6.1/include")

target_include_directories(runTests PRIVATE ${PROJECT_SOURCE_DIR})






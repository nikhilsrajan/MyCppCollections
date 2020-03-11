cmake_minimum_required(VERSION 3.5)
project(MyCppCollection)

set(CMAKE_CXX_FLAGS -pthread)

# ---------- Stopwatch ----------

add_library(Stopwatch-static STATIC
    Stopwatch/Stopwatch.hpp
    Stopwatch/Stopwatch.cpp
)

add_executable(StopwatchTest
    Tests/StopwatchTest.cpp
)
target_link_libraries(StopwatchTest
    Stopwatch-static
)

# ---------- Announcer ----------

add_executable(AnnouncerTest
    Tests/AnnouncerTest.cpp
)
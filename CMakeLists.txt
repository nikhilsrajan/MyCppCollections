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

# ---------- IO_File ----------

add_library(IO_File-static STATIC
    IO_File/Attribute_Hierarchy_Manager.hpp
    IO_File/Attribute_Hierarchy_Manager.cpp
    IO_File/Attribute_Manager_Interface.hpp
    IO_File/Attribute_Manager.hpp
    IO_File/Attributes_Manager.hpp
    IO_File/Globals.hpp
    IO_File/IO_File.hpp
    IO_File/IO_File.cpp
    IO_File/IO_Node.hpp
    IO_File/IO_Node.cpp
)

add_executable(IO_FileTest
    Tests/IO_FileTest.cpp
)
target_link_libraries(IO_FileTest
    IO_File-static
)
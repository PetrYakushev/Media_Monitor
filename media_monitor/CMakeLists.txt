cmake_minimum_required(VERSION 3.16)

project(media_monitor VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -Werror
)

find_package(Threads REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(media_monitor
    src/main.cpp
    src/FileScanner.cpp
    src/JsonWriter.cpp
    src/HttpServer.cpp
    src/Scheduler.cpp
)

target_include_directories(media_monitor
    PRIVATE
        include
)

target_link_libraries(media_monitor
    PRIVATE
        Threads::Threads
        nlohmann_json::nlohmann_json
)

target_compile_definitions(media_monitor PRIVATE CPPHTTPLIB_HEADER_ONLY)
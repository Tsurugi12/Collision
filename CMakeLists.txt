cmake_minimum_required(VERSION 3.16)
project(collision)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(collision
    src/main.cpp
    src/boule.cpp
    src/rectangle.cpp
    src/commande.cpp
)


target_include_directories(collision PRIVATE include)
target_link_libraries(collision sfml-graphics sfml-window sfml-system)
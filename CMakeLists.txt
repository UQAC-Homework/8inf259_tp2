cmake_minimum_required(VERSION 4.1)
project(8inf259_tp2)

set(CMAKE_CXX_STANDARD 20)

add_executable(8inf259_tp2 main.cpp
        include/Ville.h
        include/Plateau.h
        source/Plateau.cpp
        source/Ville.cpp
        include/string_utils.h
        source/Map.cpp
        include/Map.h
        include/menu_utils.h
        source/Graphs/BaseGraph.cpp
        include/Graphs/BaseGraph.h
        source/Graphs/CityGraph.cpp
        include/Graphs/CityGraph.h)

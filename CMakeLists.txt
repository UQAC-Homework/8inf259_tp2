cmake_minimum_required(VERSION 4.1)
project(8inf259_tp2)

set(CMAKE_CXX_STANDARD 20)

add_executable(8inf259_tp2 main.cpp
        include/Ville.h
        include/Plateau.h
        source/Plateau.cpp
        source/Ville.cpp
        include/utils/string.h
        include/utils/menu.h
        source/CityGraph.cpp
        include/CityGraph.h
        include/utils/pathfinding.h
        include/ds/Graph.h
        source/ds/Graph.tpp
        include/utils/graph.h
        include/TransportMode.h
        source/TransportMode.cpp
        include/utils/cities.h
)

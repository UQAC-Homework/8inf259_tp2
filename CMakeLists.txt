cmake_minimum_required(VERSION 4.1)
project(8inf259_tp2)

set(CMAKE_CXX_STANDARD 20)

add_executable(8inf259_tp2 main.cpp
        include/Ville.h
        include/Plateau.h
        source/Plateau.cpp
        source/Ville.cpp
        include/utils/string.h
        source/ds/Map.tpp
        include/ds/Map.h
        include/utils/menu.h
        source/Graphs/CityGraph.cpp
        include/Graphs/CityGraph.h
        source/ds/Set.tpp
        include/ds/Set.h
        include/utils/pathfinding.h
        include/ds/Graph.h
        source/ds/Graph.tpp
        include/exceptions/KeyNotFoundException.h
        include/utils/graph.h
)

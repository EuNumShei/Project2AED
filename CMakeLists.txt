cmake_minimum_required(VERSION 3.26)
project(projetoAJUDA)

set(CMAKE_CXX_STANDARD 17)

add_executable(projetoAJUDA main.cpp
        Companhia.cpp
        Sistema.cpp
        Graph.cpp
        Distancia.h)

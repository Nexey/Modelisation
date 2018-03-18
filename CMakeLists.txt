cmake_minimum_required(VERSION 3.9)
project(Modelisation)

set(CMAKE_CXX_STANDARD 11)

add_executable(Modelisation
        Modelisation/Graphe/Graphe.h
        Modelisation/Graphe/Maillon.h
        Modelisation/Main/Erreur.h
        Modelisation/Main/Main.cpp
        Modelisation/Outils/ChargerGraphe.h
        Modelisation/Graphe/ElementsGraphe.h)

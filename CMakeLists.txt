cmake_minimum_required(VERSION 3.24)
project(TEP_Projekt)

set(CMAKE_CXX_STANDARD 17)

add_executable(TEP_Projekt main.cpp CKnapsackProblem.cpp CKnapsackProblem.h CGeneticAlgorithm.cpp CGeneticAlgorithm.h CIndividual.cpp CIndividual.h CProblem.h CMySmartPointer.h CMySmartPointer.tpp)

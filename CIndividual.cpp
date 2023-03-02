#include <iostream>
#include "CIndividual.h"

// CONSTRUCTORS, DESTRUCTOR AND OPERATORS=

CIndividual::CIndividual() {
    //std::cout << "CIndividual KD" << std::endl;
}

CIndividual::CIndividual(int genLen) {
   // std::cout << "CIndividual K" << std::endl;
    for(int i = 0; i < genLen; i++) {
        if(rand()%2==0) genotype.push_back(false);
        else genotype.push_back(true);
    }
}

CIndividual::CIndividual(CIndividual &&Cother) {
    //std::cout << "CIndividual KP" << std::endl;
    genotype = Cother.genotype;
}

CIndividual::CIndividual(const CIndividual &Cother) {
    //std::cout << "CIndividual KK" << std::endl;
    genotype = Cother.genotype;
}

CIndividual::~CIndividual() {
    //std::cout << "CIndividual D" << std::endl;
}

CIndividual &CIndividual::operator=(const CIndividual &cOther) {
    //std::cout << "CIndividual = const C &" << std::endl;
    genotype = cOther.genotype;
    return (*this);
}

CIndividual &CIndividual::operator=(CIndividual &&cOther) {
    //std::cout << "CIndividual = &&" << std::endl;
    genotype = cOther.genotype;
    return (*this);
}

// SOME FUNCTIONS

double CIndividual::fitness(CProblem &problem) {
    if(problem.genLen() != genotype.size()) throw std::invalid_argument("Invalid problem");
    return problem.fitness(genotype);
}

double CIndividual::computeWeight(CProblem &problem) {
    return problem.computeWeight(genotype);
}

double CIndividual::computeValue(CProblem &problem) {
    return problem.computeValue(genotype);
}

void CIndividual::mutate(double mutProb) {
    if(mutProb < 0 || mutProb > 1 ) throw std::invalid_argument("Invalid mutation probability!");
    for(int i = 0; i < genotype.size(); i++){
        if((float)rand() / (float)RAND_MAX < mutProb) genotype[i] = !genotype[i];
    }
}

void CIndividual::crossover(CIndividual &other) {
    if (genotype.size() != other.genotype.size()) {
        throw std::invalid_argument("Diffrent genotypes lenghts.");
    }
    bool tmp;
    for (int i = rand() % genotype.size(); i < genotype.size(); i++) {
        tmp = genotype[i];
        genotype[i] = other.genotype[i];
        other.genotype[i] = tmp;
    }
}

void CIndividual::show() {
    for(int i = 0; i < genotype.size(); i++){
        if(genotype[i]) std::cout << "1";
        else std::cout << "0";
    }
}


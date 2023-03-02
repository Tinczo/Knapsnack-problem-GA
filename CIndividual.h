//
// Created by szymi on 21.01.2023.
//

#ifndef TEP_PROJEKT_CINDIVIDUAL_H
#define TEP_PROJEKT_CINDIVIDUAL_H


#include <vector>
#include <cstdlib>
#include <algorithm>
#include "CKnapsackProblem.h"


class CIndividual {
public:

    // CONSTRUCTORS, DESTRUCTOR AND OPERATORS=
    CIndividual();
    CIndividual(int genLen);
    CIndividual(const CIndividual &Cother);
    CIndividual(CIndividual &&Cother);
    ~CIndividual();
    CIndividual& operator=(const CIndividual &cOther);
    CIndividual& operator=(CIndividual &&cOther);

    // SOME FUNCTIONS
    double fitness(CProblem & problem);
    double computeWeight(CProblem & problem);
    double computeValue(CProblem & problem);
    void mutate(double mutProb);
    void crossover(CIndividual& other);
    void show();

private:

    // FIELDS
    std::vector<bool> genotype;
};


#endif //TEP_PROJEKT_CINDIVIDUAL_H

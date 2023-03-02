//
// Created by szymi on 21.01.2023.
//

#ifndef TEP_PROJEKT_CGENETICALGORITHM_H
#define TEP_PROJEKT_CGENETICALGORITHM_H


#include <vector>
#include "CIndividual.h"

class CGeneticAlgorithm {
public:
    // CONSTRUCTORS, DESTRUCTOR AND OPERATORS=
    CGeneticAlgorithm();
    CGeneticAlgorithm(int popSize, double crossProb, double mutProb, CProblem &problem);
    CGeneticAlgorithm(const CGeneticAlgorithm &other);
    CGeneticAlgorithm(CGeneticAlgorithm &&other);
    ~CGeneticAlgorithm();
    CGeneticAlgorithm& operator=(const CGeneticAlgorithm &rhs);
    CGeneticAlgorithm& operator=(CGeneticAlgorithm &&rhs);

    // SOME FUNCTIONS
    CIndividual theBest(CProblem& problem);
    void GA(int iteration, CProblem& Problem);
    void populationFitness(CProblem& problem);

    // GETTERS
    int getPopSize() const;
    double getCrossProb() const;
    double getMutProb() const;

private:
    // FIELDS
    int _popSize;
    double _crossProb;
    double _mutProb;
    int _genLen;
    std::vector<CIndividual> _population;

};


#endif //TEP_PROJEKT_CGENETICALGORITHM_H

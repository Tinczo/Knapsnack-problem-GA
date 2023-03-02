#include <iostream>
#include "CGeneticAlgorithm.h"

// CONSTRUCTORS, DESTRUCTOR AND OPERATORS=

CGeneticAlgorithm::CGeneticAlgorithm() {
    //std::cout << "CGeneticAlgorithm KD" << std::endl;
    _popSize = 0;
    _genLen = 0;
    _crossProb = 0.5;
    _mutProb = 0.2;
}

CGeneticAlgorithm::CGeneticAlgorithm(int popSize, double crossProb, double mutProb, CProblem & problem) {

    if(crossProb < 0 || crossProb > 1 ) throw std::invalid_argument("Invalid crossing probability!");
    if(mutProb < 0 || mutProb > 1 ) throw std::invalid_argument("Invalid mutation probability!");
    if(popSize <= 1 ) throw std::invalid_argument("Invalid population size!");
    if(problem.genLen() <= 0) throw std::invalid_argument("Invalid problem!");

    //std::cout << "CGeneticAlgorithm K" << std::endl;
    _popSize = popSize;
    _crossProb = crossProb;
    _mutProb = mutProb;
    _population.reserve(_popSize);
    _genLen = problem.genLen();
    for(int i = 0; i < _popSize; i++) {
        _population.emplace_back(_genLen);
    }
}

CGeneticAlgorithm::CGeneticAlgorithm(const CGeneticAlgorithm &other) {
    //std::cout << "CGeneticAlgorithm KK" << std::endl;
    _popSize = other._popSize;
    _crossProb = other._crossProb;
    _mutProb = other._mutProb;
    _population = other._population;
}

CGeneticAlgorithm::CGeneticAlgorithm(CGeneticAlgorithm &&other) {
    //std::cout << "CGeneticAlgorithm KP" << std::endl;
    _popSize = other._popSize;
    _crossProb = other._crossProb;
    _mutProb = other._mutProb;
    _population = std::move(other._population);
    other._population.clear();
}

CGeneticAlgorithm::~CGeneticAlgorithm() {
    //std::cout << "CGeneticAlgorithm D" << std::endl;
}

CGeneticAlgorithm &CGeneticAlgorithm::operator=(const CGeneticAlgorithm &rhs) {
    //std::cout << "CGeneticAlgorithm = const C &" << std::endl;
    _popSize = rhs._popSize;
    _crossProb = rhs._crossProb;
    _mutProb = rhs._mutProb;
    _population = rhs._population;
    return (*this);
}

CGeneticAlgorithm &CGeneticAlgorithm::operator=(CGeneticAlgorithm &&rhs) {
    //std::cout << "CGeneticAlgorithm = &&" << std::endl;
    _popSize = rhs._popSize;
    _crossProb = rhs._crossProb;
    _mutProb = rhs._mutProb;
    _population = std::move(rhs._population);
    rhs._population.clear();
    return (*this);
}

//SOME FUNCTIONS

CIndividual CGeneticAlgorithm::theBest(CProblem& problem) {
    if(problem.genLen() != _genLen) throw std::invalid_argument("Invalid problem");
    if(_popSize <= 1) {
        std::cout << "Population does not exists." << std::endl;
        CIndividual ret;
        return ret;
    }else{
        double bestFit = 0;
        int id = 0;
        double actFit;
        for(int i = 0; i < _popSize; i++){
            actFit = _population[i].fitness(problem);
            if(actFit > bestFit){
                bestFit = actFit;
                id = i;
            }
        }
        return _population[id];
    }
}

void CGeneticAlgorithm::GA(int iteration, CProblem& problem) {
    if(iteration < 0) throw std::invalid_argument("Invalid number of iterations!");
    if(problem.genLen() <= 0 || problem.genLen() != _genLen) throw std::invalid_argument("Invalid problem!");
    int iter = 0;
    if(_popSize <= 1) {
        std::cout << "Population does not exist." << std::endl;
    } else {
        std::vector<CIndividual> nextGeneration;
        nextGeneration.reserve(_popSize);
        CIndividual *p1;
        CIndividual *p2;
        CIndividual *tmp;

        while (iter != iteration) {
            nextGeneration.reserve(_popSize);

            std::cout << "Iteration " << iter << std::endl;
            populationFitness(problem);

            if (_population.size() % 2 != 0) { // W przypadku gdy rozmiar populacji jest nieparzysty
                nextGeneration.push_back(_population[rand() % _popSize]);
            }

            for (int i = 0; i < _popSize / 2; i++) {
                // Wybór rodziców
                p1 = &(_population[rand() % _popSize]);
                tmp = &(_population[rand() % _popSize]);
                if (p1->fitness(problem) < tmp->fitness(problem)) p1 = tmp;

                p2 = &(_population[rand() % _popSize]);
                tmp = &(_population[rand() % _popSize]);
                if (p2->fitness(problem) < tmp->fitness(problem)) p2 = tmp;
                while (p2 != p1) {
                    p2 = &(_population[rand() % _popSize]);
                    tmp = &(_population[rand() % _popSize]);
                    if (p2->fitness(problem) < tmp->fitness(problem)) p2 = tmp;
                }

                //std::cout << "parent1 KK bedzie" << std::endl;
                CIndividual parent1(*p1);
                //std::cout << "parent2 KK bedzie" << std::endl;
                CIndividual parent2(*p2);

                if ((float) rand() / (float) RAND_MAX < _crossProb) {
                    parent1.crossover(parent2);
                }

                //std::cout << "push_back1 KK bedzie" << std::endl;
                nextGeneration.push_back(parent1);
                //std::cout << "push_back2 KK bedzie" << std::endl;
                nextGeneration.push_back(parent2);
            }
            //std::cout << "Czyszczenie populacji i _population = std::move(nextGeneration);" << std::endl;
            _population.clear();
            _population = std::move(nextGeneration);
            nextGeneration.clear();
            // Mutacja
            for (int i = 0; i < _popSize; i++) {
                //_population[i].show();
                _population[i].mutate(_mutProb);
                //std::cout << "\t";
               // _population[i].show();
              //  std::cout << "\n";
            }
            iter++;
        }
    }
}

void CGeneticAlgorithm::populationFitness(CProblem& problem) {
    if(problem.genLen() <= 0 || problem.genLen() != _genLen) throw std::invalid_argument("Invalid problem!");
    for(int i = 0; i < _popSize; i++) {
        _population[i].show();
        std::cout << "\tFitness: " << _population[i].fitness(problem);
        std::cout << "\tValue: " << _population[i].computeValue(problem);
        std::cout << "\tWeight: " << _population[i].computeWeight(problem) << std::endl;
    }
}

// GETTERS

int CGeneticAlgorithm::getPopSize() const {
    return _popSize;
}

double CGeneticAlgorithm::getCrossProb() const {
    return _crossProb;
}

double CGeneticAlgorithm::getMutProb() const {
    return _mutProb;
}


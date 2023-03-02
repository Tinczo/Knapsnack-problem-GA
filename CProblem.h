//
// Created by szymi on 21.01.2023.
//

#ifndef TEP_PROJEKT_CPROBLEM_H
#define TEP_PROJEKT_CPROBLEM_H

#include <vector>


class CProblem {
public:
    virtual double fitness(const std::vector<bool> & genotype) = 0;
    virtual double computeWeight(const std::vector<bool> & genotype) = 0;
    virtual double computeValue(const std::vector<bool> & genotype) = 0;
    virtual int genLen() = 0;
private:
};


#endif //TEP_PROJEKT_CPROBLEM_H

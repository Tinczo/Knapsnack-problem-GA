//
// Created by szymi on 21.01.2023.
//

#ifndef TEP_PROJEKT_CKNAPSACKPROBLEM_H
#define TEP_PROJEKT_CKNAPSACKPROBLEM_H


#include <string>
#include <vector>
#include "CProblem.h"
#include "CMySmartPointer.h"

class CKnapsackProblem : public CProblem {
public:
    // CONSTRUCTORS, DESTRUCTORS AND OPERATORS=
    CKnapsackProblem();
    CKnapsackProblem(std::string fileName);
    CKnapsackProblem(CKnapsackProblem &other); // musi być tak ponieważ inaczej nie dziala przy przepiywaniu danych
    CKnapsackProblem(CKnapsackProblem &&other);
    ~CKnapsackProblem();
    CKnapsackProblem& operator=(const CKnapsackProblem &rhs);
    CKnapsackProblem& operator=(CKnapsackProblem &&rhs);

    // SOME FUNCTIONS
    double fitness(const std::vector<bool> & genotype) override;
    double computeWeight(const std::vector<bool> & genotype) override;
    double computeValue(const std::vector<bool> & genotype) override;
    void showData();

    // SOME GETTERS
    int genLen() override;
    double getCapacity() const;
    int getItemsAmmount() const;

private:
    // SOME FIELDS
    double _capacity;
    int _itemsAmmount;
    CMySmartPointer<double> _tabValue;
    CMySmartPointer<double> _tabWeight;
};


#endif //TEP_PROJEKT_CKNAPSACKPROBLEM_H

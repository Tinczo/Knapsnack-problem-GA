#include <iostream>
#include <fstream>
#include "CKnapsackProblem.h"

CKnapsackProblem::CKnapsackProblem() {
   // std::cout << "CKnapsackProblem KD" << std::endl;
    _capacity = 0;
    _itemsAmmount = 0;
}

CKnapsackProblem::CKnapsackProblem(std::string fileName) {
   // std::cout << "CKnapsackProblem K" << std::endl;
    std::ifstream plik;
    std::string number;
    double capacity;
    double tmp;
    int itemsAmmount;
    plik.open(fileName.c_str());
    if(plik.good()){
        try {
            if(plik.eof()) throw std::invalid_argument("End of file!");
            plik >> capacity;
            if(plik.eof()) throw std::invalid_argument("End of file!");
            //std::cout << capacity << std::endl;
            if(capacity <= 0) throw std::invalid_argument("Invalid capacity!");
            plik >> tmp;
            if(plik.eof()) throw std::invalid_argument("End of file!");
            itemsAmmount = tmp;
           // std::cout << itemsAmmount << std::endl;
            if(itemsAmmount <= 0) throw std::invalid_argument("Invalid items ammount!");

            CMySmartPointer<double> tabValue(new double[itemsAmmount]);
            CMySmartPointer<double> tabWeight(new double[itemsAmmount]);
            for(int i = 0; i < itemsAmmount; i++)
            {
                if(plik.eof()) throw std::invalid_argument("End of file!");
                plik >> tmp;
                if(tmp <= 0) throw std::invalid_argument("Invalid value!");
                tabValue.operator->()[i] = tmp;
               // std::cout<< tabValue.operator->()[i] << std::endl;
            }
            for(int i = 0; i < itemsAmmount; i++) {
                if(plik.eof()) throw std::invalid_argument("End of file!");
                plik >> tmp;
                if(tmp <= 0) throw std::invalid_argument("Invalid weight!");
                tabWeight.operator->()[i] = tmp;
              //  std::cout << tabWeight.operator->()[i] << std::endl;
            }
            if(!plik.eof()) throw std::invalid_argument("Not end of file!");
            _capacity = capacity;
            _itemsAmmount = itemsAmmount;
            _tabValue = tabValue;
            _tabWeight = tabWeight;
            plik.close();

        }catch (const std::invalid_argument& e){
            if(plik.is_open()) plik.close();
            std::cout << "Error while loading file: " << e.what() << std::endl;
            std::cout << "Default fileds have been set..." << std::endl;
            _capacity = 0;
            _itemsAmmount = 0;
            _tabValue = CMySmartPointer<double>();
            _tabWeight = CMySmartPointer<double>();
        }catch (const std::out_of_range& e){
            if(plik.is_open()) plik.close();
            std::cout << "Error while loading file " << e.what() << std::endl;
            std::cout << "Default fileds have been set..." << std::endl;
            _capacity = 0;
            _itemsAmmount = 0;
            _tabValue = CMySmartPointer<double>();
            _tabWeight = CMySmartPointer<double>();
        }
    }
}

CKnapsackProblem::CKnapsackProblem(CKnapsackProblem &other) {
    //std::cout << "CKnapsackProblem KK" << std::endl;
    _capacity = other._capacity;
    _itemsAmmount = other._itemsAmmount;
    _tabValue = CMySmartPointer<double>(new double[_itemsAmmount]);
    _tabWeight = CMySmartPointer<double>(new double[_itemsAmmount]);
    for(int i = 0; i < _itemsAmmount; i++) _tabValue.operator->()[i] = other._tabValue.operator->()[i];
    for(int i = 0; i < _itemsAmmount; i++) _tabWeight.operator->()[i] = other._tabWeight.operator->()[i];
}

CKnapsackProblem::CKnapsackProblem(CKnapsackProblem &&other) {
    //std::cout << "CKnapsackProblem KP" << std::endl;
    _capacity = other._capacity;
    _itemsAmmount = other._itemsAmmount;
    _tabValue = other._tabValue;
    _tabWeight = other._tabWeight;
}

CKnapsackProblem::~CKnapsackProblem() {
   // std::cout << "CKnapsackProblem D" << std::endl;
}

CKnapsackProblem &CKnapsackProblem::operator=(const CKnapsackProblem &rhs) {
   // std::cout << "CKnapsackProblem = const C &" << std::endl;
    _capacity = rhs._capacity;
    _itemsAmmount = rhs._itemsAmmount;
    _tabValue = rhs._tabValue;
    _tabWeight = rhs._tabWeight;
    return (*this);
}

CKnapsackProblem &CKnapsackProblem::operator=(CKnapsackProblem &&rhs) {
    //std::cout << "CKnapsackProblem = &&" << std::endl;
    _capacity = rhs._capacity;
    _itemsAmmount = rhs._itemsAmmount;
    _tabValue = rhs._tabValue;
    _tabWeight = rhs._tabWeight;
    return (*this);
}

// SOME FUNCTIONS

double CKnapsackProblem::fitness(const std::vector<bool> &genotype) {
    if(_itemsAmmount != genotype.size()) throw std::invalid_argument("Invalid genotype.");

    double value = 0;
    double weight = 0;
    for(int i = 0; i < _itemsAmmount; i++){
        if(genotype[i]) {
            value += _tabValue.operator->()[i];
            weight += _tabWeight.operator->()[i];
        }
    }
    if(weight > _capacity) return 0;
    else return value;
}

double CKnapsackProblem::computeWeight(const std::vector<bool> &genotype) {
    if(_itemsAmmount != genotype.size()) throw std::invalid_argument("Invalid genotype.");

    double weight = 0;
    for(int i = 0; i < _itemsAmmount; i++){
        if(genotype[i]) {
            weight += _tabWeight.operator->()[i];
        }
    }
    return weight;
}

double CKnapsackProblem::computeValue(const std::vector<bool> &genotype) {
    if(_itemsAmmount != genotype.size()) throw std::invalid_argument("Invalid genotype.");
    double value = 0;
    for(int i = 0; i < _itemsAmmount; i++){
        if(genotype[i]) {
            value += _tabValue.operator->()[i];
        }
    }
    return value;
}

void CKnapsackProblem::showData() {
    std::cout << "Capacity: " << _capacity << std::endl;
    std::cout << "ItemsAmmount: " << _itemsAmmount << std::endl;
    std::cout << "Values: ";
    for(int i = 0; i < _itemsAmmount; i++) std::cout << _tabValue.operator->()[i] << " ";
    std::cout << "Shared with: " << _tabValue.shared();
    std::cout << std::endl << "Weights: ";
    for(int i = 0; i < _itemsAmmount; i++) std::cout << _tabWeight.operator->()[i] << " ";
    std::cout << "Shared with: " << _tabWeight.shared();
    std::cout << std::endl;
}

// SOMGE GETTERS

int CKnapsackProblem::genLen() {
    return _itemsAmmount;
}

double CKnapsackProblem::getCapacity() const {
    return _capacity;
}

int CKnapsackProblem::getItemsAmmount() const {
    return _itemsAmmount;
}




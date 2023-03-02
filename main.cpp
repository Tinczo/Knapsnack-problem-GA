#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include "CProblem.h"
#include "CIndividual.h"
#include "CGeneticAlgorithm.h"
#include "CKnapsackProblem.h"

void test_procentow();
void test_ladowanie_i_obliczanie();
void test_mutacji();
void test_fstream();
void test_vector_operator_rownasie(); // kopiuje, kopie są niezależne
void test_GA();
void test_Plecaki_Kostruktor_kopiujacy_i_operator_przypisujący();


int main() {
    srand(time(nullptr));
    test_GA();
    return 0;
}

void test_procentow() {
    for (int i = 0; i < 20; i++) {
        std::cout << (float) rand() / (float) RAND_MAX << std::endl;
    }
}

void test_ladowanie_i_obliczanie(){
    CKnapsackProblem plecak("test2.txt");
    CGeneticAlgorithm algorytm(5,0.5,0.2,plecak);

    algorytm.populationFitness(plecak);

    std::cout << std::endl;
    algorytm.theBest(plecak).show();
    std::cout << std::endl;
    std::cout << "Fitness: " << algorytm.theBest(plecak).fitness(plecak) << std::endl;
    std::cout << "Weight: " << algorytm.theBest(plecak).computeWeight(plecak) << std::endl;
}

void test_mutacji(){
    std::vector<bool> genotype;

    for(int i = 0; i < 10; i++) {
        if(rand()%2==0) genotype.push_back(false);
        else genotype.push_back(true);
    }

    for(int i = 0; i < 10; i++) {
        if (genotype[i]) std::cout << "1";
        else std::cout << "0";
    }
    std::cout<<std::endl;

    for(int i = 0; i < genotype.size(); i++){
        if((float)rand() / (float)RAND_MAX < 0.4) {
            std::cout << "Wczesniejsza: " << genotype[i];
            genotype[i] = !genotype[i];
            std::cout << "\tPozniejsza: " << genotype[i] << std::endl;
        }
    }

    for(int i = 0; i < 10; i++) {
        if (genotype[i]) std::cout << "1";
        else std::cout << "0";
    }
}

void test_fstream() {
    int x;
    int y;
    std::ifstream plik;
    plik.open("test.txt");
    if(plik.good()) {
        plik >> x;
        plik >> y;
    }
    std::cout << x << " " << y;
}

void test_GA(){
        int iteration = 20;
        CKnapsackProblem plecak("test2.txt");
        plecak.showData();
        CGeneticAlgorithm algorytm(9,0.5,0.1,plecak);
        algorytm.GA(iteration,plecak);
        std::cout << "Iteration " << iteration << std::endl;
        algorytm.populationFitness(plecak);
}

void test_vector_operator_rownasie(){
    std::vector<bool> v1;
    std::vector<bool> v2;
    v1.push_back(false);
    v1.push_back(false);
    v1.push_back(false);
    std::cout << v1[0] << " " << v1[1] << " " << v1[2] << std::endl;

    v2.push_back(true);
    v2.push_back(true);
    v2.push_back(true);
    std::cout << v2[0] << " " << v2[1] << " " << v2[2] << std::endl;

    v1 = v2;
    std::cout << v1[0] << " " << v1[1] << " " << v1[2] << std::endl;
    std::cout << v2[0] << " " << v2[1] << " " << v2[2] << std::endl;

    v2[0] = false;
    std::cout << v1[0] << " " << v1[1] << " " << v1[2] << std::endl;
    std::cout << v2[0] << " " << v2[1] << " " << v2[2] << std::endl;
}

void test_Plecaki_Kostruktor_kopiujacy_i_operator_przypisujący(){
    std::cout << "CKnapsackProblem plecak1(\"test.txt\");" << std::endl;
    CKnapsackProblem plecak1("test.txt");
    std::cout << "plecak1.showData();" << std::endl;
    plecak1.showData();
    std::cout << "CKnapsackProblem plecak2(\"test2.txt\");" << std::endl;
    CKnapsackProblem plecak2("test2.txt");
    std::cout << "plecak2.showData();" << std::endl;
    plecak2.showData();
    std::cout << "CKnapsackProblem plecak3(plecak2);" << std::endl;
    CKnapsackProblem plecak3(plecak2);
    std::cout << "plecak3.showData();" << std::endl;
    plecak3.showData();
    std::cout << "plecak2 = plecak1;" << std::endl;
    plecak2 = plecak1;
    std::cout << "plecak2.showData();" << std::endl;
    plecak2.showData();
    std::cout << "plecak1 = plecak3;" << std::endl;
    plecak1 = plecak3;
    std::cout << "plecak1.showData();" << std::endl;
    plecak1.showData();
    std::cout << "plecak2.showData();" << std::endl;
    plecak2.showData();
    std::cout << "plecak3.showData();" << std::endl;
    plecak3.showData();

}
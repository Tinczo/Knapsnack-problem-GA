//
// Created by szymi on 04.01.2022.
//

#include <iostream>
#include "CMySmartPointer.h"

template<typename T>
CMySmartPointer<T>::CMySmartPointer() {
    //std::cout << "CMySmartPointer KD" << std::endl;
    pc_pointer = new T;
    pc_counter = new CRefCounter();
    pc_counter->iAdd();
}

template<typename T>
CMySmartPointer<T>::CMySmartPointer(T* pcPointer) {
    //std::cout << "CMySmartPointer K" << std::endl;
    pc_pointer = pcPointer;
    pc_counter = new CRefCounter();
    pc_counter->iAdd();
}

template<typename T>
CMySmartPointer<T>::CMySmartPointer(const CMySmartPointer& pcOther) {
    //std::cout << "CMySmartPointer KK" << std::endl;
    share(pcOther);
}

template<typename T>
CMySmartPointer<T>::~CMySmartPointer() {
    //std::cout << "CMySmartPointer D" << std::endl;
    detach();
}

template<typename T>
CMySmartPointer<T>& CMySmartPointer<T>::operator=(const CMySmartPointer<T>& rhs) {
   // std::cout << "CMySmartPointer = const C &" << std::endl;
    detach();
    share(rhs);
    return (*this);
}


template<typename T>
void CMySmartPointer<T>::share(const CMySmartPointer<T>& cOther) {
    pc_pointer = cOther.pc_pointer;
    pc_counter = cOther.pc_counter;
    pc_counter->iAdd();
}

template<typename T>
void CMySmartPointer<T>::detach() {
    if (pc_counter->iDec() == 0)
    {
        delete [] pc_pointer;
        delete [] pc_counter;
    }
}

template<typename T>
int CMySmartPointer<T>::shared() {
    return pc_counter->iGet();
}





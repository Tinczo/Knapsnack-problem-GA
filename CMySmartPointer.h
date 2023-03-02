//
// Created by szymi on 24.01.2023.
//

#ifndef TEP_PROJEKT_CMYSMARTPOINTER_H
#define TEP_PROJEKT_CMYSMARTPOINTER_H

template <typename T>
class CMySmartPointer
{
public:
    // CONSTRUKTORS, DESTRUCTORS AND OPERATORS=
    CMySmartPointer();
    CMySmartPointer(T* pcPointer);
    CMySmartPointer(const CMySmartPointer& pcOther);
    ~CMySmartPointer();
    CMySmartPointer<T>& operator=(const CMySmartPointer<T>& rhs);

    // SOME FUNCTIONS
    T* operator->() { return(pc_pointer); }
    T& operator*() { return(*pc_pointer); }
    int shared();

private:
    class CRefCounter {
    public:
        CRefCounter() { i_count = 0; }
        int iAdd() { return(++i_count); }
        int iDec() { return(--i_count); };
        int iGet() { return(i_count); }
    private:
        int i_count;
    };

    void share(const CMySmartPointer<T>& cOther);
    void detach();
    T* pc_pointer;
    CRefCounter* pc_counter;
};



#include "CMySmartPointer.tpp"


#endif //TEP_PROJEKT_CMYSMARTPOINTER_H

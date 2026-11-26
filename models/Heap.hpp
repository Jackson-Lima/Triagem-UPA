#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>
#include "Patient.hpp"

using namespace std;

// Min-heap de pacientes, ordenado pela regra de precedência do enunciado
class Heap
{
    private:
        vector<Patient> data;  // árvore binária guardada em vetor

        // Índices de pai e filhos na numeração do vetor, começando em 0
        int parent(int i) const;
        int leftChild(int i) const;
        int rightChild(int i) const;

    public:
        Heap();
        bool isEmpty() const;
        int getSize() const;
};

#endif
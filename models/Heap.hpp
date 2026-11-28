#ifndef HEAP_HPP
#define HEAP_HPP

#include <vector>
#include "Patient.hpp"

using namespace std;

// Min-heap de pacientes, ordenado pela regra de precedência do enunciado
class Heap
{
    private:
        vector<Patient> data;  // Árvore binária guardada em vetor

        // Índices de pai e filhos na numeração do vetor, começando em 0
        int parent(int i) const;
        int leftChild(int i) const;
        int rightChild(int i) const;
        
        void swap(int i, int j);  // Troca dois elementos do vetor
        void siftUp(int i);     // Sobe o elemento na posição i até a posição correta
        void siftDown(int i);   // Desce o elemento da posição i enquanto um dos filhos precede ele

        vector<int> position;  // position[id] = índice do paciente id em data, ou -1 se não estiver no heap

    public:
        Heap();
        bool isEmpty() const;
        int getSize() const;    // Tamanho do vetor

        void insert(const Patient &p);  // Inserção no Heap

        // Consulta a raiz. Pré-condição: o heap não pode estar vazio (checar com isEmpty() antes)
        const Patient &peekTop() const;

        Patient removeTop();  // Remove o paciente mais urgente

        bool reclassify(int id, PatientPriority newPriority);  // False se o paciente não estiver no heap

        bool removeById(int id);  // False se o paciente não estiver no heap

        vector<Patient> listOrdered() const;  // Lista a fila de espera sem alterar o heap
};

#endif
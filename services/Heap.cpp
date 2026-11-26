// services/heap.cpp
#include "../models/Heap.hpp"

Heap::Heap() {}

bool Heap::isEmpty() const
{
    return data.empty();
}

int Heap::getSize() const
{
    return static_cast<int>(data.size()); // Converte o retorno size_t (int sem sinal) em int
}

// Índice do pai. Não chamar com i = 0 pois a raiz não tem pai.
int Heap::parent(int i) const
{
    return (i - 1) / 2;
}

// Índice do filho esquerdo. Pode estar fora do vetor, por isso quem chama deve checar o tamanho.
int Heap::leftChild(int i) const
{
    return 2 * i + 1;
}

// Índice do filho direito. Mesma observação do filho esquerdo.
int Heap::rightChild(int i) const
{
    return 2 * i + 2;
}
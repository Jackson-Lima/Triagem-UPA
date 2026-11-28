#include "../models/Heap.hpp"

Heap::Heap() {}

bool Heap::isEmpty() const
{
    return data.empty();
}

// Tamanho do vetor
int Heap::getSize() const
{
    return static_cast<int>(data.size()); // Converte o retorno size_t (int sem sinal) em int
}

// Índice do pai. Não chamar com i = 0 pois a raiz não tem pai
int Heap::parent(int i) const
{
    return (i - 1) / 2;
}

// Índice do filho esquerdo. Pode estar fora do vetor, por isso quem chama deve checar o tamanho
int Heap::leftChild(int i) const
{
    return 2 * i + 1;
}

// Índice do filho direito. Mesma observação do filho esquerdo
int Heap::rightChild(int i) const
{
    return 2 * i + 2;
}

// Inserção
void Heap::insert(const Patient &p)
{
    // Garante que position tem espaço para o id do paciente (-1 = ainda fora do heap)
    if (p.getId() >= static_cast<int>(position.size())){
        position.resize(p.getId() + 1, -1);     // Adiciona +1 espaço e coloca o -1 nele, informando que está fora
    }

    // Coloca o paciente no fim do vetor (última posição da árvore)
    data.push_back(p);

    // Descobre em qual posição ele ficou
    int novaPosicao = static_cast<int>(data.size()) - 1;  // size() devolve size_t (sem sinal), então converte para int

    // Registra a posição de entrada, antes do siftUp (que pode mudar ela depois, no swap)
    position[p.getId()] = novaPosicao;

    // Sobe o paciente enquanto ele preceder o pai
    siftUp(novaPosicao);
}

// Troca os elementos das posições i e j.
void Heap::swap(int i, int j)
{
    Patient temp = data[i];
    data[i] = data[j];
    data[j] = temp;

    // Atualiza as posições dos dois ids que trocaram de lugar
    position[data[i].getId()] = i;  //o paciente de id "X" agora está na posição i
    position[data[j].getId()] = j;  //o paciente de id "Y" agora está na posição j
}

// Sobe o elemento da posição i enquanto ele precede o pai (O menor para o topo)
void Heap::siftUp(int i)
{
    while (i > 0)
    {
        int p = parent(i);

        // Se o elemento não precede o pai, a propriedade já está valendo: break
        if (!data[i].precedes(data[p])){
            break;
        } else {
            swap(i, p);
            i = p;  // Continua a partir da nova posição
        }
    }
}

// Desce o elemento da posição i enquanto um dos filhos precede ele (O maior pra baixo)
void Heap::siftDown(int i)
{
    int n = getSize();

    while (true)    // Continua até break parar o laço
    {
        int left = leftChild(i);
        int right = rightChild(i);
        int best = i;  // Índice do mais urgente entre i e seus filhos nesta volta. Começa valendo i e muda só se um filho vencer

        // Filho esquerdo existe e precede o best atual?
        if (left < n && data[left].precedes(data[best])){
            best = left;
        }

        // Filho direito existe e precede o best atual (que pode já ser o esquerdo)?
        if (right < n && data[right].precedes(data[best])){
            best = right;
        }

        // Ninguém precede o elemento: a propriedade do heap já está valendo 
        if (best == i){
            break;
        }

        // O filho vencedor (que está na posição best) sobe para i, e o que estava em i desce para best, na árvore (vetor)
        swap(i, best);  

        // Passa para "i" a posição do best (onde o elemento que desceu foi parar). A próxima volta compara os filhos dele
        i = best;
    }
}

// Consulta a raiz
const Patient &Heap::peekTop() const
{
    return data[0];  // A raiz é o mais urgente
}

// Remove e devolve o paciente mais urgente.
Patient Heap::removeTop()
{
    Patient top = data[0];        // Guarda a raiz, o paciente que vai sair

    swap(0, getSize() - 1);       // Troca: leva a raiz (que vai sair) para o fim e o último para o topo
    data.pop_back();              // Remove o último (que agora é a raiz antiga)
    position[top.getId()] = -1;   // O paciente saiu do heap

    if (!isEmpty()){
        siftDown(0);              // Desce o novo topo (que antes era o ultimo) para a posição correta
    }

    return top;                   // Devolve o paciente removido
}

// Altera a prioridade de um paciente pelo id e reorganiza o heap
bool Heap::reclassify(int id, PatientPriority newPriority)
{
    // Checa se o id existe na árvore e se o paciente está no heap (-1 = fora)
    if (id < 0 || id >= static_cast<int>(position.size()) || position[id] == -1){
        return false;
    }

    int index = position[id];         // Onde o paciente está agora
    data[index].setPriority(newPriority);

    siftUp(index);                    // Se ficou mais urgente, sobe
    siftDown(position[id]);           // Se ficou menos urgente, desce (usa a posição atual pois siftUp pode ter mudado ela)

    return true;
}

// Remove o paciente com o id dado, de qualquer posição do heap
bool Heap::removeById(int id)
{
    // Checa id negativo, id fora do vetor e id já removido (-1)
    if (id < 0 || id >= static_cast<int>(position.size()) || position[id] == -1){
        return false;
    }

    int index = position[id];          // Onde o paciente está agora
    int last = getSize() - 1;          // Último índice do vetor

    swap(index, last);                 // Leva o paciente para o fim
    data.pop_back();                   // Remove o paciente do vetor
    position[id] = -1;                 // Paciente saiu do heap

    // Reorganiza o paciente que era o último e ficou no lugar do removido
    // Se o paciente removido era o último, não há ninguém para reorganizar
    if (index < getSize()){
        siftUp(index);                              // Se o elemento que veio para index é mais urgente que o pai, sobe
        siftDown(position[data[index].getId()]);    // Se ele é menos urgente que os filhos, desce (usa a posição atual, que o siftUp pode ter mudado)
    }

    return true;
}

// Lista a fila de espera na ordem de atendimento e sem alterar o heap original
vector<Patient> Heap::listOrdered() const
{
    Heap copy = *this;   // Cópia completa (data e position), para poder remover sem afetar o original
    vector<Patient> ordered;

    while (!copy.isEmpty()){
        ordered.push_back(copy.removeTop());  // O removeTop devolve sempre o mais urgente restante
    }
    
    return ordered;
}
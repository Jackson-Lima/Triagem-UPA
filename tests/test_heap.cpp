// tests/test_heap.cpp
#include <iostream>
#include "../models/Heap.hpp"
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int failures = 0;

void check(bool condition, const string &description)
{
    if (condition)
    {
        cout << "[OK]    " << description << endl;
    }
    else
    {
        cout << "[FALHA] " << description << endl;
        failures++;
    }
}

int main()
{
    // Cenário: a raiz deve ser YELLOW (id 3), por ser a única prioridade mais urgente
    Heap heap;
    heap.insert(Patient(1, "Bruno", 40, "tosse", PatientPriority::BLUE, 1));
    heap.insert(Patient(2, "Diego", 35, "corte", PatientPriority::GREEN, 2));
    heap.insert(Patient(3, "Ana", 30, "febre", PatientPriority::YELLOW, 3));
    heap.insert(Patient(4, "Carla", 25, "dor", PatientPriority::BLUE, 4));

    check(heap.peekTop().getId() == 3, "antes: raiz é YELLOW (id 3)");

    // Caso 1: reclassificar para cima. Carla (id 4) passa de BLUE para RED e deve virar a raiz
    check(heap.reclassify(4, PatientPriority::RED), "reclassify retorna true para id existente");
    check(heap.peekTop().getId() == 4, "subiu: RED (id 4) virou a raiz");

    // Caso 2: reclassificar para baixo. Carla volta para BLUE e a raiz deve ser YELLOW de novo
    check(heap.reclassify(4, PatientPriority::BLUE), "reclassify para BLUE");
    check(heap.peekTop().getId() == 3, "desceu: YELLOW (id 3) voltou para a raiz");

    // Caso 3: reclassificar um paciente que está no fim da árvore (Bruno, id 1) para RED.
    // Como a chegada dele é 1, ele vence o RED de Carla... mas Carla já é BLUE, então Bruno vira a raiz.
    check(heap.reclassify(1, PatientPriority::RED), "reclassify do id 1 para RED");
    check(heap.peekTop().getId() == 1, "subiu: RED (id 1, chegada 1) virou a raiz");

    // Caso 4: id que nunca entrou no heap
    check(!heap.reclassify(99, PatientPriority::RED), "id inexistente retorna false");

    // Caso 5: a remoção final deve seguir a prioridade: RED(1), YELLOW(3), GREEN(2), BLUE(4)
    int ordem[4];
    for (int k = 0; k < 4; k++)
        ordem[k] = heap.removeTop().getId();

    check(ordem[0] == 1 && ordem[1] == 3 && ordem[2] == 2 && ordem[3] == 4,
          "removeTop devolve os ids 1, 3, 2, 4");
    check(heap.isEmpty(), "heap vazio após remover todos");

    // Caso 6: paciente já removido não pode ser reclassificado (position = -1)
    check(!heap.reclassify(1, PatientPriority::BLUE), "paciente removido retorna false");

    // Caso 7: removeById no meio da árvore, com o último mais urgente que o pai
    Heap h2;
    h2.insert(Patient(1, "A", 1, "x", PatientPriority::BLUE, 1));
    h2.insert(Patient(2, "B", 1, "x", PatientPriority::YELLOW, 2));
    h2.insert(Patient(3, "C", 1, "x", PatientPriority::GREEN, 3));
    h2.insert(Patient(4, "D", 1, "x", PatientPriority::RED, 4));

    check(h2.removeById(2), "removeById retorna true para id no meio");
    check(!h2.removeById(2), "removeById de paciente já removido retorna false");
    check(h2.peekTop().getId() == 4, "após remover id 2, a raiz continua sendo RED (id 4)");

    int ordem2[3];
    for (int k = 0; k < 3; k++)
        ordem2[k] = h2.removeTop().getId();

    check(ordem2[0] == 4 && ordem2[1] == 3 && ordem2[2] == 1,
        "ordem restante após removeById: 4 (RED), 3 (GREEN), 1 (BLUE)");
    check(h2.isEmpty(), "heap vazio após remover os restantes");

    // Caso 8: listOrdered não altera o heap original
    Heap h3;
    h3.insert(Patient(1, "A", 1, "x", PatientPriority::BLUE, 1));
    h3.insert(Patient(2, "B", 1, "x", PatientPriority::YELLOW, 2));
    h3.insert(Patient(3, "C", 1, "x", PatientPriority::GREEN, 3));
    h3.insert(Patient(4, "D", 1, "x", PatientPriority::RED, 4));

    vector<Patient> lista = h3.listOrdered();

    check(lista.size() == 4, "listOrdered devolve os 4 pacientes");
    check(lista[0].getId() == 4 && lista[1].getId() == 2 &&
        lista[2].getId() == 3 && lista[3].getId() == 1,
        "ordem de listOrdered: RED(4), YELLOW(2), GREEN(3), BLUE(1)");
    check(h3.getSize() == 4, "heap original continua com 4 pacientes");
    check(h3.peekTop().getId() == 4, "raiz do heap original continua sendo RED (id 4)");

    // Caso 9: comparação com std::sort (gabarito)
    Heap h4;
    vector<Patient> base;
    for (int id = 1; id <= 20; id++)
    {
        PatientPriority pr = static_cast<PatientPriority>(id % 5 + 1);  // prioridades 1 a 5
        int arrival = (id * 7) % 11;                                     // chegadas com empates
        Patient p(id, "P" + to_string(id), 30, "x", pr, arrival);
        base.push_back(p);
        h4.insert(p);
    }

    vector<Patient> gabarito = base;
    sort(gabarito.begin(), gabarito.end(),
        [](const Patient &a, const Patient &b) { return a.precedes(b); });

    vector<Patient> saida = h4.listOrdered();

    bool iguais = saida.size() == gabarito.size();
    for (size_t k = 0; iguais && k < saida.size(); k++)
        iguais = saida[k].getId() == gabarito[k].getId();

    check(iguais, "listOrdered com 20 pacientes bate com o std::sort");

    cout << endl;
    if (failures == 0)
        cout << "Todos os testes passaram." << endl;
    else
        cout << failures << " teste(s) falharam." << endl;

    return failures == 0 ? 0 : 1;
}
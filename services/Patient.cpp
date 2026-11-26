#include "../models/Patient.hpp"

Patient::Patient(int id, const string &name, int age, const string &complaint, PatientPriority priority, int arrival)
{
    this->id = id;
    this->name = name;
    this->age = age;
    this->complaint = complaint;
    this->priority = priority;
    this->arrival = arrival;
}

int Patient::getId() const
{
    return id;
}

const string &Patient::getName() const
{
    return name;
}

int Patient::getAge() const
{
    return age;
}

const string &Patient::getComplaint() const
{
    return complaint;
}

PatientPriority Patient::getPriority() const
{
    return priority;
}

int Patient::getArrival() const
{
    return arrival;
}

void Patient::setPriority(PatientPriority newPriority)
{
    priority = newPriority;
}

bool Patient::precedes(const Patient &other) const
{
    // enum class não compara com < diretamente, então é necessário converter para int
    int myPriority = static_cast<int>(priority);
    int otherPriority = static_cast<int>(other.priority);

    if (myPriority != otherPriority)
        return myPriority < otherPriority;   // número menor = mais grave
    if (arrival != other.arrival)
        return arrival < other.arrival;      // mesma prioridade: quem chegou antes
    return id < other.id;                    // empate total: menor id
}
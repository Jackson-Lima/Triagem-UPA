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
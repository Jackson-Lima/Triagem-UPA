#ifndef PATIENT_HPP
#define PATIENT_HPP

#include <string>
#include "../enums/PatientPriority.hpp"

using namespace std;

// Representa um paciente na fila de triagem
class Patient
{
    private:
        int id;                    // senha de atendimento, gerado pelo sistema
        string name;               // nome do paciente
        int age;                   // idade em anos
        string complaint;          // queixa principal
        PatientPriority priority;  // classe de risco (RED a BLUE)
        int arrival;               // minuto simulado de chegada

    public:
        Patient(int id, const string &name, int age, const string &complaint, PatientPriority priority, int arrival);

        int getId() const;
        const string &getName() const;
        int getAge() const;
        const string &getComplaint() const;
        PatientPriority getPriority() const;
        int getArrival() const;

        // Usado na reclassificação. Não altera a chegada, que serve de desempate.
        void setPriority(PatientPriority newPriority);

        // Regra de precedência: prioridade, chegada, id
        bool precedes(const Patient &other) const;

};

#endif
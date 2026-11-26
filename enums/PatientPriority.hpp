// Impede que o mesmo arquivo .hpp seja incluído mais de uma vez durante a compilação.
#pragma once

// Classificação de risco
enum class PatientPriority
{
    RED = 1,     // Emergência: atendimento imediato (0 min)
    ORANGE = 2,  // Muito urgente: 10 min
    YELLOW = 3,  // Urgente: 60 min
    GREEN = 4,   // Pouco urgente: 120 min
    BLUE = 5     // Não urgente: 240 min
};
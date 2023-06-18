#include <stdio.h>
#include "libagenda.h"

int main()
{
    agenda_t* agenda = cria_agenda();

    
    insere_compromisso(agenda, cria_horario_compromisso(12, 30, 14, 0), 1, "Reuniao");
    insere_compromisso(agenda, cria_horario_compromisso(9, 0, 10, 30), 2, "Apresentacao");
    insere_compromisso(agenda, cria_horario_compromisso(16, 0, 17, 30), 3, "Treinamento");

   
    imprime_agenda_mes(agenda);

    
    destroi_agenda(agenda);

    return 0;
}

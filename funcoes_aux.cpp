#include "funcoes_aux.h"

#define DIFICULDADE 20


bool ta_na_hora()
{
    return rand()%100<(DIFICULDADE/5);
}

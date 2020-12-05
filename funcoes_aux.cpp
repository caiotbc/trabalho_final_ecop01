#include "funcoes_aux.h"

#define DIFICULDADE 10


bool ta_na_hora()
{
    return rand()%100<(DIFICULDADE/5);
}

#ifndef __C_MINADO_LOGIC_H__
#define __C_MINADO_LOGIC_H__

#include "../build/type.h"

int verificarQuantidadesDeJogadas(struct CampoMinado campoMinado ) {
  
  int jogadas = 0;

  for(int i = 1; i < MAX - 1; i++) {
    for(int j = 1; j < MAX - 1; j++) { 
      if(campoMinado.campoJogadas[i][j] == DESATIVADO)
        jogadas++;
    }
  }

  return jogadas - campoMinado.bombas;
}

#endif //__C_MINADO_LOGIC_H__
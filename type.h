#ifndef __C_MINADO_TYPE_H__
#define __C_MINADO_TYPE_H__

#include <stdbool.h>


#define MAX 10
#define BOMBA 9
#define VAZIO 0
#define VERSAO "0.0.2"



struct Coordenada
{
  int i;
  int j;
};

struct CampoMinado
{
  char campo[MAX][MAX];
  char campoJogadas[MAX][MAX];
  int nivel;
  int bombas;
  int jogadas;
  bool fimDoJogo;
  struct Coordenada coordenada;
};

#endif // __C_MINADO_TYPE_H__
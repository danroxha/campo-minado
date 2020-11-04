#ifndef __C_MINADO_DRAW_H__
#define __C_MINADO_DRAW_H__


#include <stdio.h>
#include "type.h"


void desenharCampoMinado(struct CampoMinado );
void desenharTabuleiro(struct CampoMinado );


void desenharTabuleiro(struct CampoMinado campoMinado) {

  system("clear");
  printf("\033[40;7m");

  switch(campoMinado.nivel) {
    case FACIL  : printf("Nivel: \033[34;3m Facil | ");    break;
    case MEDIO  : printf("Nivel: \033[32;3m Medio  | ");   break;
    case DIFICIL: printf("Nivel: \033[31;3m Dificil  | "); break;
  }

  printf("Bombas: %d | Jogadas: %d \033[0;0m\n", campoMinado.bombas, campoMinado.jogadas);

  desenharCampoMinado(campoMinado);

  const char* mensagemPerdeu = "\033[47;31;7m VOCÊ PERDEU! BOMBA EM ";
  const char* mensagemGanhou = "\033[42;1m VOCÊ GANHOU! \033[0;0m\n";
  const char* mensagemJogada = "\033[41;1m ULTIMA JOGADA: ";


  if( campoMinado.fimDoJogo && campoMinado.jogadas > 0)
    printf("%s (%d, %d)\033[0;0m\n", mensagemPerdeu, campoMinado.coordenada.i, campoMinado.coordenada.j);
  else if( !campoMinado.fimDoJogo && campoMinado.jogadas <= 0)
    printf("%s", mensagemGanhou);
  else if( campoMinado.jogadas + campoMinado.bombas < (MAX - 2)*(MAX - 2))
    printf("%s (%d, %d)\033[0;0m\n", mensagemJogada, campoMinado.coordenada.i, campoMinado.coordenada.j);
   
  printf("MENU (0,0) | NOVO JOGO (9,9)\n");
  printf("COMANDO | POSICAO (linha, coluna): ");
}


void desenharCampoMinado(struct CampoMinado campoMinado) {

  for(int i = 0; i < MAX; i++) {
    if(i != 0 && i < MAX - 1) printf("%d", i);
    else printf("    ");    
  }

  printf("\n");
  
  for(int i = 0; i < MAX; i++) {
    
    if(i != 0 && i < MAX - 1) printf(" %d ", i);
    else printf("   ");  

    for(int j = 0; j < MAX; j++) {
     
      if( campoMinado.campo[i][j] == BOMBA && campoMinado.fimDoJogo) printf("\033[33;31;5m*\033[0;0m");
      else if( campoMinado.campo[i][j] == 21 ) printf("\033[1;34m\u2554\033[0;0m"); // "\u2554: ╔"
      else if( campoMinado.campo[i][j] == 22 ) printf("\033[1;34m\u2557\033[0;0m"); // "\u2557: ╗"
      else if( campoMinado.campo[i][j] == 23 ) printf("\033[1;34m\u255A\033[0;0m"); // "\u255A: ╚"
      else if( campoMinado.campo[i][j] == 24 ) printf("\033[1;34m\u255D\033[0;0m"); // "\u255D: ╝"
      else if( campoMinado.campo[i][j] == 25 ) printf("\033[1;34m\u2551\033[0;0m"); // "\u2551: ║"
      else if( campoMinado.campo[i][j] == 26 ) printf("\033[1;34m\u2550\033[0;0m"); // "\u2550: ═"
      else if( campoMinado.campo[i][j] >= VAZIO && campoMinado.campo[i][j] <= BOMBA && !campoMinado.fimDoJogo && !campoMinado.campoJogadas[i][j]) printf("\u2B25"); // "\u2B25: ⬥" 
      else if( campoMinado.campo[i][j] == VAZIO && campoMinado.campoJogadas[i][j]) printf(" ");
      else printf("\033[1;33m%d\033[0;0m", campoMinado.campo[i][j]);
    }

    printf("\n");
  }
}

#endif // __C_MINADO_DRAW_H__
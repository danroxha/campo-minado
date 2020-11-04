#ifndef __C_MINADO_GENERATORS_H__
#define __C_MINADO_GENERATORS_H__


#include <time.h>
#include <stdlib.h>
#include <stdbool.h>


#include "type.h"
#include "../logic/logic.h"


void gerarCampoMinado(struct CampoMinado*);
void gerarDica(struct CampoMinado*);
void revelarCasasVazias(struct CampoMinado*, struct Coordenada);


void gerarCampoMinado(struct CampoMinado* campoMinado) {
  
  srand(clock());
  
  campoMinado->bombas = 0;
  campoMinado->jogadas = 0;
  campoMinado->fimDoJogo = false;
  campoMinado->coordenada.i = 0;
  campoMinado->coordenada.j = 0;


  for(int i = 0; i < MAX; i++) {
    for(int j = 0; j < MAX; j++) {

      campoMinado->campoJogadas[i][j] = 0;
      
      bool primeiraLinha   = i == 0;
      bool ultimaLinha     = i == MAX - 1;
      bool limiteEsquerda  = j == 0;
      bool limiteDireira   = j == MAX - 1;

      if(primeiraLinha || ultimaLinha || limiteEsquerda || limiteDireira) {
       
        if(primeiraLinha && limiteEsquerda )       campoMinado->campo[i][j] = 21; // "\u2554: ╔"
        else if( primeiraLinha && limiteDireira )  campoMinado->campo[i][j] = 22; // "\u2557: ╗"
        else if( ultimaLinha && limiteEsquerda )   campoMinado->campo[i][j] = 23; // "\u255A: ╚"
        else if( ultimaLinha && limiteDireira )    campoMinado->campo[i][j] = 24; // "\u255A: ╝"
        else if( limiteEsquerda || limiteDireira ) campoMinado->campo[i][j] = 25; // "\u2551: ║"
        else if( primeiraLinha || ultimaLinha )    campoMinado->campo[i][j] = 26; // "\u2550: ═"
        continue;
      
      }

      
      int chanceDeBomba;

      switch(campoMinado->nivel) {
        default     : chanceDeBomba = P_SESSENTA;       break;
        case FACIL  : chanceDeBomba = P_QUINZE;         break;
        case MEDIO  : chanceDeBomba = P_VINTE_E_CINCO;  break;
        case DIFICIL: chanceDeBomba = P_TRINTA_E_CINCO; break;
      }
      
      campoMinado->campo[i][j] = (char)(rand() % P_CEM <= chanceDeBomba )? BOMBA : VAZIO;
      
      if(campoMinado->campo[i][j] == BOMBA)
        campoMinado->bombas++;
    }
  }

  if(!campoMinado->bombas) 
    gerarCampoMinado(campoMinado);

  gerarDica(campoMinado);
  campoMinado->jogadas = verificarQuantidadesDeJogadas(*campoMinado);
}


void gerarDica(struct CampoMinado* campoMinado) {
  
  for(int i = 1; i < MAX - 1; i++) {
    for(int j = 1; j < MAX - 1; j++) {
    
      if(campoMinado->campo[i][j] == BOMBA) {
        // Adicionar +1 ao redor das bombas
        for(int y = i - 1; y <= i + 1; y++) {
          
          bool limiteAlturaSuperior = y < 1; 
          bool limiteAlturaInferior = y > MAX - 2;

          if(limiteAlturaSuperior) y = 1;
          if(limiteAlturaInferior) continue;

          for(int x = j - 1; x <= j + 1; x++) { 
          
            bool limiteLateralEsquerdo = x < 1; 
            bool limiteLateralDireito  = x > MAX - 2;

            if(limiteLateralEsquerdo) x = 1;
            if(limiteLateralDireito ) continue;
            

            bool naoEhUmaBomba = campoMinado->campo[y][x] != BOMBA;
            if(naoEhUmaBomba)
              campoMinado->campo[y][x]++;

          }
        }
      }
    }
  }
}


void revelarCasasVazias(struct CampoMinado* campoMinado, struct Coordenada coordenada ) {
  
  campoMinado->campoJogadas[coordenada.i][coordenada.j] = 1;

  for(int i = coordenada.i - 1; i <= coordenada.i + 1; i++) {
    
    bool limiteAlturaSuperior = i < 1; 
    bool limiteAlturaInferior = i > MAX - 2;

    if(limiteAlturaSuperior) i = 1;
    if(limiteAlturaInferior) continue;
    

    for(int j = coordenada.j - 1; j <= coordenada.j + 1; j++) {

      bool limiteLateralEsquerdo = j < 1; 
      bool limiteLateralDireito  = j > MAX - 2;

      if(limiteLateralEsquerdo) j = 1;
      if(limiteLateralDireito ) continue;

      if(campoMinado->campo[i][j] == VAZIO &&  campoMinado->campoJogadas[i][j] != ATIVADO) {
        struct Coordenada coord = {i , j};
        revelarCasasVazias(campoMinado, coord);
      }
      else
        campoMinado->campoJogadas[i][j] = 1;
  
    }
  }
}


#endif //__C_MINADO_GENERATORS_H__
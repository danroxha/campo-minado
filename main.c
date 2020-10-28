#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#include "type.h"
#include "banner.h"


void criarCampoMinado(struct CampoMinado*);
void gerarDica(struct CampoMinado*);
void jogo(struct CampoMinado* );
void desenharTabuleiro(struct CampoMinado);
void desenharCampoMinado(struct CampoMinado);
void obterComando(int *opcao, void (*)(void *), void *dados);


int main(){

  struct CampoMinado campoMinado;
    campoMinado.nivel = 1;

  enum OPCOES {
    INICIAR_JOGO = 1, SELECIONAR_NIVEL = 2, SAIR = 3
  };

  int opcao;

  bannerIntroducao(); 

  do {
    
    obterComando(&opcao, bannerMenu, NULL);

    switch(opcao) {
      case INICIAR_JOGO: 
        jogo(&campoMinado);
        break;
      case SELECIONAR_NIVEL:
        obterComando(&campoMinado.nivel, bannerNivel, (void*) &campoMinado);
        break;
    }

    if( opcao == SAIR)
      bannerSair();
  }

  while(opcao != SAIR);
  
}


void criarCampoMinado(struct CampoMinado* campoMinado) {
  
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
        
      enum Porcentagem {
        QUINZE          = 15, 
        VINTE_E_CINCO   = 25, 
        TRINTA_E_CINCO  = 35, 
        SESSENTA        = 60, 
        CEM             = 100
      };

      enum Niveis {
        FACIL   = 1,
        MEDIO   = 2,
        DIFICIL = 3
      };
      
      int chanceDeBomba;

      switch(campoMinado->nivel) {
        default     : chanceDeBomba = SESSENTA;       break;
        case FACIL  : chanceDeBomba = QUINZE;         break;
        case MEDIO  : chanceDeBomba = VINTE_E_CINCO;  break;
        case DIFICIL: chanceDeBomba = TRINTA_E_CINCO; break;
      }
      
      campoMinado->campo[i][j] = (char)(rand() % CEM <= chanceDeBomba )? BOMBA : VAZIO;
      
      if(campoMinado->campo[i][j] == BOMBA)
        campoMinado->bombas++;
      else
        campoMinado->jogadas++;
    }
  }

  if(!campoMinado->bombas) 
    criarCampoMinado(campoMinado);

  gerarDica(campoMinado);
}


void desenharTabuleiro(struct CampoMinado campoMinado) {

  system("clear");
  printf("\033[40;7m");
  switch(campoMinado.nivel) {
    case 1: printf("Nivel: \033[34;3m Facil | "); break;
    case 2: printf("Nivel: \033[32;3m Medio  | "); break;
    case 3: printf("Nivel: \033[31;3m Dificil  | "); break;
  }

  printf("Bombas: %d | Jogadas: %d \033[0;0m\n", campoMinado.bombas, campoMinado.jogadas);

  desenharCampoMinado(campoMinado);

  if( campoMinado.fimDoJogo && campoMinado.jogadas > 0)
    printf("\033[47;31;7m VOCÊ PERDEU! BOMBA EM (%d, %d)\033[0;0m\n", campoMinado.coordenada.i, campoMinado.coordenada.j);
  else if( !campoMinado.fimDoJogo && campoMinado.jogadas <= 0)
    printf("\033[42;1m VOCÊ GANHOU! \033[0;0m\n");
  else
    printf("\033[41;1m ULTIMA JOGADA: (%d, %d)\033[0;0m\n", campoMinado.coordenada.i, campoMinado.coordenada.j);
   
  printf("VOLTAR (0,0) | NOVO JOGO (9,9)\n");
  printf("COMANDO | POSICAO (linha, coluna): ");
}


void desenharCampoMinado(struct CampoMinado campoMinado) {

  for(int i = 0; i < MAX; i++) {
    if(i != 0 && i < MAX - 1) printf("%d", i);
    else printf("  ");    
  }

  printf("\n");
  
  for(int i = 0; i < MAX; i++) {
    
    if(i != 0 && i < MAX - 1) printf("%d", i);
    else printf(" ");  

    for(int j = 0; j < MAX; j++) {
     
      if( campoMinado.campo[i][j] == BOMBA && campoMinado.fimDoJogo) printf("\033[33;31;5m*\033[0;0m");
      else if( campoMinado.campo[i][j] == 21 ) printf("\033[1;34m\u2554\033[0;0m"); // "\u2554: ╔"
      else if( campoMinado.campo[i][j] == 22 ) printf("\033[1;34m\u2557\033[0;0m"); // "\u2557: ╗"
      else if( campoMinado.campo[i][j] == 23 ) printf("\033[1;34m\u255A\033[0;0m"); // "\u255A: ╚"
      else if( campoMinado.campo[i][j] == 24 ) printf("\033[1;34m\u255D\033[0;0m"); // "\u255D: ╝"
      else if( campoMinado.campo[i][j] == 25 ) printf("\033[1;34m\u2551\033[0;0m"); // "\u2551: ║"
      else if( campoMinado.campo[i][j] == 26 ) printf("\033[1;34m\u2550\033[0;0m"); // "\u2550: ═"
      else if( campoMinado.campo[i][j] >= VAZIO && campoMinado.campo[i][j] <= BOMBA && !campoMinado.fimDoJogo && !campoMinado.campoJogadas[i][j]) printf("\u2B25"); // "\u2B25: ⬥" 
      else printf("\033[1;33m%d\033[0;0m", campoMinado.campo[i][j]);
    }

    printf("\n");
  }
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


void obterComando(int *opcao, void (*template)(void *da), void *dados ) {
 
  do {
    
    int comando;
    
    if(template)
      template(dados);

    setbuf(stdin, NULL);
    scanf("%d", &comando);
    
    if(comando > 0 && comando < 4) {
      *opcao = comando;
      
      if(template)
        template(dados);

      printf("\n");
      break;
    }
    else {
      printf("\033[43;31mCOMANDO INVALIDO\033[0;0m\n");
      system("sleep .4");      
    } 
    
  } while(true);
}


void jogo(struct CampoMinado* campoMinado) {

  criarCampoMinado(campoMinado);
  
  struct Coordenada coordenada;

  do {
   
    desenharTabuleiro(*campoMinado);

    scanf("%d %d", &coordenada.i, &coordenada.j);
    setbuf(stdin, NULL);

    bool limiteLateralEsquerdo = coordenada.i > 0;
    bool limiteLateralDireito  = coordenada.i < MAX - 1;
    bool limiteAlturaSuperior  = coordenada.j > 0;
    bool limiteAlturaInferior  = coordenada.j < MAX - 1;

    if( limiteLateralEsquerdo && limiteLateralDireito &&
        limiteAlturaSuperior && limiteAlturaInferior && !campoMinado->fimDoJogo ) 
    {
      
      campoMinado->campoJogadas[coordenada.i][coordenada.j] = 1;
      campoMinado->coordenada.i = coordenada.i;
      campoMinado->coordenada.j = coordenada.j;
      
      bool encontrouBomba = campoMinado->campo[coordenada.i][coordenada.j] == BOMBA;

      if(encontrouBomba)
        campoMinado->fimDoJogo = !campoMinado->fimDoJogo;
      else
        campoMinado->jogadas--;
    }


    bool IforaDosLimite = (coordenada.i < 0 || coordenada.i >= MAX );
    bool JforaDosLimite = (coordenada.j < 0 || coordenada.j >= MAX );


    if( coordenada.i == 9 && coordenada.j == 9)
      criarCampoMinado(campoMinado);
    else if(coordenada.i == 0 && coordenada.j == 0)
      break;
    else if(IforaDosLimite || JforaDosLimite) {
      printf("\033[43;31mCOMANDO OU POSICAO INVALIDO\033[0;0m\n");
      system("sleep .5");
    }

  } while(campoMinado->jogadas != 0 || !campoMinado->fimDoJogo);
}

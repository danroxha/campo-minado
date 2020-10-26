#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10
#define BOMBA 9
#define VAZIO 0

struct CampoMinado
{
  char campo[MAX][MAX];
  int nivel;
  int bombas;
  int jogadas;
  bool fimDoJogo;

};


void criarCampoMinado(struct CampoMinado*);
void gerarDica(struct CampoMinado*);
void desenharCampoMinado(struct CampoMinado);
int calcularJogadasDisponiveis(char [MAX][MAX]);


int main(){

  struct CampoMinado campoMinado;
    campoMinado.nivel = 3;
    campoMinado.fimDoJogo = true;
  
  criarCampoMinado(&campoMinado);
  gerarDica(&campoMinado);
  desenharCampoMinado(campoMinado);
}


void criarCampoMinado(struct CampoMinado* campoMinado) {
  
  srand(clock());
  
  campoMinado->bombas = 0;
  
  for(int i = 0; i < MAX; i++) {
    for(int j = 0; j < MAX; j++) {
      
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
        DEZ             = 10, 
        VINTE           = 20, 
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
        default     : chanceDeBomba = DEZ;            break;
        case FACIL  : chanceDeBomba = VINTE;          break;
        case MEDIO  : chanceDeBomba = TRINTA_E_CINCO; break;
        case DIFICIL: chanceDeBomba = SESSENTA;       break;
      }
      
      campoMinado->campo[i][j] = (char)(rand() % CEM <= chanceDeBomba )? BOMBA : VAZIO;
      
      if(campoMinado->campo[i][j] == BOMBA)
        campoMinado->bombas++;
    }
  }

  if(!campoMinado->bombas) 
    criarCampoMinado(campoMinado);
  else
    campoMinado->jogadas = calcularJogadasDisponiveis(campoMinado->campo);

}


void desenharCampoMinado(struct CampoMinado campoMinado) {

  system("clear");
  printf("\033[40;7m");
  switch(campoMinado.nivel) {
    default: printf("Nivel: \033[34;3m Facil | "); break;
    case 1: printf("Nivel: \033[32;3m Medio  | "); break;
    case 2: printf("Nivel: \033[33;3m Dificil  | "); break;
    case 3: printf("Nivel: \033[31;3m Muito Dificil  | "); break;
  }

  printf("Bombas: %d | Jogadas: %d \033[0;0m\n", campoMinado.bombas, campoMinado.jogadas);
  printf("  12345678\n");
  
  for(int i = 0; i < MAX; i++) {
    if(i != 0 && i < MAX - 1) printf("%d",i);
    else printf(" ");  

    for(int j = 0; j < MAX; j++) {
     
      if( campoMinado.campo[i][j] == BOMBA && campoMinado.fimDoJogo) printf("\033[33;31;5m*\033[0;0m");
      else if( campoMinado.campo[i][j] == 21 ) printf("\033[1;34m\u2554\033[0;0m"); // "\u2554: ╔"
      else if( campoMinado.campo[i][j] == 22 ) printf("\033[1;34m\u2557\033[0;0m"); // "\u2557: ╗"
      else if( campoMinado.campo[i][j] == 23 ) printf("\033[1;34m\u255A\033[0;0m"); // "\u255A: ╚"
      else if( campoMinado.campo[i][j] == 24 ) printf("\033[1;34m\u255D\033[0;0m"); // "\u255D: ╝"
      else if( campoMinado.campo[i][j] == 25 ) printf("\033[1;34m\u2551\033[0;0m"); // "\u2551: ║"
      else if( campoMinado.campo[i][j] == 26 ) printf("\033[1;34m\u2550\033[0;0m"); // "\u2550: ═"
      else if( campoMinado.campo[i][j] >= VAZIO && campoMinado.campo[i][j] <= BOMBA && !campoMinado.fimDoJogo ) printf("\u2B25"); // "\u2B25: ⬥" 
      else printf("\033[1;33m%d\033[0;0m", campoMinado.campo[i][j]);
    }

    printf("\n");
  }

  if( campoMinado.fimDoJogo && campoMinado.jogadas > 0)
    printf("\033[47;31;7m VOCÊ PERDEU! \033[0;0m\n");
    // printf("\033[47;6;31;7m VOCÊ PERDEU! \033[0;0m\n");

    // printf("\033[41;1m ");
  
  // printf("\033[43;31m VOCÊ PERDEU! \033[0;0m\n");
  // printf("\033[42;1m VOCÊ GANHOU! \033[0;0m\n");
  // printf("\n");
  
  printf("SAIR (0,0) | NOVO JOGO (9,9)\n");
  printf("COMANDO | POSICAO (x, y): ");
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


int calcularJogadasDisponiveis(char campoMinado[MAX][MAX]) {
  
  int contador = 0;
  
  for(int i = 1;  i < MAX - 1; i++) {
    for(int j = 1;  j < MAX - 1; j++) {
      if(campoMinado[i][j] >= VAZIO && campoMinado[i][j] < BOMBA)
        contador++;
    }
  }
    
  return contador;
}
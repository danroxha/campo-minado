#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

struct CampoMinado
{
  char campo[MAX][MAX];
  int nivel;
  int numeroDeBombas;
  int jogadasRestantes;
  bool emJogo;

};


int nivel = 3;
int numeroDeBombas = 0;
int jogadasRestantes = 0;
bool perdeu = true;


void gerarDica(char [MAX][MAX]);
void desenharCampoMinado(char [MAX][MAX], unsigned);
void criarCampoMinado(char [MAX][MAX], unsigned );
int calcularJogadasDisponiveis(char [MAX][MAX]);


int main(){
  char campoMinado[MAX][MAX] = {0};
  
  criarCampoMinado(campoMinado, nivel);
  gerarDica(campoMinado);
  desenharCampoMinado(campoMinado, nivel);
}


void criarCampoMinado(char campoMinado[MAX][MAX], unsigned nivel) {
  
  srand(clock());

  int quantidadeDeBombas = 0;
  
  for(int i = 0; i < MAX; i++) {
    for(int j = 0; j < MAX; j++) {
      
      bool primeiraLinha   = i == 0;
      bool ultimaLinha     = i == MAX - 1;
      bool limiteEsquerda  = j == 0;
      bool limiteDireira   = j == MAX - 1;

      if(primeiraLinha || ultimaLinha || limiteEsquerda || limiteDireira) {
       
        if(primeiraLinha && limiteEsquerda )       campoMinado[i][j] = 21; // "\u2554: ╔"
        else if( primeiraLinha && limiteDireira )  campoMinado[i][j] = 22; // "\u2557: ╗"
        else if( ultimaLinha && limiteEsquerda )   campoMinado[i][j] = 23; // "\u255A: ╚"
        else if( ultimaLinha && limiteDireira )    campoMinado[i][j] = 24; // "\u255A: ╝"
        else if( limiteEsquerda || limiteDireira ) campoMinado[i][j] = 25; // "\u2551: ║"
        else if( primeiraLinha || ultimaLinha )    campoMinado[i][j] = 26; // "\u2550: ═"
        continue;
      
      }
        
      enum Porcentagem {
        DEZ = 10, VINTE = 20, TRINTA_E_CINCO = 35, SESSENTA = 60, CEM = 100,
      };
      
      int chanceDeBomba;

      switch(nivel) {
        default: chanceDeBomba  = DEZ;            break;
        case 1: chanceDeBomba   = VINTE;          break;
        case 2: chanceDeBomba   = TRINTA_E_CINCO; break;
        case 3: chanceDeBomba   = SESSENTA;       break;
      }
      
      campoMinado[i][j] = (char)(rand() % CEM <= chanceDeBomba )? 9 : 0;
      if(campoMinado[i][j] == 9 )
        quantidadeDeBombas++;


    }
  }

  if(!quantidadeDeBombas) criarCampoMinado(campoMinado, nivel);

  numeroDeBombas = quantidadeDeBombas;
}


void desenharCampoMinado(char campoMinado[MAX][MAX], unsigned nivel) {

  system("clear");
  switch(nivel) {
    default: printf("Nivel: Facil | "); break;
    case 1: printf("Nivel: Medio | "); break;
    case 2: printf("Nivel: Dificil | "); break;
    case 3: printf("Nivel: Muito Dificil | "); break;
  }

  printf("Bombas: %d | Jogadas: %d\n", numeroDeBombas, calcularJogadasDisponiveis(campoMinado));
  printf("  12345678\n");
  
  for(int i = 0; i < MAX; i++) {
    if(i != 0 && i < MAX - 1) printf("%d",i);
    else printf(" ");  

    for(int j = 0; j < MAX; j++) {
     
      if( campoMinado[i][j] == 9 && perdeu) printf("\033[1;31m*\033[0;0m");
      else if( campoMinado[i][j] == 21 ) printf("\033[1;34m\u2554\033[0;0m"); // "\u2554: ╔"
      else if( campoMinado[i][j] == 22 ) printf("\033[1;34m\u2557\033[0;0m"); // "\u2557: ╗"
      else if( campoMinado[i][j] == 23 ) printf("\033[1;34m\u255A\033[0;0m"); // "\u255A: ╚"
      else if( campoMinado[i][j] == 24 ) printf("\033[1;34m\u255D\033[0;0m"); // "\u255D: ╝"
      else if( campoMinado[i][j] == 25 ) printf("\033[1;34m\u2551\033[0;0m"); // "\u2551: ║"
      else if( campoMinado[i][j] == 26 ) printf("\033[1;34m\u2550\033[0;0m"); // "\u2550: ═"
      else if( campoMinado[i][j] >= 0 && campoMinado[i][j] <= 9 && !perdeu ) printf("\u2B25"); // "\u2B25: ⬥" 
      else printf("\033[1;33m%d\033[0;0m", campoMinado[i][j]);
    }

    printf("\n");
  }

  if( perdeu )
    printf("\033[41;1m VOCÊ PERDEU! \033[0;0m\n");
  
  // printf("\033[43;31m VOCÊ PERDEU! \033[0;0m\n");
  // printf("\033[42;1m VOCÊ GANHOU! \033[0;0m\n");
    // printf("\n");
  printf("SAIR (0,0) | NOVO JOGO (9,9)\n");
  printf("VERIFICAR A POSICAO (x, y): ");
}


void gerarDica(char campoMinado[MAX][MAX]) {
  
  for(int i = 1; i < MAX - 1; i++) {
    for(int j = 1; j < MAX - 1; j++) {
    
      if(campoMinado[i][j] == 9) {
        // Adicionar +1 ao redor das bombas
        for(int y = i - 1; y < i + 2; y++) {
          
          bool limiteAlturaSuperior = y < 1; 
          bool limiteAlturaInferior = y > MAX - 2;

          if(limiteAlturaSuperior) y = 1;
          if(limiteAlturaInferior) continue;

          for(int x = j - 1; x < j + 2; x++) { 
          
            bool limiteLateralEsquerdo = x < 1; 
            bool limiteLateralDireito  = x > MAX - 2;

            if(limiteLateralEsquerdo) x = 1;
            if(limiteLateralDireito ) continue;
            

            bool naoEhUmaBomba = campoMinado[y][x] != 9;
            if(naoEhUmaBomba)
              campoMinado[y][x]++;

          }
        }
      }
    }
  }
}


int calcularJogadasDisponiveis(char campoMinado[MAX][MAX]) {
  
  int contador = 0;
  
  for(int i = 1;  i < MAX - 2; i++) {
    for(int j = 1;  j < MAX - 2; j++) {
      if(campoMinado[i][j] != 9)
        contador++;
    }
  }
    
  return contador;
}
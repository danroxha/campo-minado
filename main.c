#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define parseInt(caracter) (caracter >= 48 && caracter <= 57)? caracter - 48: caracter


#define MAX 10
#define BOMBA 9
#define VAZIO 0

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

int calcularJogadasDisponiveis(char [MAX][MAX]);
void criarCampoMinado(struct CampoMinado*);
void gerarDica(struct CampoMinado*);
void jogo(struct CampoMinado* );
void desenharCampoMinado(struct CampoMinado);
void introducao();
void bannerMenu(void *);
void bannerNivel(void *);
void obterComando(int *opcao, void (*template)(void *), void *dados);


int main(){

  struct CampoMinado campoMinado;
    campoMinado.nivel = 1;


  int opcao;
  introducao(); 

  do {
    
    obterComando(&opcao, bannerMenu, NULL);

    switch(opcao){
    case 1: 
      jogo(&campoMinado);
      break;
    case 2:
      obterComando(&campoMinado.nivel, bannerNivel, (void*) &campoMinado);
      break;
    case 3:
      exit(0);
    }
  }

  while(opcao != 0);
  
}


void criarCampoMinado(struct CampoMinado* campoMinado) {
  
  srand(clock());
  
  campoMinado->bombas = 0;
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

  gerarDica(campoMinado);
}


void desenharCampoMinado(struct CampoMinado campoMinado) {

  system("clear");
  printf("\033[40;7m");
  switch(campoMinado.nivel) {
    case 1: printf("Nivel: \033[34;3m Facil | "); break;
    case 2: printf("Nivel: \033[32;3m Medio  | "); break;
    case 3: printf("Nivel: \033[31;3m Dificil  | "); break;
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
      else if( campoMinado.campo[i][j] >= VAZIO && campoMinado.campo[i][j] <= BOMBA && !campoMinado.fimDoJogo && !campoMinado.campoJogadas[i][j]) printf("\u2B25"); // "\u2B25: ⬥" 
      else printf("\033[1;33m%d\033[0;0m", campoMinado.campo[i][j]);
    }

    printf("\n");
  }

  if( campoMinado.fimDoJogo && campoMinado.jogadas > 0)
    printf("\033[47;31;7m VOCÊ PERDEU! BOMBA EM (%d, %d)\033[0;0m\n", campoMinado.coordenada.i, campoMinado.coordenada.j);
  else
    printf("\033[41;1m ULTIMA JOGADA: (%d, %d)\033[0;0m\n", campoMinado.coordenada.i, campoMinado.coordenada.j);
    // printf("\033[47;6;31;7m VOCÊ PERDEU! \033[0;0m\n");

    // printf("\033[41;1m ");
  
  // printf("\033[43;31m VOCÊ PERDEU! BOMBA EM (%d, %d)\033[0;0m\n");
  // printf("\033[42;1m VOCÊ GANHOU! \033[0;0m\n");
  // printf("\n");
  
  printf("SAIR (0,0) | NOVO JOGO (9,9)\n");
  printf("COMANDO | POSICAO (linha, coluna): ");
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


void introducao(){

  system("clear");
  
  printf("::::::'######:::::'###::::'##::::'##:'########:::'#######::::::\n");
  printf(":::::'##... ##:::'## ##::: ###::'###: ##.... ##:'##.... ##:::::\n");
  printf("::::: ##:::..:::'##:. ##:: ####'####: ##:::: ##: ##:::: ##:::::\n");
  printf("::::: ##:::::::'##:::. ##: ## ### ##: ########:: ##:::: ##:::::\n");
  printf("::::: ##::::::: #########: ##. #: ##: ##.....::: ##:::: ##:::::\n");
  printf("::::: ##::: ##: ##.... ##: ##:.:: ##: ##:::::::: ##:::: ##:::::\n");
  printf(":::::. ######:: ##:::: ##: ##:::: ##: ##::::::::. #######::::::\n");
  printf("::::::......:::..:::::..::..:::::..::..::::::::::.......:::::::\n");
  
  printf("\033[33;33;5m");
  printf("::'##::::'##:'####:'##::: ##::::'###::::'########:::'#######:::\n");
  printf(":: ###::'###:. ##:: ###:: ##:::'## ##::: ##.... ##:'##.... ##::\n");
  printf(":: ####'####:: ##:: ####: ##::'##:. ##:: ##:::: ##: ##:::: ##::\n");
  printf(":: ## ### ##:: ##:: ## ## ##:'##:::. ##: ##:::: ##: ##:::: ##::\n");
  printf(":: ##. #: ##:: ##:: ##. ####: #########: ##:::: ##: ##:::: ##::\n");
  printf(":: ##:.:: ##:: ##:: ##:. ###: ##.... ##: ##:::: ##: ##:::: ##::\n");
  printf(":: ##:::: ##:'####: ##::. ##: ##:::: ##: ########::. #######:::\n");
  printf("::..:::::..::....::..::::..::..:::::..::........::::.......::::\n");
  printf("\033[0;0m\n");
  
  system("sleep 3");
}


void bannerMenu(void *dados) {
  system("clear");
  printf("   ___                              \n");
  printf("  / __|  __ _   _ __    _ __   ___  \n");
  printf(" | (__  / _` | | '  \\  | '_ \\ / _ \\ \n");
  printf("  \\___| \\__,_| |_|_|_| | .__/ \\___/ \n");
  printf("                       |_|          \n");
  printf("          _                    _        \n");
  printf("  _ __   (_)  _ _    __ _   __| |  ___  \n");
  printf(" | '  \\  | | | ' \\  / _` | / _` | / _ \\ \n");
  printf(" |_|_|_| |_| |_||_| \\__,_| \\__,_| \\___/ \n");
                                         

  printf("\n================ Menu =================\n");
  printf("=          1 - Novo Jogo              =\n");
  printf("=          2 - Selecionar Nivel       =\n");
  printf("=          3 - Sair                   =\n");
  printf("=======================================\n");
  printf("Opcao: ");

}


void bannerNivel(void *dados) {

  struct CampoMinado campoMinado = *(struct CampoMinado*)dados;
  
  system("clear");
  switch(campoMinado.nivel) {
    case 1: printf("\033[33;34m Facil  "); break;
    case 2: printf("\033[33;32m Medio  "); break;
    case 3: printf("\033[33;31m Dificil"); break;
  }
  
  printf("   ▄   ▄█     ▄   ▄███▄   █     \n");
  printf("    █  ██      █  █▀   ▀  █     \n");
  printf("██   █ ██ █     █ ██▄▄    █     \n");
  printf("█ █  █ ▐█  █    █ █▄   ▄▀ ███▄  \n");
  printf("█  █ █  ▐   █  █  ▀███▀       ▀ \n");
  printf("█   ██       █▐                 \n");
  printf("             ▐                  \n");
  printf("\033[0;0m\n");
  printf("================================\n");
  printf("=          1 - Facil           =\n");
  printf("=          2 - Medio           =\n");
  printf("=          3 - Dificil         =\n");
  printf("================================\n");

  printf("Selecionar: ");

}


void obterComando(int *opcao, void (*template)(void *da), void *dados ) {
 
  do {
    
    char comando;
    
    if(template)
      template(dados);

    fflush(stdin);    
    gets(&comando);
    printf("\n");

    *opcao = parseInt(comando);
    
    if(*opcao > 0 && *opcao < 4 )
      break;
  
  } while(true);
}


void jogo(struct CampoMinado* campoMinado){

  criarCampoMinado(campoMinado);
  
  struct Coordenada coordenada;

  do {
   
    desenharCampoMinado(*campoMinado);

    scanf("%d %d", &coordenada.i, &coordenada.j);

    bool limiteLateralEsquerdo = coordenada.i > 0;
    bool limiteLateralDireito  = coordenada.i < MAX - 1;
    bool limiteAlturaSuperior  = coordenada.j > 0;
    bool limiteAlturaInferior  = coordenada.j < MAX - 1;

    if(limiteLateralEsquerdo && limiteLateralDireito && limiteAlturaSuperior && limiteAlturaInferior ) {
      campoMinado->campoJogadas[coordenada.i][coordenada.j] = 1;

      bool encontrouBomba = campoMinado->campo[coordenada.i][coordenada.j] == BOMBA;

      if(encontrouBomba)
        campoMinado->fimDoJogo = !campoMinado->fimDoJogo;
      else
        campoMinado->jogadas--;
    }

    if( coordenada.i == 9 && coordenada.j == 9)
      criarCampoMinado(campoMinado);
    else if( coordenada.i == 0 && coordenada.j == 0)
      break;

  } while(campoMinado->jogadas != 0 || !campoMinado->fimDoJogo);
  
  // system("sleep 5");
}
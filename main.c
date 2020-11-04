
#include <stdio.h>
#include <stdbool.h>


#include "./src/campominado.h"


void jogo(struct CampoMinado* );


int main(){

  struct CampoMinado campoMinado;
    campoMinado.nivel = 1;

  enum OPCOES {
    INICIAR_JOGO = 1, SELECIONAR_NIVEL = 2, SAIR = 3
  };

  int opcao;

  bannerIntroducao(); 

  do {
    
    selecionarOpcao(&opcao, bannerMenu, NULL);

    switch(opcao) {
      case INICIAR_JOGO: 
        jogo(&campoMinado);
        break;
      case SELECIONAR_NIVEL:
        selecionarOpcao(&campoMinado.nivel, bannerNivel, (void*) &campoMinado);
        break;
    }

    if( opcao == SAIR)
      bannerSair();
  }

  while(opcao != SAIR);
  
}


void jogo(struct CampoMinado* campoMinado) {

  gerarCampoMinado(campoMinado);
  
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
      bool encontrouVazio = campoMinado->campo[coordenada.i][coordenada.j] == VAZIO;

      if(encontrouVazio)
        revelarCasasVazias(campoMinado, coordenada);

      if(encontrouBomba)
        campoMinado->fimDoJogo = !campoMinado->fimDoJogo;
      else
        campoMinado->jogadas--;
    }


    bool IforaDosLimite = (coordenada.i < 0 || coordenada.i >= MAX );
    bool JforaDosLimite = (coordenada.j < 0 || coordenada.j >= MAX );

    struct Coordenada menu     = {0, 0};
    struct Coordenada novoJogo = {9, 9};

    bool iniciarNovoJogo = coordenada.i == novoJogo.i && coordenada.j == novoJogo.j;
    bool menuPrincipal   = coordenada.i == menu.i && coordenada.j == menu.j;

    if(iniciarNovoJogo)
      gerarCampoMinado(campoMinado);
    else if(menuPrincipal)
      break;
    else if(IforaDosLimite || JforaDosLimite) {
      printf("\033[43;31mCOMANDO OU POSICAO INVALIDO\033[0;0m\n");
      system("sleep .5");
    }

    campoMinado->jogadas = verificarQuantidadesDeJogadas(*campoMinado);

  } while(campoMinado->jogadas != 0 || !campoMinado->fimDoJogo);
}

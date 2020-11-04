#ifndef __C_MINADO_INPUT_H__
#define __C_MINADO_INPUT_H__


#include <stdio.h>
#include <stdlib.h>


void selecionarOpcao(int *opcao, void (*)(void *), void *);


void selecionarOpcao(int *opcao, void (*template)(void *da), void *dados ) {
 
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

#endif //__C_MINADO_INPUT_H__
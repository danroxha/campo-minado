#ifndef __C_MINADO_BANNER_H__
#define __C_MINADO_BANNER_H__

#include <stdio.h>
#include <stdlib.h>
#include "type.h"


void bannerIntroducao(void) {

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
  
  system("sleep 1.5");
}


void bannerMenu(void *dados) {
  system("clear");
  printf("\033[33;33;5m");
  printf("   ___                              \n");
  printf("  / __|  __ _   _ __    _ __   ___  \n");
  printf(" | (__  / _` | | '  \\  | '_ \\ / _ \\ \n");
  printf("  \\___| \\__,_| |_|_|_| | .__/ \\___/ \n");
  printf("                       |_|          \n");
  printf("          _                    _        \n");
  printf("  _ __   (_)  _ _    __ _   __| |  ___  \n");
  printf(" | '  \\  | | | ' \\  / _` | / _` | / _ \\ \n");
  printf(" |_|_|_| |_| |_||_| \\__,_| \\__,_| \\___/ \n");
  printf("\033[0;0m\n");                                       
  printf("\n================ Menu =================\n");
  printf("=          1 - Novo Jogo              =\n");
  printf("=          2 - Selecionar Nivel       =\n");
  printf("=          \033[33;31m3 - Sair\033[0;0m                   =\n");
  printf("====================== Versao: %s ==\n", VERSAO);
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
  printf("====================================\n");
  printf("=            \033[33;34m1 - Facil   \033[0;0m          =\n");
  printf("=            \033[33;32m2 - Medio   \033[0;0m          =\n");
  printf("=            \033[33;31m3 - Dificil \033[0;0m          =\n");
  printf("====================================\n");

  printf("Selecionar: ");
  system("sleep .3");   

}


void bannerSair(void) {
  system("clear");
  printf("\n\n\n\n");
  printf("     ,--\033[1;33;5m.!,\033[0;0m    Desenvolvido por \n");
  printf("  __/   \033[1;33;5m-\033[0;0m\033[31;1m*\033[0;0m\033[1;33;5m-\033[0;0m     * Daniel Rocha\n");
  printf("\033[30;30;1m,d08b.\033[0;0m  \033[1;33;5m'|`\033[0;0m     * Tadeu Viegas \n");
  printf("\033[30;30;1m0088MM\033[0;0m         \n");
  printf("\033[30;30;1m`9MMP'\033[0;0m        2020\n");
  printf("\n\n\n\n");
  system("sleep 1.5");  
}


#endif // __C_MINADO_BANNER_H__
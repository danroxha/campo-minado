#ifndef __C_MINADO_BANNER_H__
#define __C_MINADO_BANNER_H__

#include <stdio.h>
#include <stdlib.h>
#include "type.h"


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
  printf("=            1 - Facil             =\n");
  printf("=            2 - Medio             =\n");
  printf("=            3 - Dificil           =\n");
  printf("====================================\n");

  printf("Selecionar: ");

}


#endif // __C_MINADO_BANNER_H__
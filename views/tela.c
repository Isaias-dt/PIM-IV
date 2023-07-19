#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <windows.h>
#include "../headers/services.h"

void showHead()
{
    system("cls || clear");
    printf("#############################\n");
    printf("    MONITORAMENTO COVID-19   \n");
    printf("#############################\n\n");
}

void showHeadRegPac()
{
    printf("\n==========================\n");
    printf("   CADASTRO DE PACIENTE:");
    printf("\n==========================\n\n");
}

void showHeadCadUser()
{
    printf("==========================\n");
    printf("   CADASTRO DE USUÁRIO:");
    printf("\n==========================\n\n");
}

void systemPause()
{
    printf("\n");
    printf("Pressione qualquer tecla para continuar. . .");
    fflush(stdin);
    getchar();
}

void menuHome()
{
    printf("\n\n");
    printf("|_HOME_|\n\n");
    printf("| Entrar.............[1] |\n");
    printf("| Registrar Usuário..[2] |\n");
    printf("| Sair...............[0] |\n");
    printf("\n\n");
}

void cadComSucesso(char *alguem)
{
    printf("[---> %s cadastrado com Sucesso <---]", alguem);
}

void menuUsuario(char *user)
{
    showHead();
    printf("SEJA BEM VINDO |_%s_|\n", user);
    printf("\n==========================\n");
    printf("        MENU USUÁRIO       ");
    printf("\n==========================\n");

    if(strcmp(user, "root") == 0)
    {
        printf("\n\n");
        printf("| Registrar Paciente.[1] |\n");
        printf("| Registrar Usuário..[2] |\n");
        printf("| Voltar............[-1] |\n");
        printf("| Sair...............[0] |\n");
        printf("\n\n");
    }
    else
    {
        printf("\n\n");
        printf("| Registrar Paciente.[1] |\n");
        printf("| Voltar ...........[-1] |\n");
        printf("| Sair ..............[0] |\n");
        printf("\n\n");
    }
}

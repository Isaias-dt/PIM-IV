#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>
#include "../headers/services.h"

void popUsers()
{
    if(existeEsteArq(PATH_USER_DATABASE) == 0)
    {
        FILE *ponteiroArquivo;
        ponteiroArquivo=(fopen(PATH_USER_DATABASE, "a"));
        fprintf(ponteiroArquivo, "Nome Completo,Email,Usuario,Senha,Data de Nascimento,CPF,Telefone,CEP,Rua,Casa,Bairro,Cidade,Estado\n");
        fclose(ponteiroArquivo);
    }
}

void popComorbidade()
{
    if(existeEsteArq(PATH_COM_DATABASE) == 0)
    {
        FILE *ponteiroArquivo;
        ponteiroArquivo=(fopen(PATH_COM_DATABASE, "a"));
        fprintf(ponteiroArquivo, "Lista de Comorbidades\n");
        fprintf(ponteiroArquivo, "Diabetes\n");
        fprintf(ponteiroArquivo, "Obesidade\n");
        fprintf(ponteiroArquivo, "Hipertensão\n");
        fprintf(ponteiroArquivo, "Tuberculose");
        fclose(ponteiroArquivo);
    }
}

void popPaciente()
{
    if(existeEsteArq(PATH_PACIENTES_DATABASE) == 0)
    {
        FILE *ponteiroArquivo;
        ponteiroArquivo=(fopen(PATH_PACIENTES_DATABASE, "a"));
        fprintf(ponteiroArquivo, "Nome Completo,Email,Data de Nascimento,CPF,Telefone,CEP,Data do Diagnostico,Rua,Casa,Bairro,Cidade,Estado,Comorbidade\n");
        fclose(ponteiroArquivo);
    }
}

void popGrupoRisco()
{
    if(existeEsteArq(PATH_GP_RISCO_DATABASE) == 0)
    {
        FILE *ponteiroArquivo;
        ponteiroArquivo=(fopen(PATH_GP_RISCO_DATABASE, "a"));
        fprintf(ponteiroArquivo, "CPF,CEP,Idade\n");
        fclose(ponteiroArquivo);
    }
}

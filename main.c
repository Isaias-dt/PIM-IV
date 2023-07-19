#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include "headers/services.h"

int main(void)
{
    setlocale(LC_ALL, "Portuguese");

    char login[50];
    char *senha, *path;
    int logado = 0;
    int op = UNDEFINED, qtsCp;

    // Startup (configurações iniciais)
    startup();

    // Menu principal (home):
    while(1)
    {
        showHead();
        menuHome();

        printf("-> ");
        scanf("%i", &op);

        // Opção 1 menu principal
        if(op == 1)
        {

            // Entrada do usuário
            while(1)
            {
                showHead();
                path = PATH_USER_DATABASE;

                printf("\nENTRE COM O USUÁRIO DO SISTEMA:\n\n");
                setbuf(stdin, NULL);
                printf("LOGIN: ");
                scanf("%s", &login);
                printf("SENHA: ");
                senha = ocultaSenha();

                char **lUser = lista(path, "Usuario", login);
                int indice = indiceDoCampo(path, "Senha");
                qtsCp = qtsCampo(path);

                if(lUser != NULL && strcmp(lUser[indice], senha) == 0)
                {

                    // Menu usuário
                    while(1)
                    {
                        showHead();
                        menuUsuario(login);
                        setbuf(stdin, NULL);
                        op = UNDEFINED;

                        printf("-> ");
                        scanf("%i", &op);

                        // Opção 1 menu usuário
                        if(op == 1)
                        {
                            if(CadastraPaciente() == 0)
                            {
                                continue;
                            }
                            systemPause();
                            continue;
                        }

                        // Opção 0 menu usuário sair do programa.
                        else if(op == 0)
                        {
                            desalocaMat(lUser, qtsCp);
                            exit(0);
                        }

                        // Opção -1 menu usuário voltar ao menu principal.
                        else if(op == -1)
                        {
                            break;
                        }

                        // Caso nenhuma opção válida seja digitada volta a tela de menu usuário.
                        else
                        {
                            printf("Opcão inválida!");
                            systemPause();
                            continue;
                        }
                    }

                }
                else
                {
                    printf("\n\nUsuário inválido!\n");
                    desalocaMat(lUser, qtsCp);
                    systemPause();
                    continue;
                }
                desalocaMat(lUser, qtsCp);
                if(op == -1)
                {
                    op = UNDEFINED;
                    break;
                }
            }
        }

        // Opção 2 menu principal
        else if(op == 2)
        {
            showHead();
            if(cadastraUsuario() == 0)
            {
                continue;
            }
            systemPause();
            continue;
        }

        // Opção 3 menu principal
        else if(op == 0)
        {
            exit(0);
        }

        // Caso nenhuma opção válida seja digitada volta a tela de menu principal.
        else
        {
            printf("Opção inválida!");
            setbuf(stdin, NULL);
            systemPause();
            continue;
        }
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>
#include <unistd.h>
#include "../headers/services.h"

// Retorna o index do caracter passado por parametro que esta na string, caso não existir retorna -1.
int indexOf(char *str, char caracter)
{
    int i;
    int t = strlen(str);

    for(i = 0; i < t; i++)
    {
        if(str[i] == caracter)
        {
            return i;
        }
    }
    return -1;
}

// Verifica se o arquivo existe
int existeEsteArq(char caminho[])
{
    int error = access(caminho, F_OK);
    return (error == 0 ? 1 : 0);
}

// Oculta a senha digitada
char* ocultaSenha()
{
    char *buffer;
    int pos = 0;
    char c;
    do
    {
        c = getch();

        if(isprint(c))
        {
            buffer[ pos++ ] = c;
            printf("%c", '*');
        }
        else if(c == 8 && pos)
        {
            buffer[ pos-- ] = '\0';
            printf("%s", "\b \b");
        }
    }
    while(c != 13);

    return buffer;
}

// busca a lista de comorbidades na base de dados.
char** listaComorbidade()
{
    char *path = PATH_COM_DATABASE, linha[SIZE];
    FILE *pontArq;
    pontArq = fopen(path, "r");
    char **mat = alocaMat(4, SIZE);
    int pulaCabecalho = 0, count = 0;

    while(fgets(linha, 200, pontArq) != NULL)
    {
        if(pulaCabecalho == 0)
        {
            pulaCabecalho = 1;
            continue;
        }
        strcpy(mat[count], strtok(linha, "\n"));
        count++;
    }
    fclose(pontArq);
    return mat;
}

// Cadastra o usuario.
int cadastraUsuario()
{
    Usuario us;
    char confirmaCad;

    setbuf(stdin, NULL);
    showHeadCadUser();

    do
    {
        printf("Nome Completo: ");
        scanf(" %50[^\n]s", us.nomeCompleto);
        setbuf(stdin, NULL);
    }
    while(!validaNome(us.nomeCompleto));

    do
    {
        printf("Email: ");
        scanf(" %50[^\n]s", us.email);
        setbuf(stdin, NULL);
    }
    while(!validaEmail(us.email, PATH_USER_DATABASE));

    do
    {
        printf("CPF: ");
        scanf(" %12[^\n]s", us.cpf);
        setbuf(stdin, NULL);
    }
    while(!validaCPF(us.cpf, PATH_USER_DATABASE));

    do
    {
        printf("DDD + Telefone: ");
        scanf(" %12[^\n]s", us.telefone);
        setbuf(stdin, NULL);
    }
    while(!validaTel(us.telefone));

    printf("\n[--------USUÁRIO--------]\n");
    do
    {
        printf("Nome de usuário: ");
        scanf(" %30[^\n]s", us.nomeUsuario);
        setbuf(stdin, NULL);
    }
    while(!validaUs(us.nomeUsuario));

    printf("Senha: ");
    scanf(" %50[^\n]s", us.senha);

    printf("\n[---DATA DE NASCIMENTO---]\n");

    printf("\nDia: ");
    scanf(" %i", &us.DataNasc.dia);

    printf("Mês: ");
    scanf(" %lld", &us.DataNasc.mes);

    printf("Ano: ");
    scanf(" %i", &us.DataNasc.ano);


    printf("\n\n[--------ENDEREÇO--------]\n\n");

    do
    {
        printf("CEP: ");
        scanf(" %9[^\n]s", us.End.cep);
        setbuf(stdin, NULL);
    }
    while(!validaCEP(us.End.cep));

    do
    {
        printf("Rua: ");
        scanf(" %30[^\n]s", us.End.rua);
        setbuf(stdin, NULL);
    }
    while(!validaRua(us.End.rua));

    do
    {
        printf("Casa: ");
        scanf(" %i", &us.End.casa);
        setbuf(stdin, NULL);
    }
    while(!validaNumCasa(us.End.casa));

    printf("Bairro: ");
    scanf(" %50[^\n]s", us.End.bairro);

    printf("Cidade: ");
    scanf(" %50[^\n]s", us.End.cidade);

    printf("Estado: ");
    scanf(" %50[^\n]s", us.End.estado);
    setbuf(stdin, NULL);

    showUsuario(us);

    printf("\nDeseja salvar? (s/n)");
    do
    {
        printf("\n-> ");
        scanf(" %c", &confirmaCad);
    }
    while(confirmaCad != 's' && confirmaCad != 'n');

    if(confirmaCad == 's')
    {
        if(registraUsuario(&us) > 0)
        {
            printf("\nCadastrado com Sucesso!\n");
            return 1;
        }
        else
        {
            printf("\n\nNão foi possivel cadastrar!\n");
            exit(0);
        }
    }
    printf("\nCadastro não confirmado!\n");
    return 0;
}

// Cadastrar Paciente
int CadastraPaciente()
{
    Paciente pac;
    char risco, confirmaCad;
    int idade;
    char op;

    time_t segundos;
    time(&segundos);
    pac.DataDiag = localtime(&segundos);
    int anoAtual = pac.DataDiag->tm_year + 1900;

    showHeadRegPac();
    do
    {
        printf("Nome Completo: ");
        scanf(" %30[^\n]s", &pac.nomeCompleto);
        setbuf(stdin, NULL);
    }
    while(!validaNome(pac.nomeCompleto));

    do
    {
        printf("Email: ");
        scanf(" %30[^\n]s", pac.email);
        setbuf(stdin, NULL);
    }
    while(!validaEmail(pac.email, PATH_PACIENTES_DATABASE));

    do
    {
        printf("CPF: ");
        scanf(" %12[^\n]s", pac.cpf);
        setbuf(stdin, NULL);
    }
    while(!validaCPF(pac.cpf, PATH_PACIENTES_DATABASE));

    do
    {
        printf("DDD + Telefone: ");
        scanf(" %12[^\n]s", pac.telefone);
        setbuf(stdin, NULL);
    }
    while(!validaTel(pac.telefone));

    printf("\n[---DATA DE NASCIMENTO---]\n");

    printf("\nDia: ");
    scanf(" %i", &pac.DataNasc.dia);

    printf("Mês: ");
    scanf(" %lld", &pac.DataNasc.mes);

    printf("Ano: ");
    scanf(" %i", &pac.DataNasc.ano);

    printf("\n[---------ENDEREÇO---------]\n");

    do
    {
        printf("CEP: ");
        scanf(" %30[^\n]s", pac.End.cep);
        setbuf(stdin, NULL);
    }
    while(!validaCEP(pac.End.cep));

    do
    {
        printf("Rua: ");
        scanf(" %30[^\n]s", pac.End.rua);
        setbuf(stdin, NULL);
    }
    while(!validaRua(pac.End.rua));

    do
    {
        printf("Casa nª: ");
        scanf(" %i", &pac.End.casa);
        setbuf(stdin, NULL);
    }
    while(!validaNumCasa(pac.End.casa));

    printf("Bairro: ");
    scanf(" %30[^\n]s", pac.End.bairro);

    printf("Cidade: ");
    scanf(" %30[^\n]s", pac.End.cidade);

    printf("Estado: ");
    scanf(" %30[^\n]s", pac.End.estado);

    pac.idade = anoAtual - pac.DataNasc.ano;
    setbuf(stdin, NULL);

    do
    {
        printf("O paciente possue alguma comorbidade? (s/n): ");
        scanf("%c", &op);
        setbuf(stdin, NULL);
    }
    while(op != 's' && op != 'n');

    if(op == 's')
    {
        char com[SIZE] = "";
        int qtsCom = qtsLinha(PATH_COM_DATABASE), qtsComPac = 0, opDigPeloPac = 0;
        char **lCom = listaComorbidade();

        // mostrando lista de comorbidades:
        printf("\n\nx-x-x-x-x-x-x-x-x-x-x-x-x\n");
        for(int i = 0; i < qtsCom; i++)
        {
            printf("[%i] %s\n", i + 1, lCom[i]);
        }
        printf("x-x-x-x-x-x-x-x-x-x-x-x-x\n");

        do
        {
            printf("\nEla(s) esta na lista acima? (s/n): ");
            scanf(" %c", &op);
            setbuf(stdin, NULL);
        }
        while(op != 's' && op != 'n');

        if(op == 's')
        {
            do
            {
                printf("\nPaciente tem quantas comorbidade na lista acima?\n-> ");
                scanf(" %i", &qtsComPac);
            }
            while(qtsComPac > qtsCom || qtsComPac < 1);

            printf("\nQual(s)? Digite os número da comorbidade da lista\n");
            for(int i = 0; i < qtsComPac; i ++)
            {
                do
                {
                    printf("%iª Comorbidade -> ", i + 1);
                    scanf(" %i", &opDigPeloPac);

                }
                while(opDigPeloPac > qtsCom || opDigPeloPac < 0);
                strcat(com, strcat(lCom[opDigPeloPac - 1], (i == qtsComPac - 1 ? "" : "|")));
            }
            pac.comorbidade = com;
        }
        else
        {
            do
            {
                printf("\nPaciente tem quantas comorbidade?\n-> ");
                scanf(" %i", &qtsComPac);
            }
            while(qtsComPac > qtsCom);

            char lComPacTem[qtsComPac][50];

            printf("\nDigite as comorbidades:\n");
            for(int i = 0; i < qtsComPac; i++)
            {

                printf("%iª Comorbidade -> ", i + 1);
                scanf(" %50[^\n]s", lComPacTem[i]);
                fflush(stdin);
                strcat(com, strcat(lComPacTem[i], (i == qtsComPac - 1 ? "" : "|")));
            }
            pac.comorbidade = com;
        }
        fflush(stdin);
        desalocaMat(lCom, qtsCom);
    }
    else
    {
        pac.comorbidade = "não";
    }

    showPaciente(pac);

    printf("\n\nDeseja salvar? (s/n)");
    do
    {
        printf("\n-> ");
        scanf(" %c", &confirmaCad);
    }
    while(confirmaCad != 's' && confirmaCad != 'n');

    if(confirmaCad == 's')
    {

        // Grupo de Risco
        if(pac.idade > 65 && strcmp(pac.comorbidade, "não") != 0)
        {
            if(registraGrupoRisco(pac) > 0)
            {
                printf("\nPaciente foi Registrado no grupo de Risco!\n");
            }
            else
            {
                printf("\n\nErro: Não foi possivel registrar o paciente no grupo de risco!\n");
                exit(0);
            }
        }

        if(registraPaciente(pac) > 0)
        {
            printf("\nCadastrado com Sucesso!\n");
            return 1;
        }
        else
        {
            printf("\n\nError: Não foi possivel cadastrar!\n");
            exit(0);
        }
    }
    printf("\nCadastro não confirmado!\n");
    return 0;
}

// Salva na base de dados do usuario
int registraUsuario(Usuario us)
{
    int error;
    char *path = PATH_USER_DATABASE;
    FILE *pontArq = fopen(path, "a");

    if(!existeEsteArq(path))
    {
        printf("\nBase de dados não existe!");
        exit(0);
    }

    //Nome Completo,Email,Usuario,Senha,Data de Nascimento,CPF,Telefone,Endereço,Bairro,Cidade,Estado
    error = fprintf(pontArq, "%s,%s,%s,%s,%i/%i/%i,%s,%s,%s,%s,%i,%s,%s,%s\n", us.nomeCompleto, us.email, us.nomeUsuario, us.senha, us.DataNasc.dia, us.DataNasc.mes,
                    us.DataNasc.ano, us.cpf, us.telefone, us.End.cep, us.End.rua, us.End.casa, us.End.bairro, us.End.cidade, us.End.estado);
    fclose(pontArq);
    return error;
}

// salva no base de dados do grupo de risco
int registraGrupoRisco(Paciente pac)
{
    int error;
    char *path = PATH_GP_RISCO_DATABASE;
    FILE *pontArq = fopen(path, "a");

    if(!existeEsteArq(path))
    {
        printf("\nBase de dados não existe!");
        exit(0);
    }

    //CPF,CEP,Idade
    error = fprintf(pontArq, "%s,%s,%i\n", pac.cpf, pac.End.cep, pac.idade);
    fclose(pontArq);
    return error;
}

// Salva na base de dados do paciente
int registraPaciente(Paciente pac)
{
    int error;
    char *path = PATH_PACIENTES_DATABASE, dataDiag[20] = "";
    FILE *pontArq = fopen(path, "a");

    if(!existeEsteArq(path))
    {
        printf("\nBase de dados não existe!");
        exit(0);
    }

    strftime(dataDiag, 20, "%d/%m/%Y %H:%M", pac.DataDiag);

    //Nome Completo,Email,Data de Nascimento,CPF,Telefone,CEP,Data do Diagnostico,Endereço,Bairro,Cidade,Estado,Comorbidade
    error = fprintf(pontArq, "%s,%s,%i/%i/%i,%s,%s,%s,%s,%s,%i,%s,%s,%s,%s\n",
                    pac.nomeCompleto, pac.email, pac.DataNasc.dia, pac.DataNasc.mes, pac.DataNasc.ano, pac.cpf, pac.telefone, pac.End.cep, dataDiag,
                    pac.End.rua, pac.End.casa, pac.End.bairro, pac.End.cidade, pac.End.estado, pac.comorbidade);
    fclose(pontArq);
    return error;
}

int qtsLinha(char *path)
{
    char linha[SIZE];
    FILE *pontArq;
    pontArq = fopen(path, "r");
    char **mat = alocaMat(4, SIZE);
    int pulaCabecalho = 0, count = 0;

    while(fgets(linha, 200, pontArq) != NULL)
    {
        if(pulaCabecalho == 0)
        {
            pulaCabecalho = 1;
            continue;
        }
        count++;
    }
    fclose(pontArq);
    return count;
}

// Aloca memoria
char** alocaMat(int linha, int coluna)
{

    char **mat = (char**)malloc(linha * sizeof(char*));//aloca as linhas da matriz
    for(int i = 0; i < linha; i++)
    {
        mat[i] = (char*)malloc(coluna * sizeof(char));//aloca as colunas para cada linha da matriz
    }

    return mat;
}
// Libera memoria dinâmica
void desalocaMat (char **mat, int linhas)
{
    int i;
    if(mat != NULL)
    {
        for(i = 0; i < linhas; i++)
        {
            free(mat[i]);
        }
        free(mat);
    }
}

char** listaCampos(char *linha, int qtsCampo)
{
    int count = 0;
    char **mat, *campo;
    mat = (char**)malloc(qtsCampo * sizeof(char*));

    campo = strtok(linha, ",\n");
    while(campo != NULL)
    {
        mat[count] = (char*)malloc(strlen(campo) * sizeof(char));
        mat[count] = campo;
        campo = strtok(NULL, ",\n");
        count++;
    }
    return *mat;
}

char** lista(char *caminhoArq, char *nomeCampo, char *valorCampo)
{
    char linha[SIZE], *linhaAux;
    char *campo;
    int pulaCabecalho = 0, count = 0, indiceCp = indiceDoCampo(caminhoArq, nomeCampo), qtsCp = qtsCampo(caminhoArq);
    char **mat = alocaMat(qtsCp, SIZE);

    FILE *pontArq = (fopen(caminhoArq, "r"));

    if(pontArq == NULL || (existeEsteArq(caminhoArq) == 0))
    {
        printf("\nErro: fonte de dados não encontrada!\n");
        systemPause();
        exit(0);
    }
    while(linhaAux = fgets(linha, 200, pontArq) != NULL)
    {
        if(pulaCabecalho == 0)
        {
            pulaCabecalho = 1;
            continue;
        }

        //strcpy(auxLinha, linha);
        campo = strtok(linha, ",\n");
        while(campo != NULL)
        {
            strcpy(mat[count], campo);
            count++;
            campo = strtok(NULL, ",\n");
        }

        if(strcmp(mat[indiceCp], valorCampo) == 0)
        {
            fclose(pontArq);
            return mat;
        }
        count = 0;
    }
    if(linhaAux == NULL)
    {
        desalocaMat(mat, qtsCp);
        fclose(pontArq);
        return NULL;
    }
    fclose(pontArq);
}

// Retorna o localidade(indice) do campo que foi passado como parametro, caso não exista retorna -1.
int indiceDoCampo(char *caminhoArq, char *nomeCampo)
{
    setlocale(LC_ALL, "Portuguese_Brazil");

    FILE *pontArq;
    pontArq = (fopen(caminhoArq, "r"));
    char linha[SIZE];
    int count = 0;
    char *campo;

    if(pontArq == NULL || (existeEsteArq(caminhoArq) == 0))
    {
        printf("\nErro: fonte de dados não encontrada!\n");
        systemPause();
        return 0;
    }
    if(nomeCampo == NULL || strcmp(nomeCampo,"") == 0)
    {
        printf("\nErro: parametro indefinido!");
        return 0;
    }
    fgets(linha, SIZE, pontArq);
    campo = strtok(linha, ",");
    while(campo != NULL)
    {
        if(strcmp(campo, nomeCampo) == 0)
        {
            return count;
        }
        count++;
        campo = strtok(NULL, ",\n");
    }
    fclose(pontArq);
    return -1;
}

int qtsCampo(char caminhoArq[])
{
    FILE *pontArq;
    pontArq = (fopen(caminhoArq, "r"));
    char linha[SIZE];
    int count = 0;
    char *campo;

    if(pontArq == NULL || (existeEsteArq(caminhoArq) == 0))
    {
        printf("\nErro: fonte de dados não encontrada!\n");
        systemPause();
        return 0;
    }
    fgets(linha, SIZE, pontArq);
    campo = strtok(linha, ",\n");
    do
    {
        count++;
        campo = strtok(NULL, ",\n");
    }
    while(campo != NULL);
    fclose(pontArq);
    return count;
}

void showUsuario(Usuario us)
{
    printf("______________________________");
    printf("\n\nPOR FAVOR CONFIRME OS DADOS ANTES DE CONCLUIR CADASTRO!\n");
    printf("\n\n[-----DADOS PESSOAIS-----]\n");
    printf("Nome Completo: %s\n", us.nomeCompleto);
    printf("Email: %s\n", us.email);
    printf("CPF: %s\n", us.cpf);
    printf("Telefone: %s\n", us.telefone);

    printf("\n\n[---------USUÁRIO--------]\n");
    printf("Nome de usuário: ");
    printf("Senha do usuário: ");

    printf("\n\n[---DATA DE NASCIMENTO---]\n");
    printf("%i/%i/%i\n", us.DataNasc.dia, us.DataNasc.mes, us.DataNasc.ano);

    printf("\n\n[--------ENDEREÇO--------]\n");
    printf("CEP: %s\n", us.End.cep);
    printf("Rua: %i\n", us.End.rua);
    printf("Casa: %i\n", us.End.casa);
    printf("Bairro: %s\n", us.End.bairro);
    printf("Cidade: %s\n", us.End.cidade);
    printf("Estado: %s\n", us.End.estado);

}

void showPaciente(Paciente pac)
{
    printf("______________________________");
    printf("\n\nPOR FAVOR CONFIRME OS DADOS ANTES DE CONCLUIR CADASTRO!\n");
    printf("Nome Completo: %s\n", pac.nomeCompleto);
    printf("Email: %s\n", pac.email);
    printf("CPF: %s\n", pac.cpf);
    printf("Telefone: %s\n", pac.telefone);

    printf("\n\n[---DATA DE NASCIMENTO---]\n");
    printf("%i/%i/%i\n", pac.DataNasc.dia, pac.DataNasc.mes, pac.DataNasc.ano);

    printf("\n\n[--------ENDEREÇO--------]\n");
    printf("CEP: %s\n", pac.End.cep);
    printf("Rua: %i\n", pac.End.rua);
    printf("Casa: %i\n", pac.End.casa);
    printf("Bairro: %s\n", pac.End.bairro);
    printf("Cidade: %s\n", pac.End.cidade);
    printf("Estado: %s\n", pac.End.estado);

    printf("\n\n[--------COMORBIDADES--------]\n");
    printf("%s", pac.comorbidade);
}

/******************<
    VALIDAÇÃO
*******************/

// funcão genérica que verifica se qualquer valor existe em uma base de dados especifica.
int existeEsteDados(char *valorCampo, char *path, char *nomeCampo)
{
    char **mat = lista(path, nomeCampo, valorCampo);
    if(mat)
    {
        desalocaMat(mat, qtsCampo(path));
        return 1;
    }
    desalocaMat(mat, qtsCampo(path));
    return 0;
}

// verifica se existe tal usuario.
int existeEsteUs(char *valorCampo, char *path)
{
    char *us = "Usuario";
    if(existeEsteDados(valorCampo, path, us))
    {
        return 1;
    }
    return 0;
}

// verifica se existe tal CPF.
int existeEsteCPF(char *valorCampo, char *path)
{
    char *cpf = "CPF";
    if(existeEsteDados(valorCampo, path, cpf))
    {
        return 1;
    }
    return 0;
}

// verifica se o usuário esta válido.
int validaUs(char *valorCampo)
{
    if(strlen(valorCampo) < 4 || strlen(valorCampo) > 30)
    {
        printf("Nome usuário tem que ter tamanho minimo 4 e no máximo 30 caracteres!\n\n");
        return 0;
    }

    if(existeEsteUs(valorCampo, PATH_USER_DATABASE))
    {
        printf("Este usuário já existe!\n\n");
        return 0;
    }

    if(!soAlphaNum(valorCampo))
    {
        printf("Nome de usuário incorreto! Apenas números e letras.\n\n");
    }
    return 1;
}
int soAlphaNum(char *str)
{
    for(int i = 0; i < strlen(str); i++)
    {
        if(!isalnum(str[i]))
        {
            return 0;
        }
    }
    return 1;
}
// verifica se o CPF esta válido.
int validaCPF(char *valorCampo, char *path)
{
    if(strlen(valorCampo) != 11)
    {
        printf("Digite apenas 11 digitos!\n\n");
        return 0;
    }

    if(!soTemDigitos(valorCampo))
    {
        printf("Digite apenas numeros!\n\n");
        return 0;
    }

    if(existeEsteCPF(valorCampo, path))
    {
        printf("Este CPF já existe na base de dados, digite novamente!\n\n");
        return 0;
    }
    return 1;
}

// verifica se a apenas números na string.
int soTemDigitos(char *str)
{
    for(int i = 0; i < strlen(str); i++)
    {
        if(!isdigit(str[i]))
        {
            return 0;
        }
    }
    return 1;
}

int validaTel(char *tel)
{
    if(strlen(tel) != 11)
    {
        printf("Digite apenas 11 digitos!\n\n");
        return 0;
    }
    if(!soTemDigitos(tel))
    {
        printf("Digite apenas números!\n\n");
        return 0;
    }
    return 1;
}

int validaNome(char *nome)
{
    if(strlen(nome) <= 0 && strlen(nome) > 40)
    {
        printf("Permite até 40 caracteres!\n\n");
        return 0;
    }

    if(soTemDigitos(nome))
    {
        printf("Nome incorreto!\n\n");
        return 0;
    }
    return 1;
}


// Procedimento que converte uma string para maiúsculo
char* maiusculo(char *str)
{
    int i = 0;
    char *aux;

    while(str[i] != '\0')
    {
        aux[i] = toupper(str[i]);
        i++;
    }
    aux[i] = '\0';
    return aux;
}

// Procedimento que converte uma string para minúsculo
char* minusculo(char *str)
{
    int i = 0;
    char *aux;

    while(str[i] != '\0')
    {
        aux[i] = tolower(str[i]);
        i++;
    }
    aux[i] = '\0';
    return aux ;
}

/******************************<
    VALIDANDO DADOS ENDEREÇO
*******************************/

int validaCEP(char *cep)
{
    if(strlen(cep) != 8)
    {
        printf("CEP incorredo! tem que conter 8 digitos.\n\n");
        return 0;
    }
    if(!soTemDigitos(cep))
    {
        printf("CEP incorreto! tem que conter apenas números!\n\n");
        return 0;
    }
    return 1;
}

int validaNumCasa(int numCasa)
{
    if(numCasa > 999 && numCasa <= 0)
    {
        return 0;
    }
    return 1;
}

int validaRua(char *rua)
{
    if(strlen(rua) <= 0 && strlen(rua) > 40)
    {
        printf("Permite até 30 caracteres!\n\n");
        return 0;
    }
    return 1;
}

int validaEmail(char *email, char *path)
{
    if(existeEsteDados(email, path, "Email"))
    {
        printf("Este email já está cadastrado!\n\n");
        return 0;
    }
    return 1;
}
/*
int validaBairro(char *bairro)
{
    return 1;
}

int validaCidade(char *cidade)
{
    return 1;
}

int validaEstado(char *estado)
{
    return 1;
}

*/


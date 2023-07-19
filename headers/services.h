#ifndef SERVICES_H_INCLUDED
#define SERVICES_H_INCLUDED

// constates
#define SIZE 200
#define UNDEFINED -2

// caminhos de arquivos:
#define PATH_BASE "PIM-IV/"
#define PATH_USER_DATABASE "db_files/users/user.csv"
#define PATH_ROOT_DATABASE "db_files/users/root.csv"
#define PATH_PACIENTES_DATABASE "db_files/pacientes/pacientes.csv"
#define PATH_GP_RISCO_DATABASE "db_files/grupo-de-risco/gp-risco.csv"
#define PATH_COM_DATABASE "db_files/comorbidades/comorbidades.csv"

// startup
void startup();

// funções
char* ocultaSenha();
int existeEsteArq(char caminho[]);
char* maiusculo(char *str);
char* minusculo(char *str);
int indiceDoCampo(char *caminhoArq, char *nomeCampo);
char** lista(char *caminhoArq, char *nomeCampo, char *valorCampo);
int qtsCampo(char caminhoArq[]);
char** listaCampos(char *linha, int qtsCampo);
void desalocaMat(char **mat, int linhas);
char** alocaMat(int linha, int coluna);

// tela
void showHead();
void systemPause();
void menuUsuario(char *user);
void showHeadRegPac();
void showHeadRegUser();
void menuHome();
void showHeadCadUser();
void showHeadCadPac();

// popular os db_files
void popUsers();
void popComorbidade();
void popPaciente();
void popGrupoRisco();

//strucs
typedef struct
{
    int dia, mes, ano;
} Data;

typedef struct
{
    char cep[9];
    char rua[50];
    int casa;
    char bairro[50];
    char cidade[50];
    char estado[3];
} Endereco;

typedef struct
{
    char nomeCompleto[50];
    char email[50];
    Data DataNasc;
    int idade;
    char cpf[12];
    char telefone[12];
    struct tm *DataDiag;
    Endereco End;
    char *comorbidade;
    char agenteDeSaude[50];
} Paciente;

typedef struct
{
    char nomeCompleto[50];
    char nomeUsuario[30];
    char email[50];
    char senha[50];
    Data DataNasc;
    char cpf[12];
    char telefone[12];
    Endereco End;
} Usuario;


#endif // SERVICES_H_INCLUDED

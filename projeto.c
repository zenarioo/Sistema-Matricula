
#include <stdio.h>
#include <stdlib.h> //qsort para arrays
#include <string.h>
#include <ctype.h>

//aqui eu defini todas as structs do projeto que foram apresentadas nas orientações do projeto
typedef struct {
    int dia;
    int mes;
    int ano;
} td_data;

typedef struct {
    int hora;
    int min;
} td_hora;

typedef struct {
    int codigo_dis;
    char disciplina[100];
} td_disciplina;

typedef struct {
    int ra;
    char nome[100];
    char email[100]; 
} td_aluno;

typedef struct {
    int ra;           
    int codigo_dis;    
    td_data data_matricula;
    float notas[4];
} td_matricula;

typedef struct {
    td_aluno aluno;
    td_hora horario;
    td_data data;
    char descricao[300];
} td_compromisso;

// aqui eu apresentei os prototipos das funcoes
// sao responsaveis por gerenciar a memoria para vetores
// essas funcoes sao para alocar memoria inicial para um vetor de cada tipo
// os parametros *dimensao sao ponteiros para um int que sera usado para informar a dimensao incial do vetor alocado
//mesmo para *vetor

td_aluno* aloca_vetor_alunos(int *dimensao);
td_aluno* realoca_vetor_alunos(td_aluno *vetor, int *dimensao);
td_disciplina* aloca_vetor_disciplinas(int *dimensao);
td_disciplina* realoca_vetor_disciplinas(td_disciplina *vetor, int *dimensao);
td_matricula* aloca_vetor_matriculas(int *dimensao);
td_matricula* realoca_vetor_matriculas(td_matricula *vetor, int *dimensao);
td_compromisso* aloca_vetor_compromissos(int *dimensao);
td_compromisso* realoca_vetor_compromissos(td_compromisso *vetor, int *dimensao);

//prototipo das minhas funcoes void e int 
// parametros vetor e posicao para eu indicar a posicao especifica dentro do vetor
void cadastra_aluno(td_aluno vetor[], int posicao);
void cadastra_disciplina(td_disciplina vetor[], int posicao);
void cadastra_matricula(td_matricula vetor[], int posicao, td_aluno alunos[], int tam_alunos, td_disciplina disciplinas[], int tam_disciplinas);
int verifica_data(td_data *data);
int verifica_horario(td_hora *hora);
void cadastra_compromisso(td_compromisso vetor[], int posicao, td_aluno alunos[], int tam_alunos);
void imprime_vetor_de_alunos(td_aluno vetor[], int dimensao);
int encontra_aluno(td_aluno *vetor, int dimensao, int codigo);
int encontra_disciplina(td_disciplina *vetor, int dimensao, int codigo);
int procura_data(td_compromisso *vetor, int dimensao, td_data *data, int ra);
int procura_horario(td_compromisso *vetor, int dimensao, td_hora *hora, td_data *data, int ra);
int verifica_email(char email[]);

void le_horario(td_hora *hora);
void le_data(td_data *data);

//funcoes qsort como apresentadas na aba "Exemplos para auxiliar no projeto"
int compara_alunos_ra(const void *a, const void *b); //essa funcao sera responsavel por comparar dois objetos do tipo td_aluno
int compara_compromissos_data_hora(const void *a, const void *b); //compara primariamente por sua data em caso de datas iguais e depois por sua hora
int compara_compromissos_ra_data_hora(const void *a, const void *b); 
int compara_compromissos_hora_ra(const void *a, const void *b);
int compara_compromissos_data_hora_ra(const void *a, const void *b);

void relatorio_compromissos_aluno(td_compromisso vetor[], int dimensao, td_aluno alunos[], int tam_alunos);
void relatorio_compromissos_todos(td_compromisso vetor[], int dimensao);
void relatorio_compromissos_data(td_compromisso vetor[], int dimensao);
void relatorio_compromissos_todas_datas(td_compromisso vetor[], int dimensao);
void relatorio_dados_aluno(td_aluno vetor[], int dimensao, td_matricula matriculas[], int tam_matriculas, td_disciplina disciplinas[], int tam_disciplinas);
void relatorio_dados_todos_alunos(td_aluno vetor[], int dimensao);

//agora eu venho para a minha main
int main() {
    
    //inicializando minhas variaveis
    //as com comecam com dim represetam a capacidade maxima das minhas variaveis
    //as que comecam com qnt representam o valor inicial delas
    int dim_alunos = 10, dim_disciplinas = 10, dim_matriculas = 20, dim_compromissos = 15;
    int qtd_alunos = 0, qtd_disciplinas = 0, qtd_matriculas = 0, qtd_compromissos = 0;
    int opcao;
    
    // aqui é a alocação dinâmica de memória para armazenar dados relacionados a alunos, disciplinas, matrículas e compromissos
    // ex: td_aluno *alunos declara um ponteiro chamado alunos que será capaz de apontar para um objeto do tipo td_aluno
    // depois chama a funcao aloca_vetor_alunos e passas o endereco de memoria dim_alunos para a funcao (que pode ler o valor inicia de dim_alunos)
    // ele sabe quantos elementos alocar e modificar depois
    td_aluno *alunos = aloca_vetor_alunos(&dim_alunos);
    td_disciplina *disciplinas = aloca_vetor_disciplinas(&dim_disciplinas);
    td_matricula *matriculas = aloca_vetor_matriculas(&dim_matriculas);
    td_compromisso *compromissos = aloca_vetor_compromissos(&dim_compromissos);
    
    //aqui eu comeco desenvolver o meu menu
    do {
        printf("\nMENU PRINCIPAL\n");
        printf("1 - Cadastrar aluno\n");
        printf("2 - Cadastrar disciplina\n");
        printf("3 - Cadastrar matricula\n");
        printf("4 - Cadastrar compromisso\n");
        printf("5 - Mostrar compromissos\n");
        printf("6 - Mostrar dados de um aluno\n");
        printf("7 - Mostrar dados de todos os alunos\n");
        printf("8 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        
        //faço um switch case de acordo com as opcoes digitadas no menu
        //esse swithc case é responsavel por verificar a quantidade de objetos alocados em uma determinada opcao
        switch(opcao) {
            case 1: 
                if (qtd_alunos == dim_alunos) {
                    alunos = realoca_vetor_alunos(alunos, &dim_alunos); //vai verificar se a quantidade de alunos é igual a dim alunos, se for ele chama a funcao para realocar o vetor
                }
                cadastra_aluno(alunos, qtd_alunos);
                qtd_alunos++;
                break;
            case 2:
                if (qtd_disciplinas == dim_disciplinas) {
                    disciplinas = realoca_vetor_disciplinas(disciplinas, &dim_disciplinas);
                }
                cadastra_disciplina(disciplinas, qtd_disciplinas);
                qtd_disciplinas++;
                break;
            case 3:
                if (qtd_matriculas == dim_matriculas) {
                    matriculas = realoca_vetor_matriculas(matriculas, &dim_matriculas);
                }
                cadastra_matricula(matriculas, qtd_matriculas, alunos, qtd_alunos, disciplinas, qtd_disciplinas);
                qtd_matriculas++;
                break;
            case 4:
                if (qtd_compromissos == dim_compromissos) {
                    compromissos = realoca_vetor_compromissos(compromissos, &dim_compromissos);
                }
                cadastra_compromisso(compromissos, qtd_compromissos, alunos, qtd_alunos);
                qtd_compromissos++;
                break;
            case 5:
                printf("\nSubmenu de Compromissos\n");
                printf("a - De um aluno (ordenado por data e hora)\n");
                printf("b - De todos os alunos (ordenado por RA, data e hora)\n");
                printf("c - De uma data (ordenado por hora e RA)\n");
                printf("d - De todas as datas (ordenado por data, hora e RA)\n");
                printf("Opcao: ");
                char sub_opcao;
                scanf(" %c", &sub_opcao);
                
                switch(sub_opcao) {
                    case 'a':
                        relatorio_compromissos_aluno(compromissos, qtd_compromissos, alunos, qtd_alunos);
                        break;
                    case 'b':
                        relatorio_compromissos_todos(compromissos, qtd_compromissos);
                        break;
                    case 'c':
                        relatorio_compromissos_data(compromissos, qtd_compromissos);
                        break;
                    case 'd':
                        relatorio_compromissos_todas_datas(compromissos, qtd_compromissos);
                        break;
                    default:
                        printf("Opcao invalida!\n");
                }
                break;
            case 6:
                relatorio_dados_aluno(alunos, qtd_alunos, matriculas, qtd_matriculas, disciplinas, qtd_disciplinas);
                break;
            case 7:
                relatorio_dados_todos_alunos(alunos, qtd_alunos);
                break;
            case 8:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 8);
    

    free(alunos);
    free(disciplinas);
    free(matriculas);
    free(compromissos);
    
    return 0;
}

td_aluno* aloca_vetor_alunos(int *dimensao) {
    td_aluno *vetor = (td_aluno*) malloc(*dimensao * sizeof(td_aluno));
    if (vetor == NULL) {
        printf("Erro ao alocar memoria para vetor de alunos!\n");
        exit(1);
    }
    return vetor;
}

td_aluno* realoca_vetor_alunos(td_aluno *vetor, int *dimensao) {
    *dimensao += 10;
    td_aluno *novo_vetor = (td_aluno*) realloc(vetor, *dimensao * sizeof(td_aluno));
    if (novo_vetor == NULL) {
        printf("Erro ao realocar memoria para vetor de alunos!\n");
        exit(1);
    }
    return novo_vetor;
}

td_disciplina* aloca_vetor_disciplinas(int *dimensao) {
    td_disciplina *vetor = (td_disciplina*) malloc(*dimensao * sizeof(td_disciplina));
    if (vetor == NULL) {
        printf("Erro ao alocar memoria para vetor de disciplinas!\n");
        exit(1);
    }
    return vetor;
}

td_disciplina* realoca_vetor_disciplinas(td_disciplina *vetor, int *dimensao) {
    *dimensao += 5;
    td_disciplina *novo_vetor = (td_disciplina*) realloc(vetor, *dimensao * sizeof(td_disciplina));
    if (novo_vetor == NULL) {
        printf("Erro ao realocar memoria para vetor de disciplinas!\n");
        exit(1);
    }
    return novo_vetor;
}

td_matricula* aloca_vetor_matriculas(int *dimensao) {
    td_matricula *vetor = (td_matricula*) malloc(*dimensao * sizeof(td_matricula));
    if (vetor == NULL) {
        printf("Erro ao alocar memoria para vetor de matriculas!\n");
        exit(1);
    }
    return vetor;
}

td_matricula* realoca_vetor_matriculas(td_matricula *vetor, int *dimensao) {
    *dimensao += 10;
    td_matricula *novo_vetor = (td_matricula*) realloc(vetor, *dimensao * sizeof(td_matricula));
    if (novo_vetor == NULL) {
        printf("Erro ao realocar memoria para vetor de matriculas!\n");
        exit(1);
    }
    return novo_vetor;
}

td_compromisso* aloca_vetor_compromissos(int *dimensao) {
    td_compromisso *vetor = (td_compromisso*) malloc(*dimensao * sizeof(td_compromisso));
    if (vetor == NULL) {
        printf("Erro ao alocar memoria para vetor de compromissos!\n");
        exit(1);
    }
    return vetor;
}

td_compromisso* realoca_vetor_compromissos(td_compromisso *vetor, int *dimensao) {
    *dimensao += 5;
    td_compromisso *novo_vetor = (td_compromisso*) realloc(vetor, *dimensao * sizeof(td_compromisso));
    if (novo_vetor == NULL) {
        printf("Erro ao realocar memoria para vetor de compromissos!\n");
        exit(1);
    }
    return novo_vetor;
}

void cadastra_aluno(td_aluno vetor[], int posicao) {
    printf("Cadastro de Aluno");
    printf("Digite o RA: ");
    scanf("%d", &vetor[posicao].ra);

    printf("Digite o nome do aluno: ");
    scanf("%s", vetor[posicao].nome);

    do{
        printf("Digite seu Email: ");
        scanf("%s", vetor[posicao]. email);
    }

    while(!verifica_email(vetor[posicao].email));
    printf("Cadastro Concluido");

}

void cadastra_disciplina(td_disciplina vetor[], int posicao){

printf("Digite o Codigo da Disciplina: ");
scanf("%d", &vetor[posicao].codigo_dis);

printf("Digite o Nome da Disciplina: ");
scanf("%s", vetor[posicao].disciplina);

printf("Disciplina Cadastrada");

}

void cadastra_matricula(td_matricula vetor[])




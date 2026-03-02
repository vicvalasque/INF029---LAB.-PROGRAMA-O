#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_ALUNO 3

#define CAD_ALUNO_SUCESSO -1
#define MATRICULA_INVALIDA -2
#define LISTA_CHEIA -3
#define ATU_ALUNO_SUCESSO -4
#define MATRICULA_INEXISTENTE -5
#define EXCLU_ALU_SUCESSO -6
#define DATA_INVALIDA -7
#define DATA_VALIDA -8

typedef struct alu
{
    int matricula;
    char nome[200];
    int dia;
    int mes;
    int ano;
    char sexo;
    char cpf[15];
    int ativo;
} Aluno;

// Protótipos das funções
int menuGeral();
int menuAluno();
int cadastrarAluno(Aluno listaAluno[], int qtdAluno);
void listarAluno(Aluno listaAluno[], int qtdAluno);
int atualizarAluno(Aluno listaAluno[], int qtdAluno);
int excluirAluno(Aluno listaAluno[], int qtdAluno);

int main()
{

    printf("Projeto escola\n\n");
    Aluno listaAluno[TAM_ALUNO];
    int opcao;

    int sair = 0;

    while (!sair)
    {

        opcao = menuGeral();

        switch (opcao)
        {
        case 0:
        {
            sair = 1;
            printf("Saindo do menu principal...");
            break;
        }
        case 1:
        {

            int sairAluno = 0;
            int opcaoAluno;
            int qtdAluno = 0;
            while (!sairAluno)
            {
                printf("Modulo Aluno\n");

                opcaoAluno = menuAluno();

                switch (opcaoAluno)
                {
                case 0:
                {
                    sairAluno = 1;
                    printf("Saindo do modulo aluno...");
                    break;
                }
                case 1:
                {
                    int retorno = cadastrarAluno(listaAluno, qtdAluno);
                    if (retorno == LISTA_CHEIA)
                    {
                        printf("Lista de alunos esta cheia.\n");
                    }
                    else if (retorno == MATRICULA_INVALIDA)
                    {
                        printf("Matricula invalida\n");
                    }
                    else if (retorno == CAD_ALUNO_SUCESSO)
                    {
                        qtdAluno++;
                        printf("Cadastrado com sucesso!\n");
                    }

                    break;
                }
                case 2:
                {
                    listarAluno(listaAluno, qtdAluno);
                    break;
                }
                case 3:
                {
                    int retorno = atualizarAluno(listaAluno, qtdAluno);

                    if (retorno == MATRICULA_INVALIDA)
                    {
                        printf("Matricula invalida\n");
                    }
                    else if (retorno == ATU_ALUNO_SUCESSO)
                    {
                        printf("Atualizacao de aluno realizada com sucesso.\n");
                    }
                    else if (retorno == MATRICULA_INEXISTENTE)
                    {
                        printf("Matricula inexistente.\n");
                    }
                    break;
                }
                case 4:
                {
                    int retorno = excluirAluno(listaAluno, qtdAluno);

                    if (retorno == MATRICULA_INVALIDA)
                    {
                        printf("Matricula invalida\n");
                    }
                    else if (retorno == EXCLU_ALU_SUCESSO)
                    {
                        printf("Exclusao realizada com sucesso.\n");
                    }
                    else if (retorno == MATRICULA_INEXISTENTE)
                    {
                        printf("Matricula inexistente.\n");
                    }
                    qtdAluno--;
                    break;
                }
                default:
                {
                    printf("Opcao invalida.");
                }
                }
            }
            break;
        }
        case 2:
        {
            printf("Modulo Professor\n");
            break;
        }
        case 3:
        {
            printf("Modulo Disciplina\n");
            break;
        }
        default:
        {
            printf("Opcao invalida.");
        }
        }
    }
    return 0;
}

int menuGeral()
{
    int opcao;

    printf("Insira a opcao desejada\n");
    printf("0 - Sair\n");
    printf("1 - Modulo Aluno\n");
    printf("2 - Modulo Professor\n");
    printf("3 - Modulo Disciplina\n");
    scanf("%d", &opcao);

    return opcao;
}

int menuAluno()
{

    int opcaoAluno;
    printf("Insira a opcao desejada\n");
    printf("0 - Voltar\n");
    printf("1 - Cadastrar aluno\n");
    printf("2 - Listar aluno\n");
    printf("3 - Atualizar aluno\n");
    printf("4 - Excluir aluno\n");
    scanf("%d", &opcaoAluno);

    return opcaoAluno;
}

int validarDataAluno(Aluno listaAluno[], int qtdAluno, int dia, int mes, int ano)
{

    if (ano >= 1970 && ano <= 2026)
    {
        if (mes > 0 && mes < 13)
        {
            if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
            {
                if (dia > 0 && dia < 31)
                {
                    return DATA_VALIDA;
                }
                else
                {
                    return DATA_INVALIDA;
                }
            }
            else if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)
            {
                if (dia > 0 && dia < 32)
                {
                    return DATA_VALIDA;
                }
                else
                {
                    return DATA_INVALIDA;
                }
            }
            else if (mes == 02)
            {
                if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0))
                {
                    if (dia > 0 && dia < 30)
                    {
                        return DATA_VALIDA;
                    }
                    else
                    {
                        return DATA_INVALIDA;
                    }
                }
                else
                {
                    if (dia > 0 && dia < 29)
                    {
                        return DATA_VALIDA;
                    }
                    else
                    {
                        return DATA_INVALIDA;
                    }
                }
            }
        }
        else
        {
            return DATA_INVALIDA;
        }
    }
    else
    {
        return DATA_INVALIDA;
    }
    return DATA_INVALIDA;
}

int cadastrarAluno(Aluno listaAluno[], int qtdAluno)
{
    printf("Cadastrar aluno\n");
    int matricula;
    char nome[200];
    int dia;
    int mes;
    int ano;
    char cpf[15];
    char sexo;

    if (qtdAluno == TAM_ALUNO)
    {
        return LISTA_CHEIA;
    }
    else
    {
        printf("Digite a matricula: \n");
        scanf("%d", &matricula);

        if (matricula < 0)
        {
            return MATRICULA_INVALIDA;
        }

        printf("Insira o nome completo: \n");
        getchar();
        fgets(nome, 200, stdin);

        printf("Insira a data de nascimento (XX/XX/XXXX): \n");
        scanf("%d/%d/%d", &dia, &mes, &ano);

        int resultado = validarDataAluno(listaAluno, qtdAluno, dia, mes, ano);
        if (resultado == DATA_VALIDA)
        {
            listaAluno[qtdAluno].dia = dia;
            listaAluno[qtdAluno].mes = mes;
            listaAluno[qtdAluno].ano = ano;
        }
        else
        {
            return DATA_INVALIDA;
        }
        /*printf("Digite o sexo: \n");
        scanf("%c", &sexo);

        printf("Insira o CPF: \n");
        fgets(cpf, 15, stdin);*/

        // Else será readicionado após colocar validação do CPF.

        listaAluno[qtdAluno].matricula = matricula;
        listaAluno[qtdAluno].ativo = 1;
        return CAD_ALUNO_SUCESSO;
    }
}

void listarAluno(Aluno listaAluno[], int qtdAluno)
{
    printf("Listar aluno\n");
    if (qtdAluno == 0)
    {
        printf("Lista vazia.\n");
    }
    else
    {
        for (int i = 0; i < qtdAluno; i++)
        {
            if (listaAluno[i].ativo == 1)
                printf("Matricula: %d\n", listaAluno[i].matricula);
        }
    }
}

int atualizarAluno(Aluno listaAluno[], int qtdAluno)
{
    printf("Atualizar aluno\n");
    printf("Digite a matricula: \n");
    int matricula;
    scanf("%d", &matricula);
    int achou = 0;

    if (matricula < 0)
    {
        return MATRICULA_INVALIDA;
    }
    else
    {
        for (int i = 0; i < qtdAluno; i++)
        {
            if (matricula == listaAluno[i].matricula && listaAluno[i].ativo)
            {
                printf("Digite a nova matricula: \n");
                int novaMatricula;
                scanf("%d", &novaMatricula);
                listaAluno[i].matricula = novaMatricula;

                achou = 1;
                break;
            }
        }
        if (achou == 1)
            return ATU_ALUNO_SUCESSO;

        else
            return MATRICULA_INEXISTENTE;
    }
}

int excluirAluno(Aluno listaAluno[], int qtdAluno)
{
    printf("Excluir aluno\n");
    printf("Digite a matricula: \n");
    int matricula;
    scanf("%d", &matricula);
    int achou = 0;

    if (matricula < 0)
    {
        return MATRICULA_INVALIDA;
    }
    for (int i = 0; i < qtdAluno; i++)
    {
        if (matricula == listaAluno[i].matricula)
        {
            listaAluno[i].ativo = -1;
            for (int j = i; j < qtdAluno - 1; j++)
            { // shift
                listaAluno[j].matricula = listaAluno[j + 1].matricula;
                listaAluno[j].ativo = listaAluno[j + 1].ativo;
            }
            achou = 1;
            break;
        }
    }
    if (achou == 1)
    {
        return EXCLU_ALU_SUCESSO;
    }
    else
    {
        return MATRICULA_INEXISTENTE;
    }
}
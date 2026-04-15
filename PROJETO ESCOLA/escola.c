#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM_ALUNO 3
#define TAM_PROFESSOR 3

#define CAD_ALUNO_SUCESSO -1
#define MATRICULA_INVALIDA -2
#define LISTA_CHEIA -3
#define ATU_ALUNO_SUCESSO -4
#define MATRICULA_INEXISTENTE -5
#define EXCLU_ALU_SUCESSO -6
#define DATA_INVALIDA -7
#define DATA_VALIDA -8
#define CPF_VALIDO -9
#define CPF_INVALIDO -10
#define SEXO_INVALIDO -11
#define LISTA_INVALIDA -12
#define CAD_PROFESSOR_SUCESSO -13
#define ATU_PROFESSOR_SUCESSO -14
#define EXCLU_PROF_SUCESSO -15

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

typedef struct prof
{
    int matricula;
    char nome[200];
    int dia;
    int mes;
    int ano;
    char sexo;
    char cpf[15];
    int ativo;
} Professor;

int menuGeral();
int menuAluno();
int cadastrarAluno(Aluno listaAluno[], int qtdAluno);
void listarAluno(Aluno listaAluno[], int qtdAluno);
int atualizarAluno(Aluno listaAluno[], int qtdAluno);
int excluirAluno(Aluno listaAluno[], int qtdAluno);
int validarCPF(char cpf[]);
int menuListarAluno();
int listarAluSexo(Aluno listaAluno[], int qtdAluno);
int validarDataAluno(Aluno listaAluno[], int qtdAluno, int dia, int mes, int ano);

int menuProfessor();
int cadastrarProfessor(Professor listaProfessor[], int qtdProfessor);
void listarProfessor(Professor listaProfessor[], int qtdProfessor);
int atualizarProfessor(Professor listaProfessor[], int qtdProfessor);
int excluirProfessor(Professor listaProfessor[], int qtdProfessor);
int menuListarProfessor();
int listarProfSexo(Professor listaProfessor[], int qtdProfessor);
int validarDataProfessor(Professor listaProfessor[], int qtdProfessor, int dia, int mes, int ano);

int main()
{
    printf("Projeto escola\n\n");
    Aluno listaAluno[TAM_ALUNO];
    Professor listaProfessor[TAM_PROFESSOR];
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
            int opcaoListaAluno;

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
                    else if (retorno == DATA_INVALIDA)
                    {
                        printf("Data de nascimento invalida\n");
                    }
                    else if (retorno == SEXO_INVALIDO)
                    {
                        printf("Sexo informado invalido.\n");
                    }
                    else if (retorno == CPF_INVALIDO)
                    {
                        printf("CPF informado invalido.\n");
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
                    opcaoListaAluno = menuListarAluno();
                    switch (opcaoListaAluno)
                    {
                    case 0:
                        break;
                    case 1:
                        listarAluno(listaAluno, qtdAluno);
                        break;
                    case 2:
                        listarAluSexo(listaAluno, qtdAluno);
                        break;
                    default:
                        printf("Opcao invalida.\n");
                    }
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
                        qtdAluno--;
                        printf("Exclusao realizada com sucesso.\n");
                    }
                    else if (retorno == MATRICULA_INEXISTENTE)
                    {
                        printf("Matricula inexistente.\n");
                    }
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
            int sairProfessor = 0;
            int opcaoProfessor;
            int qtdProfessor = 0;
            int opcaoListaProfessor;

            while (!sairProfessor)
            {
                printf("Modulo Professor\n");
                opcaoProfessor = menuProfessor();

                switch (opcaoProfessor)
                {
                case 0:
                {
                    sairProfessor = 1;
                    printf("Saindo do modulo professor...");
                    break;
                }
                case 1:
                {
                    int retorno = cadastrarProfessor(listaProfessor, qtdProfessor);
                    if (retorno == LISTA_CHEIA)
                    {
                        printf("Lista de professores esta cheia.\n");
                    }
                    else if (retorno == MATRICULA_INVALIDA)
                    {
                        printf("Matricula invalida\n");
                    }
                    else if (retorno == DATA_INVALIDA)
                    {
                        printf("Data de nascimento invalida\n");
                    }
                    else if (retorno == SEXO_INVALIDO)
                    {
                        printf("Sexo informado invalido.\n");
                    }
                    else if (retorno == CPF_INVALIDO)
                    {
                        printf("CPF informado invalido.\n");
                    }
                    else if (retorno == CAD_PROFESSOR_SUCESSO)
                    {
                        qtdProfessor++;
                        printf("Cadastrado com sucesso!\n");
                    }
                    break;
                }
                case 2:
                {
                    opcaoListaProfessor = menuListarProfessor();
                    switch (opcaoListaProfessor)
                    {
                    case 0:
                        break;
                    case 1:
                        listarProfessor(listaProfessor, qtdProfessor);
                        break;
                    case 2:
                        listarProfSexo(listaProfessor, qtdProfessor);
                        break;
                    default:
                        printf("Opcao invalida.\n");
                    }
                    break;
                }
                case 3:
                {
                    int retorno = atualizarProfessor(listaProfessor, qtdProfessor);
                    if (retorno == MATRICULA_INVALIDA)
                    {
                        printf("Matricula invalida\n");
                    }
                    else if (retorno == ATU_PROFESSOR_SUCESSO)
                    {
                        printf("Atualizacao de professor realizada com sucesso.\n");
                    }
                    else if (retorno == MATRICULA_INEXISTENTE)
                    {
                        printf("Matricula inexistente.\n");
                    }
                    break;
                }
                case 4:
                {
                    int retorno = excluirProfessor(listaProfessor, qtdProfessor);
                    if (retorno == MATRICULA_INVALIDA)
                    {
                        printf("Matricula invalida\n");
                    }
                    else if (retorno == EXCLU_PROF_SUCESSO)
                    {
                        qtdProfessor--;
                        printf("Exclusao realizada com sucesso.\n");
                    }
                    else if (retorno == MATRICULA_INEXISTENTE)
                    {
                        printf("Matricula inexistente.\n");
                    }
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

int menuProfessor()
{
    int opcaoProfessor;
    printf("Insira a opcao desejada\n");
    printf("0 - Voltar\n");
    printf("1 - Cadastrar professor\n");
    printf("2 - Listar professor\n");
    printf("3 - Atualizar professor\n");
    printf("4 - Excluir professor\n");
    scanf("%d", &opcaoProfessor);
    return opcaoProfessor;
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
                    return DATA_VALIDA;
                else
                    return DATA_INVALIDA;
            }
            else if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)
            {
                if (dia > 0 && dia < 32)
                    return DATA_VALIDA;
                else
                    return DATA_INVALIDA;
            }
            else if (mes == 2)
            {
                if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0))
                {
                    if (dia > 0 && dia < 30)
                        return DATA_VALIDA;
                    else
                        return DATA_INVALIDA;
                }
                else
                {
                    if (dia > 0 && dia < 29)
                        return DATA_VALIDA;
                    else
                        return DATA_INVALIDA;
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

int validarDataProfessor(Professor listaProfessor[], int qtdProfessor, int dia, int mes, int ano)
{
    if (ano >= 1970 && ano <= 2026)
    {
        if (mes > 0 && mes < 13)
        {
            if (mes == 4 || mes == 6 || mes == 9 || mes == 11)
            {
                if (dia > 0 && dia < 31)
                    return DATA_VALIDA;
                else
                    return DATA_INVALIDA;
            }
            else if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)
            {
                if (dia > 0 && dia < 32)
                    return DATA_VALIDA;
                else
                    return DATA_INVALIDA;
            }
            else if (mes == 2)
            {
                if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0))
                {
                    if (dia > 0 && dia < 30)
                        return DATA_VALIDA;
                    else
                        return DATA_INVALIDA;
                }
                else
                {
                    if (dia > 0 && dia < 29)
                        return DATA_VALIDA;
                    else
                        return DATA_INVALIDA;
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

int validarCPF(char cpf[])
{
    char cpfLimpo[12];
    int j = 0;

    for (int i = 0; cpf[i] != '\0'; i++)
    {
        if (cpf[i] >= '0' && cpf[i] <= '9')
        {
            cpfLimpo[j] = cpf[i];
            j++;
        }
    }
    cpfLimpo[j] = '\0';

    if (j != 11)
        return CPF_INVALIDO;

    int todosIguais = 1;
    for (int i = 1; i < 11; i++)
    {
        if (cpfLimpo[i] != cpfLimpo[0])
        {
            todosIguais = 0;
            break;
        }
    }
    if (todosIguais)
        return CPF_INVALIDO;

    int soma = 0;
    for (int i = 0; i < 9; i++)
        soma += (cpfLimpo[i] - '0') * (10 - i);
    int resto = (soma * 10) % 11;
    if (resto == 10 || resto == 11)
        resto = 0;
    if (resto != (cpfLimpo[9] - '0'))
        return CPF_INVALIDO;

    soma = 0;
    for (int i = 0; i < 10; i++)
        soma += (cpfLimpo[i] - '0') * (11 - i);
    resto = (soma * 10) % 11;
    if (resto == 10 || resto == 11)
        resto = 0;
    if (resto != (cpfLimpo[10] - '0'))
        return CPF_INVALIDO;

    return CPF_VALIDO;
}

int cadastrarAluno(Aluno listaAluno[], int qtdAluno)
{
    printf("Cadastrar aluno\n");
    int matricula;
    char nome[200];
    int dia, mes, ano;
    char cpf[15];
    char sexo;

    if (qtdAluno == TAM_ALUNO)
        return LISTA_CHEIA;

    printf("Digite a matricula: \n");
    scanf("%d", &matricula);

    if (matricula < 0)
        return MATRICULA_INVALIDA;

    printf("Insira o nome completo: \n");
    getchar();
    fgets(nome, 200, stdin);

    printf("Insira a data de nascimento (XX/XX/XXXX): \n");
    scanf("%d/%d/%d", &dia, &mes, &ano);

    int resultadoData = validarDataAluno(listaAluno, qtdAluno, dia, mes, ano);
    if (resultadoData == DATA_VALIDA)
    {
        listaAluno[qtdAluno].dia = dia;
        listaAluno[qtdAluno].mes = mes;
        listaAluno[qtdAluno].ano = ano;
    }
    else
        return DATA_INVALIDA;

    printf("Digite o sexo (M/F): \n");
    getchar();
    scanf("%c", &sexo);

    if (sexo == 'm' || sexo == 'M' || sexo == 'f' || sexo == 'F')
        listaAluno[qtdAluno].sexo = sexo;
    else
        return SEXO_INVALIDO;

    printf("Insira o CPF: \n");
    getchar();
    fgets(cpf, 15, stdin);

    int resultadoCPF = validarCPF(cpf);
    if (resultadoCPF == CPF_VALIDO)
        strcpy(listaAluno[qtdAluno].cpf, cpf);
    else
        return CPF_INVALIDO;

    listaAluno[qtdAluno].matricula = matricula;
    strcpy(listaAluno[qtdAluno].nome, nome);
    listaAluno[qtdAluno].ativo = 1;
    return CAD_ALUNO_SUCESSO;
}

int cadastrarProfessor(Professor listaProfessor[], int qtdProfessor)
{
    printf("Cadastrar professor\n");
    int matricula;
    char nome[200];
    int dia, mes, ano;
    char cpf[15];
    char sexo;

    if (qtdProfessor == TAM_PROFESSOR)
        return LISTA_CHEIA;

    printf("Digite a matricula: \n");
    scanf("%d", &matricula);

    if (matricula < 0)
        return MATRICULA_INVALIDA;

    printf("Insira o nome completo: \n");
    getchar();
    fgets(nome, 200, stdin);

    printf("Insira a data de nascimento (XX/XX/XXXX): \n");
    scanf("%d/%d/%d", &dia, &mes, &ano);

    int resultadoData = validarDataProfessor(listaProfessor, qtdProfessor, dia, mes, ano);
    if (resultadoData == DATA_VALIDA)
    {
        listaProfessor[qtdProfessor].dia = dia;
        listaProfessor[qtdProfessor].mes = mes;
        listaProfessor[qtdProfessor].ano = ano;
    }
    else
        return DATA_INVALIDA;

    printf("Digite o sexo (M/F): \n");
    getchar();
    scanf("%c", &sexo);

    if (sexo == 'm' || sexo == 'M' || sexo == 'f' || sexo == 'F')
        listaProfessor[qtdProfessor].sexo = sexo;
    else
        return SEXO_INVALIDO;

    printf("Insira o CPF: \n");
    getchar();
    fgets(cpf, 15, stdin);

    int resultadoCPF = validarCPF(cpf);
    if (resultadoCPF == CPF_VALIDO)
        strcpy(listaProfessor[qtdProfessor].cpf, cpf);
    else
        return CPF_INVALIDO;

    listaProfessor[qtdProfessor].matricula = matricula;
    strcpy(listaProfessor[qtdProfessor].nome, nome);
    listaProfessor[qtdProfessor].ativo = 1;
    return CAD_PROFESSOR_SUCESSO;
}

int menuListarAluno()
{
    int opcao;
    printf("Insira a opcao desejada\n");
    printf("0 - Voltar\n");
    printf("1 - Listar alunos\n");
    printf("2 - Listar por sexo\n");
    printf("3 - Listar ordenado por nome\n");
    printf("4 - Listar aluno ordenado por data de nascimento\n");
    scanf("%d", &opcao);
    return opcao;
}

int menuListarProfessor()
{
    int opcao;
    printf("Insira a opcao desejada\n");
    printf("0 - Voltar\n");
    printf("1 - Listar professores\n");
    printf("2 - Listar por sexo\n");
    printf("3 - Listar ordenado por nome\n");
    printf("4 - Listar professor ordenado por data de nascimento\n");
    scanf("%d", &opcao);
    return opcao;
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
            {
                printf("Matricula: %d\n", listaAluno[i].matricula);
                printf("Nome completo: %s\n", listaAluno[i].nome);
                printf("Data de nascimento: %d/%d/%d\n", listaAluno[i].dia, listaAluno[i].mes, listaAluno[i].ano);
                printf("Sexo: %c\n", listaAluno[i].sexo);
                printf("CPF: %s\n", listaAluno[i].cpf);
            }
        }
    }
}

void listarProfessor(Professor listaProfessor[], int qtdProfessor)
{
    printf("Listar professor\n");
    if (qtdProfessor == 0)
    {
        printf("Lista vazia.\n");
    }
    else
    {
        for (int i = 0; i < qtdProfessor; i++)
        {
            if (listaProfessor[i].ativo == 1)
            {
                printf("Matricula: %d\n", listaProfessor[i].matricula);
                printf("Nome completo: %s\n", listaProfessor[i].nome);
                printf("Data de nascimento: %d/%d/%d\n", listaProfessor[i].dia, listaProfessor[i].mes, listaProfessor[i].ano);
                printf("Sexo: %c\n", listaProfessor[i].sexo);
                printf("CPF: %s\n", listaProfessor[i].cpf);
            }
        }
    }
}

int listarAluSexo(Aluno listaAluno[], int qtdAluno)
{
    printf("Listar aluno por sexo (M/F)\n\n");
    if (qtdAluno == 0)
    {
        printf("Lista vazia.\n");
        return LISTA_INVALIDA;
    }

    char sexo;
    printf("Informe o sexo do aluno: \n");
    getchar();
    scanf("%c", &sexo);

    if (sexo == 'M' || sexo == 'm' || sexo == 'F' || sexo == 'f')
    {
        for (int i = 0; i < qtdAluno; i++)
        {
            if ((listaAluno[i].sexo == sexo || (sexo == 'm' && listaAluno[i].sexo == 'M') || (sexo == 'M' && listaAluno[i].sexo == 'm') || (sexo == 'f' && listaAluno[i].sexo == 'F') || (sexo == 'F' && listaAluno[i].sexo == 'f')) && listaAluno[i].ativo == 1)
            {
                printf("Matricula: %d\n", listaAluno[i].matricula);
                printf("Nome completo: %s\n", listaAluno[i].nome);
                printf("Data de nascimento: %d/%d/%d\n", listaAluno[i].dia, listaAluno[i].mes, listaAluno[i].ano);
                printf("Sexo: %c\n", listaAluno[i].sexo);
                printf("CPF: %s\n", listaAluno[i].cpf);
            }
        }
    }
    else
    {
        return LISTA_INVALIDA;
    }
    return 0;
}

int listarProfSexo(Professor listaProfessor[], int qtdProfessor)
{
    printf("Listar professor por sexo (M/F)\n\n");
    if (qtdProfessor == 0)
    {
        printf("Lista vazia.\n");
        return LISTA_INVALIDA;
    }

    char sexo;
    printf("Informe o sexo do professor: \n");
    getchar();
    scanf("%c", &sexo);

    if (sexo == 'M' || sexo == 'm' || sexo == 'F' || sexo == 'f')
    {
        for (int i = 0; i < qtdProfessor; i++)
        {
            if ((listaProfessor[i].sexo == sexo || (sexo == 'm' && listaProfessor[i].sexo == 'M') || (sexo == 'M' && listaProfessor[i].sexo == 'm') || (sexo == 'f' && listaProfessor[i].sexo == 'F') || (sexo == 'F' && listaProfessor[i].sexo == 'f')) && listaProfessor[i].ativo == 1)
            {
                printf("Matricula: %d\n", listaProfessor[i].matricula);
                printf("Nome completo: %s\n", listaProfessor[i].nome);
                printf("Data de nascimento: %d/%d/%d\n", listaProfessor[i].dia, listaProfessor[i].mes, listaProfessor[i].ano);
                printf("Sexo: %c\n", listaProfessor[i].sexo);
                printf("CPF: %s\n", listaProfessor[i].cpf);
            }
        }
    }
    else
    {
        return LISTA_INVALIDA;
    }
    return 0;
}

int atualizarAluno(Aluno listaAluno[], int qtdAluno)
{
    printf("Atualizar aluno\n");
    printf("Digite a matricula: \n");
    int matricula;
    scanf("%d", &matricula);
    int achou = 0;

    if (matricula < 0)
        return MATRICULA_INVALIDA;

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

int atualizarProfessor(Professor listaProfessor[], int qtdProfessor)
{
    printf("Atualizar professor\n");
    printf("Digite a matricula: \n");
    int matricula;
    scanf("%d", &matricula);
    int achou = 0;

    if (matricula < 0)
        return MATRICULA_INVALIDA;

    for (int i = 0; i < qtdProfessor; i++)
    {
        if (matricula == listaProfessor[i].matricula && listaProfessor[i].ativo)
        {
            printf("Digite a nova matricula: \n");
            int novaMatricula;
            scanf("%d", &novaMatricula);
            listaProfessor[i].matricula = novaMatricula;
            achou = 1;
            break;
        }
    }

    if (achou == 1)
        return ATU_PROFESSOR_SUCESSO;
    else
        return MATRICULA_INEXISTENTE;
}

int excluirAluno(Aluno listaAluno[], int qtdAluno)
{
    printf("Excluir aluno\n");
    printf("Digite a matricula: \n");
    int matricula;
    scanf("%d", &matricula);
    int achou = 0;

    if (matricula < 0)
        return MATRICULA_INVALIDA;

    for (int i = 0; i < qtdAluno; i++)
    {
        if (matricula == listaAluno[i].matricula)
        {
            listaAluno[i].ativo = -1;
            for (int j = i; j < qtdAluno - 1; j++)
            {
                listaAluno[j].matricula = listaAluno[j + 1].matricula;
                listaAluno[j].ativo = listaAluno[j + 1].ativo;
            }
            achou = 1;
            break;
        }
    }

    if (achou == 1)
        return EXCLU_ALU_SUCESSO;
    else
        return MATRICULA_INEXISTENTE;
}

int excluirProfessor(Professor listaProfessor[], int qtdProfessor)
{
    printf("Excluir professor\n");
    printf("Digite a matricula: \n");
    int matricula;
    scanf("%d", &matricula);
    int achou = 0;

    if (matricula < 0)
        return MATRICULA_INVALIDA;

    for (int i = 0; i < qtdProfessor; i++)
    {
        if (matricula == listaProfessor[i].matricula)
        {
            listaProfessor[i].ativo = -1;
            for (int j = i; j < qtdProfessor - 1; j++)
            {
                listaProfessor[j].matricula = listaProfessor[j + 1].matricula;
                listaProfessor[j].ativo = listaProfessor[j + 1].ativo;
            }
            achou = 1;
            break;
        }
    }

    if (achou == 1)
        return EXCLU_PROF_SUCESSO;
    else
        return MATRICULA_INEXISTENTE;
}
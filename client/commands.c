#include "utils.h"
#include "commands.h"
#include "comm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addExperience(void)
{
    // TODO:
    // 1) get input:
    //      - email (string?)
    //      - experience (string?)
    // 2) send update to server database
    UserProfile input;
    ProtocolData comando;

    comando.op = UPDATE;
    comando.profiles_num = 1;

    puts("Voce escolheu *ADICIONAR EXPERIENCIA*. Por favor, forneca um email seguido de apenas uma experiencia\n");
    scanf("%s", input.email);
    scanf("%s", input.experiencia[0]);
    client_connect(comando, input, 0); // Alterar o ponteiro para int de forma adequada
}

void listPeopleByMajor(void)
{
    // TODO:
    // 1) get input: major (string?)
    // 2.0) queue server database for profiles with the major.
    // 2.1) queue server for database
    // 2.1.1) filter database by major
    // 3) show profiles found with Email and Name
    UserProfile input;
    ProtocolData comando;
    UserProfile *output;
    int count = 0;
    int *n_profiles = malloc(sizeof(int));

    puts("Voce escolheu *LISTAR POR FORMACAO*. Por favor, forneca uma formacao\n");
    comando.op = READ;
    scanf("%s", input.formacao);
    output = client_connect(comando, input, n_profiles);

    for (int i = 0; i < *n_profiles; i++)
    {
        if (strcmp(output[i].formacao, input.formacao) == 0)
        {
            printf("*****\nEmail: %s\nNome: %s\n", output[i].email, output[i].nome);
            count++;
        }        
    }
    
    printf("Encontrados %d perfis no total!\n", count);
}

void listPeopleBySkill(void)
{
    // TODO:
    // 1) get input: skill (string?)
    // 2.0) queue server database for profiles with the skill.
    // 2.1) queue server for database
    // 2.1.1) filter database by skill
    // 3) show profiles found with Email and Name
    UserProfile input;
    ProtocolData comando;
    UserProfile *output;
    int count = 0;
    int *n_profiles = malloc(sizeof(int));

    puts("Voce escolheu *LISTAR POR HABILIDADE*. Por favor, forneca uma habilidade\n");
    comando.op = READ;
    scanf("%s", input.habilidades);
    output = client_connect(comando, input, n_profiles);

    for (int i = 0; i < *n_profiles; i++)
    {
        if (strstr(output[i].habilidades, input.habilidades) != NULL) // Procura substring
        {
            printf("*****\nEmail: %s\nNome: %s\n", output[i].email, output[i].nome);
            count++;
        }
    }
    
    printf("Encontrados %d perfis no total!\n", count);
}

void listPeopleByGradYear(void)
{
    // TODO:
    // 1) get input: major (string?)
    // 2.0) queue server database for profiles with the major.
    // 2.1) queue server for database
    // 2.1.1) filter database by major
    // 3) show profiles found with Email, Name and Major
    UserProfile input;
    ProtocolData comando;
    UserProfile *output;
    int count = 0;
    int *n_profiles = malloc(sizeof(int));

    puts("Voce escolheu *LISTAR POR ANO DE FORMATURA*. Por favor, forneca um ano\n");
    comando.op = READ;
    scanf("%u", &input.ano_formatura);
    output = client_connect(comando, input, n_profiles);

    for (int i = 0; i < *n_profiles; i++)
    {
        if (output[i].ano_formatura == input.ano_formatura) 
        {
            printf("*****\nEmail: %s\nNome: %s\nCurso: %s\n", output[i].email, output[i].nome, 
            output[i].formacao);
            count++;
        }
    }
    
    printf("Encontrados %d perfis no total!\n", count);
}

void listAll(void)
{
    // TODO:
    // 1) queue server for whole database.
    // 2) show profiles with all info
    // 
    // example:
    //
    // Email: maria_silva@gmail.com
    // Nome: Maria
    // Sobrenome: Silva
    // Residência: Campinas
    // Formação Acadêmica: Ciência da Computação
    // Ano de Formatura: 2015
    // Habilidades: Análise de Dados, Internet das Coisas, Computação em Nuvem
    // Experiência: (1) Estágio de 1 ano na Empresa X, onde trabalhei como analista de dados
    //              (2) Trabalhei com IoT e Computação em Nuvem por 5 anos na Empresa Y
    UserProfile input;
    ProtocolData comando;
    UserProfile *output;
    int count = 0;
    int *n_profiles = malloc(sizeof(int));

    puts("Voce escolheu *LISTAR TODOS PERFIS*\n");
    comando.op = READ;
    output = client_connect(comando, input, n_profiles);

    for (int i = 0; i < *n_profiles; i++)
    {
        printf("*****\nEmail: %s\nNome: %s\nSobrenome: %s\nResidencia: %s\nFormacao: %s\n\
        Ano de formatura: %d\nHabilidades: %s\nExperiências: ",
        output[i].email, output[i].nome, 
        output[i].sobrenome, output[i].residencia, output[i].formacao, output[i].ano_formatura,
        output[i].habilidades);
        count++;
        if(output[i].n_experiencia > 0){
            for (int j = 0; j < output[i].n_experiencia; j++)
            {
                printf("(%d) %s\n", j+1, output[i].experiencia[j]);
            }
        } else{
            printf("Nenhuma!\n");
        }
    }
    
    printf("Foram listados %d perfis no total!\n", count);
}

void retrieveProfileInfo(void)
{
    // TODO:
    // 1) get input: email (string?)
    // 2.0) queue server database for profile with email.
    // 2.1) queue server for database
    // 2.1.1) find specified email in data
    // 3) show profile with all info
    //
    // example:
    //
    // Email: maria_silva@gmail.com
    // Nome: Maria
    // Sobrenome: Silva
    // Residência: Campinas
    // Formação Acadêmica: Ciência da Computação
    // Ano de Formatura: 2015
    // Habilidades: Análise de Dados, Internet das Coisas, Computação em Nuvem
    // Experiência: (1) Estágio de 1 ano na Empresa X, onde trabalhei como analista de dados
    //              (2) Trabalhei com IoT e Computação em Nuvem por 5 anos na Empresa Y
    UserProfile input;
    ProtocolData comando;
    UserProfile *output;
    int *n_profiles = malloc(sizeof(int));

    puts("Voce escolheu *LISTAR TODOS PERFIS*\n");
    comando.op = READ;
    output = client_connect(comando, input, n_profiles);

    for (int i = 0; i < *n_profiles; i++)
    {
        if (strcmp(input.email, output[i].email) == 0) 
        {
            printf("*****\nEmail: %s\nNome: %s\nSobrenome: %s\nResidencia: %s\nFormacao: %s\n\
            Ano de formatura: %d\nHabilidades: %s\nExperiências: ",
            output[i].email, output[i].nome, 
            output[i].sobrenome, output[i].residencia, output[i].formacao, output[i].ano_formatura,
            output[i].habilidades);
            if(output[i].n_experiencia > 0){
                for (int j = 0; j < output[i].n_experiencia; j++)
                {
                    printf("(%d) %s\n", j+1, output[i].experiencia[j]);
                }
            } else{
                printf("Nenhuma!\n");
            }
        }
        break;
    }
}

void deleteProfile(void)
{
    // TODO:
    // 1) get input: email (string?)
    // 2) send deletion request to server
    UserProfile input;
    ProtocolData comando;
    //UserProfile *output;
    int *n_profiles = malloc(sizeof(int));

    puts("Voce escolheu *EXCLUIR PERFIL*. Por favor, forneca um email\n");
    scanf("%s", input.email);
    comando.op = DELETE;
    client_connect(comando, input, n_profiles);

    if (1) // adicionar codigo de erro aqui
    {
        puts("Sucesso!\n");
    } else{
        puts("Falha!\n");
    }
}

void registerProfile(void)
{
    // TODO:
    // 1) get input:
    //      - email (string)
    //      - nome (string)
    //      - sobrenome (string)
    //      - residência (string)
    //      - formação academica (string)
    //      - ano de formatura (int?string?)
    //      - habilidades
    //      - experiência
    UserProfile input;
    ProtocolData comando;
    //UserProfile *output;
    int *n_profiles = malloc(sizeof(int)); // Variavel coringa para n de profiles retornados. pode ser usada para erro?

    puts("Voce escolheu *ADICIONAR NOVO PERFIL*. Por favor, forneca os dados conforme requisitado:\n");
    puts("Email:\n");
    scanf("%s", input.email);
    puts("Nome:\n");
    scanf("%s", input.nome);
    puts("Sobrenome:\n");
    scanf("%s", input.sobrenome);
    puts("Residencia:\n");
    scanf("%s", input.residencia);
    puts("Formacao Academica:\n");
    scanf("%s", input.formacao);
    puts("Ano de formatura:\n");
    scanf("%u", &input.ano_formatura);
    puts("Habilidades:\n");
    scanf("%s", input.habilidades);
    puts("Quantas experiencias quer inserir? (0-20):\n");
    scanf("%u", &input.n_experiencia);
    for (int i = 0; i < input.n_experiencia; i++)
    {
        printf("Insira experiencia #%d:\n", i+1);
        scanf("%s", input.experiencia[i]);
    }
    
    comando.op = CREATE;
    client_connect(comando, input, n_profiles);

    if (1) // adicionar codigo de erro aqui
    {
        puts("Sucesso!\n");
    } else{
        puts("Falha!\n");
    }
}

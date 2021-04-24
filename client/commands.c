#include "utils.h"
#include "commands.h"

void addExperience(void)
{
    // TODO:
    // 1) get input:
    //      - email (string?)
    //      - experience (string?)
    // 2) send update to server database
}

void listPeopleByMajor(void)
{
    // TODO:
    // 1) get input: major (string?)
    // 2.0) queue server database for profiles with the major.
    // 2.1) queue server for database
    // 2.1.1) filter database by major
    // 3) show profiles found with Email and Name
}

void listPeopleBySkill(void)
{
    // TODO:
    // 1) get input: skill (string?)
    // 2.0) queue server database for profiles with the skill.
    // 2.1) queue server for database
    // 2.1.1) filter database by skill
    // 3) show profiles found with Email and Name
}

void listPeopleByGradYear(void)
{
    // TODO:
    // 1) get input: major (string?)
    // 2.0) queue server database for profiles with the major.
    // 2.1) queue server for database
    // 2.1.1) filter database by major
    // 3) show profiles found with Email, Name and Major
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
}

void deleteProfile(void)
{
    // TODO:
    // 1) get input: email (string?)
    // 2) send deletion request to server
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
}

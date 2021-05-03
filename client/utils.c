#include "utils.h"

#include <stdio.h>
#include <string.h>

AccountType login(void)
{
    puts("Bem vindo!");

    // TODO: get input user
    // select account type based on user input
    // Q: should the user be already registered to be able to access? 
    //    (request the server for the user or allow anything?)

    char acc_type[6];

    puts("Por favor, insira o tipo de usuario. Opcoes: (admin, user):\n");
    do{
        scanf("%s", acc_type);
    } while(strcmp(acc_type,"user") != 0 || strcmp(acc_type,"admin") != 0);
  
    if(strcmp(acc_type,"user") == 0)
        return USER;

    return ADMIN;
}

int showMenu(AccountType accountType)
{
    puts("O que deseja fazer?");
    puts("0 - sair");
    puts("1 - acrescentar uma nova experiência profissional em um perfil;");
    puts("2 - listar todas as pessoas(email e nome) formadas em um determinado curso;");
    puts("3 - listar todas as pessoas(email e nome) que possuam uma determinada habilidade;");
    puts("4 - listar todas as pessoas(email, nome e curso) formadas em um determinado ano;");
    puts("5 - listar todas as informações de todos os perfis;");
    puts("6 - dado o email de um perfil, retornar suas informações;");
    if (accountType == ADMIN)
    {
        puts("7 - remover um perfil a partir de seu identificador(email).");
        puts("8 - cadastrar um novo perfil utilizando o email como identificador;");
    }

    return getchar();
}


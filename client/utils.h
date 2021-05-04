#pragma once
#include "comm.h"

#include <stdio.h>

typedef enum _AccountType
{
    ADMIN,
    USER
} AccountType;

char *fgetss(char *dest, int n, FILE *stream);

// show an option menu with choice by number and returns a char with the user input
int showMenu(AccountType accountType);

// handles user login and return its account type (admin or user)
AccountType login(void);

// TODO: add functions to handle server connection
UserProfile *client_connect(ProtocolData comando, UserProfile prof_buf, int *n_profiles);
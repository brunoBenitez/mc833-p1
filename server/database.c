#include "database.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <error.h>
#include <errno.h>
#include <dirent.h>

#define GET_FILENAME(str, email) sprintf(str, "data/%s.db", email);

// creates an entry for profile in database
// parameters:
//  profile: the profile to add to database
// return:
//  1 if succeeded, 0 if not
int create_user(UserProfile *profile)
{
    char filename[MAX_CHARS];
    FILE *db_file;
    int success = 1;

    if (profile)
    {
        GET_FILENAME(filename, profile->email);
        strcat(filename, profile->email);
        db_file = fopen(filename, "w");

        flockfile(db_file);

        fprintf(db_file, "nome: %s\n", profile->nome);
        fprintf(db_file, "sobrenome: %s\n", profile->sobrenome);
        fprintf(db_file, "residencia: %s\n", profile->residencia);
        fprintf(db_file, "formacao: %s\n", profile->formacao);
        fprintf(db_file, "ano_formatura: %s\n", profile->ano_formatura);
        fprintf(db_file, "habilidades: %s\n", profile->habilidades);
        fprintf(db_file, "experiencias:\n");
        for (int32_t i = 0; i < profile->n_experiencia; i++)
        {
            fprintf(db_file, "%s\n", profile->experiencia[i]);
        }

        funlockfile(db_file);
        fclose(db_file);
    }
    else
    {
        success = 0;
        fprintf(stderr, "invalid profile received at: %s\n", __FUNCTION__);
    }

    return success;
}

// reads database
// parameters:
//  profile: receives an array of the user profiles stored in database. Memory should be released by user.
// return:
//  number of entries in array if succeeded, -1 if failed.
int read_db(UserProfile **profile)
{
    DIR *data_dir;
    struct dirent *dir_entry;
    FILE *current_file;
    UserProfile *users;
    size_t n_files = 0;

    data_dir = opendir("data");
    if (data_dir)
    {
        while ((dir_entry = readdir(data_dir)) != NULL)
        {
            dir_entry->d_name;
            // TODO:
            n_files++;
        }
        closedir(data_dir);

        // TODO:

        flockfile(current_file);

        // TODO:

        funlockfile(current_file);
    }
    else
    {
        n_files = -1;
        perror("Error opening directory \"data\" to read database");
    }

    return n_files;
}

// updates a profile entry in database
// parameters:
//  profile: the profile to update, identified by its email which has the updated values
// return:
//  1 if succeded, 0 if not
int update_user(UserProfile *profile)
{
    char filename[MAX_CHARS];
    FILE *db_file;
    int success = 1;
    if (profile)
    {
        GET_FILENAME(filename, profile->email);
        db_file = fopen(profile->email, "r");
        if (db_file)
        {
            db_file = freopen(NULL, "a", db_file);
            if (db_file)
            {
                flockfile(db_file);

                fputs(profile->experiencia[0], db_file);

                funlockfile(db_file);
                fclose(db_file);
            }
            else
            {
                success = 0;
                perror("error trying to reopen file to append");
            }
                }
        else
        {
            success = 0;
            fprintf(stderr, "file %s not found\n", filename);
        }
    }
    else
    {
        success = 0;
        fprintf(stderr, "invalid profile received at: %s\n", __FUNCTION__);
    }
    return success;
}

// deletes a profile entry from database
// paramenters:
//  profile: the profile to delete, identified by its email
// return:
//  1 if succeeded, 0 if not.
int delete_user(UserProfile *profile)
{
    char filename[MAX_CHARS];
    FILE *db_file;
    int success = 1;
    if (profile)
    {
        GET_FILENAME(filename, profile->email);
        if (remove(filename) != 0)
        {
            success = 0;
            fprintf(stderr, "failed to remove file for %s", profile->email);
        }
    }
    else
    {
        success = 0;
        fprintf(stderr, "invalid profile received at: %s", __FUNCTION__);
    }
    return success;
}

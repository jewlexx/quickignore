//
// Created by Juliette Cordor on 6/04/2023.
//

#ifndef CIGNORE_ARGS_H
#define CIGNORE_ARGS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "slicing.h"

typedef struct {
    char *name;
    char *path;
    char *url;
} IgnoreFile;

void parse_arg(IgnoreFile *file, char *arg, char *next);

char *full_arg(const char flag);

IgnoreFile parse_args(int argc, char *argv[]);

#endif //CIGNORE_ARGS_H

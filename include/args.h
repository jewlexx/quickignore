//
// Created by Juliette Cordor on 6/04/2023.
//

#ifndef QUICKIGNORE_ARGS_H
#define QUICKIGNORE_ARGS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "slicing.h"

typedef struct {
  char *name;
  char *path;
  char *url;
} IgnoreFile;

void usage(int status);

void parse_arg(IgnoreFile *file, char *arg, char *next);

char *full_arg(const char flag);

IgnoreFile parse_args(int argc, char *argv[]);

#endif // QUICKIGNORE_ARGS_H

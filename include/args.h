//
// Created by Juliette Cordor on 6/04/2023.
//

#ifndef QUICKIGNORE_ARGS_H
#define QUICKIGNORE_ARGS_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *path;
    char *url;
} IgnoreFile;

void usage(int status);

IgnoreFile parse_args(int argc, char *argv[]);

#endif // QUICKIGNORE_ARGS_H

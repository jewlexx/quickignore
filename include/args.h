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
} IgnoreArgs;

void usage(int status);

/**
 * @brief Parse command line arguments
 *
 * @param argc
 * @param argv
 * @return
 */
IgnoreArgs parse_args(int argc, char *argv[]);

#endif // QUICKIGNORE_ARGS_H

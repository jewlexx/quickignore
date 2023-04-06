//
// Created by Juliette Cordor on 6/04/2023.
//


#include <stdio.h>

#include "../include/args.h"

int main(int argc, char *argv[]) {
    IgnoreFile file = parse_args(argc, argv);

    printf("url: %s\n", file.url);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/slicing.h"
#include "../include/args.h"

int main(int argc, char *argv[]) {
    int arg_count = argc - 1;
    char *args;
//    slice_char_array();
    IgnoreFile file = parse_args(argc, argv);

    printf("url: %s\n", file.url);

    return 0;
}

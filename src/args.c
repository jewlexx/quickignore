//
// Created by Juliette Cordor on 6/04/2023.
//

#include "../include/args.h"

void parse_arg(IgnoreFile *file, char *arg, char *next) {
    if (strcmp(arg, "name") == 0) {
        file->name = next;
    } else if (strcmp(arg, "path") == 0) {
        file->path = next;
    }
}

char *full_arg(const char flag) {
    switch (flag) {
        case 'n':
            return "name";
        case 'p':
            return "path";
    }
}


IgnoreFile parse_args(int argc, char *argv[]) {
    IgnoreFile file = {
            .name = NULL,
            .url = NULL,
            .path = NULL,
    };

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == '-') {
                char *arg_name = malloc(sizeof(char) * strlen(argv[i] - 2));
                slice(argv[i], arg_name, 2, strlen(argv[i] - 2));

                parse_arg(&file, arg_name, argv[i + 1]);
            } else {
                char *full = full_arg(argv[i][1]);
                parse_arg(&file, full, argv[i + 1]);
            }
        } else {
            file.name = argv[i];
        }
    }

    char *base_url = "https://www.toptal.com/developers/gitignore/api/";
    size_t total_url_size = strlen(file.name) + strlen(base_url);

    file.url = malloc(sizeof(char) * total_url_size);
    file.url = strcat(file.url, base_url);
    file.url = strcat(file.url, file.name);

    printf("name: %s\n", file.name);
    printf("url: %s\n", file.url);
    printf("url len: %zu\n", total_url_size);
    printf("path: %s\n", file.path);

    return file;
}
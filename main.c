#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    char *path;
    char *url;
} IgnoreFile;

void slice(const char *str, char *result, size_t start, size_t end) {
    strncpy(result, str + start, end - start);
}

void slice_char_array(char *array, char *result, size_t start, size_t end) {
    for (size_t i = start; i < end; i++) {
        memcpy(result + i - start, array + i, sizeof(char));
    }
}

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

int main(int argc, char *argv[]) {
    int arg_count = argc - 1;
    char *args;
    slice_char_array();
    IgnoreFile file = parse_args(argc, argv);

    printf("url: %s\n", file.url);

    return 0;
}

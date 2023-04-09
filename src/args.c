//
// Created by Juliette Cordor on 6/04/2023.
//

#include "../include/args.h"

static int remove_file = 0;

void usage(int status) {
    printf("usage: quickignore <URL> [OPTION]\n");

    printf("\t-n, --name=TEMPLATE\t"
           "Name of the template to grab. Can be a comma seperated list\n");

    printf("\t-p, --path=STRING\t"
           "File path to write the gitignore to\n");

    printf("\t--overwrite\t"
           "Overwrite any existing gitignore file. By default will just append "
           "to the existing file\n");

    printf("\t-h, --help\t\t"
           "Print this help and exit.\n");

    exit(status);
}

IgnoreFile parse_args(int argc, char *argv[]) {
    IgnoreFile file = {
            .url = NULL,
            .path = ".gitignore",
    };
    int help_flag = 0;
    char *name = NULL;

    struct option long_opts[] = {
            {"help",      no_argument, &help_flag, 1},
            {"name",      required_argument, NULL, 'n'},
            {"path",      required_argument, NULL, 'p'},
            {"overwrite", no_argument,       NULL, 'o'},
    };

    int opt;

    while (1) {
        opt = getopt_long(argc, argv, "n:p:oh", long_opts, NULL);

        // No more options
        if (opt == -1) {
            break;
        }

        switch (opt) {
            case 'h':
                help_flag = 1;

                break;
            case 'n': {
                size_t len = strlen(optarg) + 1;
                name = malloc(sizeof(char) * len);
                strncpy(name, optarg, len);
                name[sizeof(name) - 1] = '\0';
            }
                break;
            case 'p':
                if (optarg != NULL) {
                    size_t len = strlen(optarg) + 1 * sizeof(char);
                    file.path = malloc(len * sizeof(char));
                    strncpy(file.path, optarg, strlen(optarg));
                    file.path[strlen(file.path)] = '\0';
                }
                break;
            case 'o':
                remove_file = 1;
                break;
            case '?':
                usage(1);
                break;
            default:
                break;
        }
    }

    // for (int i = 1; i < argc; i++) {
    //   char *arg = argv[i];

    //   if (arg[0] == '-') {
    //     if (arg[1] == '-') {
    //       char *arg_name = malloc(sizeof(char) * (strlen(arg) - 2));
    //       slice(arg, arg_name, 2, strlen(arg));

    //       parse_arg(&file, arg_name, argv[i + 1]);
    //       free(arg_name);
    //     } else {
    //       char *full = full_arg(arg[1]);
    //       parse_arg(&file, full, argv[i + 1]);
    //     }
    //   }
    // }

    char *base_url = "https://www.toptal.com/developers/gitignore/api/";
    size_t total_url_size = strlen(name) + strlen(base_url);

    file.url = malloc(sizeof(char) * (total_url_size + 1));

    for (int i = 0; i < strlen(base_url); i++) {
        file.url[i] = base_url[i];
    }
    for (int i = 48; i < total_url_size; i++) {
        char next = name[i - 48];
        file.url[i] = next;
    }
    // Append null character
    file.url[total_url_size] = '\0';

    printf("name: %s\n", name);
    printf("url: %s\n", file.url);
    printf("url len: %zu\n", total_url_size);
    printf("path: %s\n", file.path);

    if (remove_file) {
        exit(remove(file.path));
    }

    return file;
}
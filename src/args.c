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
         "Overwrite any existing gitignore file\n");

  printf("\t-h, --help\t\t"
         "Print this help and exit.\n");

  exit(status);
}

void parse_arg(IgnoreFile *file, char *arg, char *next) {
  if (strcmp(arg, "help") == 0) {
    usage(0);
  } else if (strcmp(arg, "name") == 0) {
    file->name = next;
  } else if (strcmp(arg, "path") == 0) {
    file->path = next;
  } else if (strcmp(arg, "overwrite") == 0) {
    remove_file = 1;
  }
}

char *full_arg(const char flag) {
  switch (flag) {
  case 'h':
    return "help";
  case 'n':
    return "name";
  case 'p':
    return "path";
  default:
    perror("Unknown flag");
    usage(1);
    // Return nothing to hush compiler warnings.
    // Will ALWAYS exit before this line
    return NULL;
  }
}

IgnoreFile parse_args(int argc, char *argv[]) {
  IgnoreFile file = {
      .name = NULL,
      .url = NULL,
      .path = ".gitignore",
  };

  for (int i = 1; i < argc; i++) {
    char *arg = argv[i];

    if (arg[0] == '-') {
      if (arg[1] == '-') {
        char *arg_name = malloc(sizeof(char) * (strlen(arg) - 2));
        slice(arg, arg_name, 2, strlen(arg));

        parse_arg(&file, arg_name, argv[i + 1]);
        free(arg_name);
      } else {
        char *full = full_arg(arg[1]);
        parse_arg(&file, full, argv[i + 1]);
      }
    }
  }

  char *base_url = "https://www.toptal.com/developers/gitignore/api/";
  size_t total_url_size = strlen(file.name) + strlen(base_url);

  file.url = malloc(sizeof(char) * (total_url_size + 1));

  for (int i = 0; i < strlen(base_url); i++) {
    file.url[i] = base_url[i];
  }
  for (int i = 48; i < total_url_size; i++) {
    char next = file.name[i - 48];
    file.url[i] = next;
  }
  // Append null character
  file.url[total_url_size] = '\0';

  printf("name: %s\n", file.name);
  printf("url: %s\n", file.url);
  printf("url len: %zu\n", total_url_size);
  printf("path: %s\n", file.path);

  if (remove_file) {
    exit(remove(file.path));
  }

  return file;
}
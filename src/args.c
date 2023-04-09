//
// Created by Juliette Cordor on 6/04/2023.
//

#include "../include/args.h"

void usage() {
  printf("usage: quickignore [OPTION]\n");
  printf("  -h, --help\t\t"
         "Print this help and exit.\n");
  printf("  -f, --file[=FILENAME]\t"
         "Write all output to a file (defaults to out.txt).\n");
  printf("  -m, --msg=STRING\t"
         "Output a particular message rather than 'Hello world'.\n");

  exit(0);
}

void parse_arg(IgnoreFile *file, char *arg, char *next) {
  if (strcmp(arg, "name") == 0) {
    file->name = next;
  } else if (strcmp(arg, "path") == 0) {
    file->path = next;
  } else if (strcmp(arg, "help") == 0) {
    usage();
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
        char *arg_name = malloc(sizeof(char) * (strlen(argv[i]) - 2));
        slice(argv[i], arg_name, 2, strlen(argv[i]) - 2);

        parse_arg(&file, arg_name, argv[i + 1]);
        free(arg_name);
      } else {
        char *full = full_arg(argv[i][1]);
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

  return file;
}
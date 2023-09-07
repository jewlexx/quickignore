//
// Created by Juliette Cordor on 6/04/2023.
//

#include "../include/args.h"

static int remove_file = 0;

void usage(int status) {
  printf("Downloads the provided template from gitignore.io\n");
  printf("usage: quickignore <TEMPLATES> [OPTIONS]\n");

  printf("\t-p, --path[=STRING]\t"
         "File path to write the gitignore to\n");

  printf("\t--overwrite\t"
         "Overwrite any existing gitignore file. By default will just append "
         "to the existing file\n");

  printf("\t-h, --help\t\t"
         "Print this help and exit.\n");

  exit(status);
}

IgnoreArgs parse_args(int argc, char *argv[]) {
  IgnoreArgs file = {
      .url = NULL,
      .path = ".gitignore",
  };
  int help_flag = 0;

  char *templates = argv[1];

  if (templates == NULL) {
    perror("Missing templates");
    usage(1);
  }
  if (templates[0] == '-') {
    perror("Templates must come before any options");
    usage(1);
  }

  struct option long_opts[] = {
      {"help", no_argument, &help_flag, 1},
      {"path", required_argument, NULL, 'p'},
      {"overwrite", no_argument, NULL, 'o'},
  };

  int opt;

  while (1) {
    opt = getopt_long(argc, argv, "p:oh", long_opts, NULL);

    // No more options
    if (opt == -1) {
      break;
    }

    switch (opt) {
    case 'h':
      help_flag = 1;
      break;
    case 'p':
      if (optarg != NULL) {
        size_t len = strlen(optarg) + 1 * sizeof(char);
        file.path = calloc(len, sizeof(char));
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

  if (help_flag) {
    usage(0);
  }

  char *base_url = "https://www.toptal.com/developers/gitignore/api/";
  size_t total_url_size = strlen(templates) + strlen(base_url);

  file.url = calloc(total_url_size + 1, sizeof(char));

  for (int i = 0; i < strlen(base_url); i++) {
    file.url[i] = base_url[i];
  }
  for (int i = 48; i < total_url_size; i++) {
    char next = templates[i - 48];
    file.url[i] = next;
  }
  // Append null character
  file.url[total_url_size] = '\0';

  if (remove_file) {
    exit(remove(file.path));
  }

  return file;
}
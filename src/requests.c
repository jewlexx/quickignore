//
// Created by Juliette Cordor on 6/04/2023.
//

#include "../include/requests.h"
#include "../include/args.h"

IgnoreFile *args;
char *path;

size_t write_data(void *buff, size_t size, size_t nmemb, void *userp) {
  printf("Writing");
  FILE *fp = fopen(args->path, "a");

  if (fp == NULL) {
    perror("failed to open file\n");
    exit(1);
  }

  size_t written = fwrite(buff, size, nmemb, fp);

  if (fclose(fp)) /* Close the stream. */
    perror("failed to close file");

  return written;
}

void request_url(IgnoreFile *file) {
  args = file;
  char *url = file->url;
  if (url == NULL) {
    printf("request_url: url is null\n");
    return;
  }

  path = file->path;
  if (path == NULL) {
    printf("request_url: path is null\n");
    return;
  }

  printf("initializing curl\n");
  curl_global_cleanup();
  CURL *curl = curl_easy_init();
  printf("Initialized CURL\n");
  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
  CURLcode success = curl_easy_perform(curl);
  printf("Performed request\n");

  printf("Exit Code: %d\n", success);
  const char *err_desc = curl_easy_strerror(success);

  printf("Error: %s\n", err_desc);

  curl_easy_cleanup(curl);
  curl_global_cleanup();
}
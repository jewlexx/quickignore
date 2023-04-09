//
// Created by Juliette Cordor on 6/04/2023.
//

#include "../include/requests.h"

char *path;

size_t write_data(void *buff, size_t size, size_t nmemb, void *userp) {
  FILE *fp = fopen("rustignore.txt", "w");

  if (fp == NULL) {
    printf("write_data: fp is null\n");
    exit(1);
  }

  fwrite(buff, size, nmemb, fp);

  fclose(fp);
}

void request_url(IgnoreFile *file) {
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

  curl_easy_cleanup(curl);
  curl_global_cleanup();
}
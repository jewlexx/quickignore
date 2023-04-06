//
// Created by Juliette Cordor on 6/04/2023.
//

#include <curl/curl.h>

#include "../include/requests.h"

static FILE *fp;

size_t write_data(void *buff, size_t size, size_t nmemb, void *userp) {
    if (fp == NULL) {
        printf("write_data: fp is null\n");
        exit(1);
    }

    fwrite(buff, size, nmemb, fp);
}

void request_url(IgnoreFile *file) {
    char *url = file->url;
    if (url == NULL) {
        return;
    }

    char *path = file->path;
    if (path == NULL) {
        return;
    }

    fp = fopen(path, "a");

    CURL *curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    CURLcode success = curl_easy_perform(curl);

    fclose(fp);
}
//
// Created by Juliette Cordor on 6/04/2023.
//

#include "../include/requests.h"

char *path;

typedef struct {
    IgnoreFile *args;
    FILE *fp;
} OutputData;

size_t write_data(void *buff, size_t size, size_t nmemb, FILE *userp) {
    FILE *fp = userp->fp;

    if (fp == NULL) {
        perror("failed to open file\n");
        exit(1);
    }

    size_t written = fwrite(buff, size, nmemb, fp);

    if (fclose(fp)) /* Close the stream. */ {
        perror("failed to close file");
        exit(1);
    }

    return written;
}

void request_url(IgnoreFile *file) {
    if (file->url == NULL) {
        printf("request_url: url is null\n");
        return;
    }

    if (file->path == NULL) {
        printf("request_url: path is null\n");
        return;
    }

    FILE *fp = fopen(file->path, "a");

    curl_global_cleanup();
    CURL *curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, file->url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    CURLcode error = curl_easy_perform(curl);

    int to_exit = 0;

    if (fclose(fp)) {
        perror("failed to close file");
        to_exit = 1;
    }

    if (error != CURLE_OK) {
        const char *err_desc = curl_easy_strerror(error);
        printf("%s\n", err_desc);
        to_exit = 1;
    }

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    if (to_exit) {
        exit(1);
    }
}
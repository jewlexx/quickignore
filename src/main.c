//
// Created by Juliette Cordor on 6/04/2023.
//

#include <curl/curl.h>

#include "../include/requests.h"
#include "../include/args.h"

int main(int argc, char *argv[]) {
    IgnoreFile file = parse_args(argc, argv);

    curl_global_init(CURL_GLOBAL_WIN32 | CURL_GLOBAL_SSL);

    request_url(&file);

    curl_global_cleanup();

    return 0;
}

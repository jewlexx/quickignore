//
// Created by Juliette Cordor on 6/04/2023.
//

#include <curl/curl.h>

#include "../include/args.h"
#include "../include/requests.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printf("Usage: %s <url>\n", argv[0]);
        return 1;
    }

    curl_global_init(CURL_GLOBAL_DEFAULT);

    printf("Parsing args\n");
    IgnoreFile file = parse_args(argc, argv);
    printf("Parsed args\n");

    request_url(&file);

    curl_global_cleanup();

    return 0;
}

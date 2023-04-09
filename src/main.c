//
// Created by Juliette Cordor on 6/04/2023.
//

#include "../include/args.h"
#include "../include/requests.h"

int main(int argc, char *argv[]) {
    if (argc == 1) {
        usage(1);
        return 1;
    }

    IgnoreFile file = parse_args(argc, argv);

    request_url(&file);

    return 0;
}

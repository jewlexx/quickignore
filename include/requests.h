#ifndef QUICKIGNORE_REQUESTS_H
#define QUICKIGNORE_REQUESTS_H

#include <curl/curl.h>

#include "args.h"

/**
 * @brief Request a template from the given command line arguments.
 *
 * @param file
 */
void request_url(IgnoreArgs *file);

#endif // QUICKIGNORE_REQUESTS_H

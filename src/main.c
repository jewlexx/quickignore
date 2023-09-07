#include "../include/args.h"
#include "../include/requests.h"

int main(int argc, char *argv[]) {
  if (argc == 1) {
    usage(1);
    return 1;
  }

  IgnoreArgs args = parse_args(argc, argv);

  request_url(&args);

  return 0;
}

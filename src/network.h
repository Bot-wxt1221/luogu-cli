#ifndef HEADERS_LUOGU_CLI_NETWORK
#define HEADERS_LUOGU_CLI_NETWORK

#include "secret.h"
#include <stdbool.h>

bool isUserOK(struct user t);

void submitProblem(struct user t,char *problem,char *file);

int curlInit();

#endif

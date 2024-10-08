#ifndef HEADERS_LUOGU_CLI_SECRET
#define HEADERS_LUOGU_CLI_SECRET

#include <libsecret/secret.h>
struct user{
  char key[1005];
  int uid;
};
int getUser(struct user *t);

int storeUser(struct user t);

const SecretSchema *get_schema () G_GNUC_CONST;

#endif //HEADERS_LUOGU_CLI_SECRET

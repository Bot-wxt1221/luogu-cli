#include "secret.h"
#include <stdio.h>
#include <string.h>

int getUser(struct user *t){
  GError *error=NULL;
  gchar *password = secret_password_lookup_sync (get_schema(),
                                                 NULL,
                                                 &error,
                                                 "uid",t->uid,
                                                 NULL);
  if(error!=NULL){
    fprintf(stderr,"Failed to find the password!");
    g_error_free(error);
    return -1;
  }
  if(password==NULL){
    fprintf(stderr,"Failed to find the password!");
    g_error_free(error);
    return -2;
  }else{
    strcpy(t->key,password);
  }
  return 0;
}

int storeUser(struct user t){
  GError *error=NULL;
  secret_password_clear_sync(get_schema(),
                             NULL,
                             &error,
                             "uid",t.uid,
                             NULL);
  secret_password_store_sync(get_schema(),
                             SECRET_COLLECTION_DEFAULT,
                             "luogu-cli",t.key,NULL,&error,
                             "uid",t.uid,
                             NULL);
  if(error!=NULL){
    fprintf(stderr,"Failed to store the password!");
    g_error_free(error);
    return -1;
  }
  return 0;
}

const SecretSchema * get_schema(){
  static const SecretSchema schema = {
    "org.bot-wxt1221.luogu-cli", SECRET_SCHEMA_NONE,
    {
      {"uid",SECRET_SCHEMA_ATTRIBUTE_INTEGER},
      {"NULL",0},
    }
  };
  return &schema;
} 

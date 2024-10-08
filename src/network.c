#include "network.h"
#include <curl/curl.h>
#include <json-c/json.h>
#include <string.h>
#include "csrf.h"
#include <stdlib.h>

static char *buf;

static size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp){
  strcpy(buf,buffer);
  buf+=size*nmemb;
  return size*nmemb;
}

void submitProblem(struct user t,char *problem,char *file){
  char *buffer=malloc(2000*sizeof(char));
  char *buffer3=malloc(2000*sizeof(char));
  char *buffer2=malloc(200000*sizeof(char));
  char *buffer4=malloc(200000*sizeof(char));
  struct curl_slist *list=NULL;

  CURL *handle = curl_easy_init();
  char temp[]="{}";
  json_object *rootto=json_tokener_parse(temp);
  json_object_object_add(rootto,"enableO2",json_object_new_int(1));
  json_object_object_add(rootto,"lang",json_object_new_int(28));//C++14 (gcc 9)
  json_object_object_add(rootto,"code",json_object_new_string(file));

  sprintf(buffer4,"https://www.luogu.com.cn/problem/%s",problem);
  curl_easy_setopt(handle,CURLOPT_REFERER,buffer4);

  csrf(buffer4,buffer3,t);
  sprintf(buffer4,"X-Csrf-Token: %s",buffer3);
  list=curl_slist_append(list,buffer4);
  sprintf(buffer4,"Content-Type: application/json");
  list=curl_slist_append(list,buffer4);


  curl_easy_setopt(handle,CURLOPT_USERAGENT,"Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/129.0.0.0 Safari/537.36 Edg/129.0.0.0");

  curl_easy_setopt(handle,CURLOPT_HTTPHEADER,list);

  sprintf(buffer3,"https://www.luogu.com.cn/fe/api/problem/submit/%s",problem);
  curl_easy_setopt(handle,CURLOPT_URL,buffer3);
  curl_easy_setopt(handle,CURLOPT_POST,1L);
  sprintf(buffer,"_uid=%d; __client_id=%s;",t.uid,t.key);
  curl_easy_setopt(handle,CURLOPT_COOKIE,buffer);
  curl_easy_setopt(handle,CURLOPT_WRITEFUNCTION,write_data);
  curl_easy_setopt(handle,CURLOPT_POSTFIELDS,json_object_to_json_string_ext(rootto,JSON_C_TO_STRING_PLAIN));
  buf=buffer2;
  curl_easy_perform(handle);
  curl_easy_cleanup(handle);
  json_object_put(rootto);
  rootto=json_tokener_parse(buffer2);
  if(rootto==0){
    fprintf(stderr,"Error when parsing json\n");
    return ;
  }
  json_object *status=json_object_object_get(rootto,"rid");
  sprintf(buffer2,"xdg-open https://www.luogu.com.cn/record/%d",json_object_get_int(status));
  system(buffer2);
  end:{}
  free(buffer);
  free(buffer2);
  curl_slist_free_all(list);
  free(buffer3);
  json_object_put(rootto);
  free(buffer4);
  return ;
}

bool isUserOK(struct user t){
  char *buffer=malloc(2000*sizeof(char));
  char *buffer3=malloc(2000*sizeof(char));
  char *buffer2=malloc(200000*sizeof(char));
  //fetch something
  CURL *handle = curl_easy_init();
  sprintf(buffer3,"https://www.luogu.com.cn/api/user/blacklist?user=%d?page=1",t.uid);
  curl_easy_setopt(handle,CURLOPT_URL,buffer3);
  sprintf(buffer,"_uid=%d; __client_id=%s;",t.uid,t.key);
  curl_easy_setopt(handle,CURLOPT_COOKIE,buffer);
  curl_easy_setopt(handle,CURLOPT_WRITEFUNCTION,write_data);
  buf=buffer2;
  curl_easy_perform(handle);
  curl_easy_cleanup(handle);
  
  json_object *root=json_tokener_parse(buffer2);
  if(root==0){
    fprintf(stderr,"Error when prasing json");
    goto end;
  }
  json_object *status=json_object_object_get(root,"status");
  if(status){
    fprintf(stderr,"Error when fetching blacklist");
    goto end;
  }

  end:{}
  free(buffer);
  json_object_put(root);
  free(buffer3);
  free(buffer2);
  return 1;
}

int curlInit(){
  curl_global_init(CURL_GLOBAL_SSL);
  return 0;
}



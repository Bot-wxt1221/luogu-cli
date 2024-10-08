#include "csrf.h"
#include <string.h>
#include <curl/curl.h>
#include <stdbool.h>
#include <libxml/HTMLparser.h>

static char *buf;

static size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp){
  strcpy(buf,buffer);
  buf+=size*nmemb;
  return size*nmemb;
}
static void extract_links(xmlNode *a){
  if(a==NULL){
    return ;
  }
  while(a){
    xmlAttr *attr=a->properties;
    bool yes=0;
    while(attr){
      if(attr->children&&!xmlStrcmp(attr->children->content,(const xmlChar *)"csrf-token")){
        yes=1;
      }else if(attr->children&&yes){
        strcpy(buf,attr->children->content);
        yes=0;
      }
      attr=attr->next;
    }
    extract_links(a->children);
    a=a->next;
  }
}

void csrf(char *url,char *tar,struct user t){
  char *buffer=malloc(2000*sizeof(char));
  char *buffer2=malloc(200000*sizeof(char));

  CURL *handle = curl_easy_init();
  curl_easy_setopt(handle,CURLOPT_URL,url);
  sprintf(buffer,"_uid=%d; __client_id=%s;",t.uid,t.key);
  curl_easy_setopt(handle,CURLOPT_COOKIE,buffer);
  curl_easy_setopt(handle,CURLOPT_WRITEFUNCTION,write_data);
  buf=buffer2;
  curl_easy_perform(handle);
  curl_easy_cleanup(handle);
 
  htmlDocPtr doc;
  doc=htmlReadMemory(buffer2,buf-buffer2,NULL,NULL,HTML_PARSE_NOERROR);
  xmlNode *a=xmlDocGetRootElement(doc);

  extract_links(a);
  strcpy(tar,buf);

  xmlFreeDoc(doc);
  xmlCleanupParser();
  end:{}
  free(buffer);
  free(buffer2);
  return ;
}

#include <stdio.h>
#include "secret.h"
#include "network.h"
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <linux/stat.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>

void help(){
  printf("Luogu CLI written by Bot-wxt1221\n");
  return ;
}

char temp[1005];
int toint(char *x){
  int ret=0;
  while(*x!='\0'){
    ret=ret*10+((*x)^'0');
    x++;
  }
  return ret;
}

int main(int argc,char *argv[]){
  if(argc==1){
    help();
    return 0;
  }
  if(argc==2){
    help();
    return 0;
  }
  if(!strcmp(argv[1],"help")){
    help();
    return 0;
  }
  int error=curlInit();
  if(error!=0){
    fprintf(stderr,"Error when init curl!");
    return error;
  }
  struct user a;
  a.uid=toint(argv[1]);
  if(!strcmp(argv[2],"store")){
    strcpy(a.key,argv[3]);
    storeUser(a);
    return 0;
  }
  if(!strcmp(argv[2],"submit")){
    getUser(&a);
    int fd=open(argv[4],O_RDWR);
    if(fd<0){
      printf("Error opening file!");
      return -1;
    }
    struct stat buf;
    stat(argv[4],&buf);
    char *tt=mmap(NULL,buf.st_size,PROT_READ,MAP_SHARED,fd,0);
    submitProblem(a,argv[3],tt);
  }
  if(!strcmp(argv[2],"problem")){
    sprintf(temp,"xdg-open https://www.luogu.com.cn/problem/%s",argv[3]);
    system(temp);
  }
  return 0;
}

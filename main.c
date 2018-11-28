#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include<sys/wait.h> 

void pary(char ** strings){
  for (int x = 0; strings[x]; x++){
    printf("%s\n", strings[x]);
  }
}

char * toString(char ** args){
  char * ret_str = malloc(99999*sizeof(char));
  for (int x = 0; args[x]; x++){
    strcat(ret_str, args[x]);
  }

  return ret_str;
}

char ** toAry(char * args){
  char ** ret_ary = malloc(99999*sizeof(char *));
  int i = 0;
  while(args){
    char * next = strsep(&args, " ");
    ret_ary[i] = next;
    i++;
  }
  return ret_ary;
}

char * strip(char *s)
{
        size_t size;
        char *end;

        size = strlen(s);

        if (!size)
                return s;

        end = s + size - 1;
        while (end >= s && (*end == ' '))
                end--;
        *(end + 1) = '\0';

        while (*s && (*s == ' '))
                s++;

        return s;
}

int isEmpty(char * x){
  for (int i = 0; i < strlen(x); i++){
    if (x[i] != ' '){
      return 0;
    }
  }
  return 1;
}

int contains(char * str, char * sub){
  int sublen = strlen(sub);
  int strleng = strlen(str);
  for (int x = 0; x < strleng - sublen + 1; x++){
    int state_var = 1;
    for (int y = 0; y < sublen; y++){
      if (str[x+y] != sub[y]){
	state_var = 0;
      }
    }
    if (state_var) return 1;
  }
  return 0;
}

int sizeary(char ** x){
  int i = 0;
  while (*(x++)){
    i++;
  }
  return i;
}

int main(int argc, char * argv[]){
  pid_t wpid= 0;
  int status = 0;
  char** strings = malloc(sizeof(char*) * 9999);
  memcpy(strings, &argv[1], (argc-1) * sizeof(char *));
  char * str_args = toString(strings);
  //printf("%s\n", str_args);
  while(str_args){
    char * trunc_args = strsep(&str_args, ";");
    if (!isEmpty(trunc_args)){
      trunc_args = strip(trunc_args);
      char ** trunc_ary;
      // wiill make switch soon
	if (contains(trunc_args, "cd")){
	  printf("the adult here:%s\n", trunc_args);
	  trunc_ary = toAry(trunc_args);
	  //printf("cd test result: %d\n", sizeary(trunc_ary));
	  if (strcmp(trunc_ary[0], "cd") == 0 && sizeary(trunc_ary) > 1){
	    //printf("running\n");
	    printf("cding to %s\n", trunc_ary[1]);
	    chdir(trunc_ary[1]);
	  }
	}
	else{
	  int child = fork();
	  if (!child){
	    printf("the child here:%s\n", trunc_args);
	    trunc_ary = toAry(trunc_args);
	    execvp(trunc_ary[0], trunc_ary);
	    return(0);
	  }
	  while ((wpid = wait(&status)) > 0);
	}
      }
  }
  while ((wpid = wait(&status)) > 0);
  printf("done\n");
  return 0;
}

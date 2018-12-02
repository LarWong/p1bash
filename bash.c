1#include <stdlib.h>
#
include <stdio.h>
#include <string.h>
#include <unistd.h>
#include<sys/wait.h>
#include <limits.h>

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

int hasPipe(char**x){
  char ** r = x;
  for(int i = 0; r[i]; i++){
    if (!strcmp(r[i],"|")){
      return i;
    }
  }
  return 0;
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
  while (1){
    pid_t wpid= 0;
    int status = 0;
    char * str_args = calloc(sizeof(char), 9999);
    //char** strings = malloc(sizeof(char*) * 9999);
    //printf("%p\n",str_args);
    char cwd[PATH_MAX];
    getcwd(cwd,PATH_MAX);
    printf("%s$ ",cwd);
    fgets(str_args, 9999 + 1, stdin);
    //memcpy(strings, &argv[1], (argc-1) * sizeof(char *));
    //char * str_args = toString(strings);
    //printf("%s\n", str_args);
    str_args[strcspn(str_args, "\n")] = '\0';
    while(str_args){
      char * trunc_args = strsep(&str_args, ";");
      if (!isEmpty(trunc_args)){
	//printf("how doing this:%s\n",trunc_args);
	trunc_args = strip(trunc_args);
	char ** trunc_ary;
	// wiill make switch soon
	if (contains(trunc_args, "cd")){
	  //printf("the adult here:%s\n", trunc_args);
	  trunc_ary = toAry(trunc_args);
	  //printf("cd test result: %d\n", sizeary(trunc_ary));
	  if (strcmp(trunc_ary[0], "cd") == 0 && sizeary(trunc_ary) > 1){
	    //printf("running\n");
	    //printf("cding to %s\n", trunc_ary[1]);
	    chdir(trunc_ary[1]);
	  }
	}
	else{
	  trunc_ary = toAry(trunc_args);
	  int * pipe_des[2];
	  int pipeIndex = hasPipe(trunc_ary);
	  if (pipeIndex){
	    pipe(pipe_des);
	  }
	  int child = fork();
	  if (!child){
	    //printf("the child here:%s\n", trunc_args);
	    while (pipeIndex){
	      int old = dup(STDOUT_FILENO);
	      dup2(STDOUT_FILENO,pipe_des[1]);
	      execvp(trunc_ary[0], trunc_ary);
	      
	    }
	    execvp(trunc_ary[0], trunc_ary);
	    return(0);
	  }
	  while ((wpid = wait(&status)) > 0);
	}
	 
      }
    }
    while ((wpid = wait(&status)) > 0);
  }
  printf("done\n");
   return 0;
}

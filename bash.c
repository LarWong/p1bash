#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<fcntl.h>
#include<limits.h>
#include<string.h>
#include<sys/wait.h>
#include<errno.h>

static void sig(int signo){
    if (signo == SIGINT){
      printf("\nInterupt\n");
      exit(0);
    }
}

char ** parse_args(char *line){
  char ** arr = malloc(9000);
  for(int i = 0; arr[i] = strsep(&line," ");i++);
  return arr;
}

int main(){
  signal(SIGINT,sig);
  int status;
  char * input = malloc(9000);
  
  while(1){

    char cwd[PATH_MAX];
    getcwd(cwd,PATH_MAX);
    
    printf("%s$ ",cwd);
    scanf("%[^\n]%*c",input);
    char ** args = parse_args(input);

    if (!strcmp(args[0],"exit")){
      exit(0);
    }
    if (!strcmp(args[0],"cd")){
      if (args[2] == NULL){
	chdir(args[1]);
      }else{
	printf("cd: Too many args\n");
      }
    }
    
    
    int child = fork();
    if (child){
      int w = wait(&status);
    }else{
      if (execvp(args[0],args) == -1){
	printf("%s: %s\n",args[0],strerror(errno));
      }
      exit(0);
    }

  }


  return 0;
}

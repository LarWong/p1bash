#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include<fcntl.h>
#include<limits.h>
#include<string.h>

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

void pary(char ** strings){
  for (int x = 0; strings[x]; x++){
    printf("%s\n", strings[x]);
  }
}


int main(){
  signal(SIGINT,sig);
  char *input = malloc(9000);
  while(1){
    printf("\n->");
    scanf("%s",input);
    char ** args = parse_args(input);
    pary(args);
  }
  return 0;
}

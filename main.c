#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void pary(char ** strings){
  for (int x = 0; strings[x]; x++){
    printf("%s\n", strings[x]);
  }
}

string * toString(string ** args){
  char * ret_str = malloc(99999*sizeof(char));
  for (int x = 0; strings[x]; x++){
    strcat(ret_str, 
  }
}

int main(int argc, char * argv[]){
  char** strings = malloc(sizeof(char*) * 9999);
  memcpy(strings, &argv[1], (argc-1) * sizeof(char *));
  pary(strings);
  printf("done\n");
  return 0;
}


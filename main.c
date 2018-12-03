#include "shell.h"

int main(int argc, char * argv[]){
  signal(SIGINT,signal_handler);
  while (1){
    int wpid,status;
    char * str_args = calloc(sizeof(char), 9999);
    char cwd[PATH_MAX];
    getcwd(cwd,PATH_MAX);
    printf("%s$ ",cwd);
    fgets(str_args, 9999 + 1, stdin);
    str_args = remove_consec_ws(str_args);
    str_args[strcspn(str_args, "\n")] = '\0';
    while(str_args){
      char * trunc_args = strsep(&str_args, ";");
      if (!isEmpty(trunc_args)){
	trunc_args = strip(trunc_args);
      }
      char ** trunc_ary;
      trunc_ary = toAry(trunc_args);
      cmd_check(trunc_ary);
    }
    if (errno < 0)
      printf("ERROR: %s\n",strerror(errno));
    while ((wpid = wait(&status)) > 0);
  }
  return 0;
}

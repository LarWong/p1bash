#include <stdlib.h>
#include <stdio.h>
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

int help(char ** ary, char * hey){
  for (int i = 0; ary[i]; i++){
    if (strcmp(ary[i], hey) == 0){
      return 1;
    }
  }
  return 0;
}

int contains_ary(char ** ary, char ** hey){
  int state = 0;
  for (int i = 0; hey[i];i++){
    if (help(ary, hey[i])){
      return i;
    }
  }
  return -1;
}

int sizeary(char ** x){
  int i = 0;
  while (*(x++)){
    i++;
  }
  return i;
}

char *str_replace( char *s, const char *oldW, 
		   const char *newW) 
{ 
  char * result = malloc(sizeof(char) * 9999); 
  int i, cnt = 0; 
  int newWlen = strlen(newW); 
  int oldWlen = strlen(oldW); 
  
  // Counting the number of times old word 
  // occur in the string 
  for (i = 0; s[i] != '\0'; i++) 
    { 
      if (strstr(&s[i], oldW) == &s[i]) 
        { 
	  cnt++; 
  
	  // Jumping to index after the old word. 
	  i += oldWlen - 1; 
        } 
    } 
  
  // Making new string of enough length 
  result = (char *)malloc(i + cnt * (newWlen - oldWlen) + 1); 
  
  i = 0; 
  while (*s) 
    { 
      // compare the substring with the result 
      if (strstr(s, oldW) == s) 
        { 
	  strcpy(&result[i], newW); 
	  i += newWlen; 
	  s += oldWlen;
        } 
      else
	result[i++] = *s++; 
    } 
  
  result[i] = '\0'; 
  return result; 
} 

char * remove_consec_ws(char * x){
  char * new_str = malloc(sizeof(char) * 9999);
  strcpy(new_str, x);
  while(contains(new_str, "  ")){
    new_str = str_replace(new_str, "  ", " ");
  }
  return new_str;
}

char ** subarr(int start, int  division, char ** args){
  char ** items = args;
  char ** sub = malloc(sizeof(char)*9000);
  int x = 0;
  int i = 0;
  for(i = start; i < division; i++){
    sub[x] = items[i];
    x++;
  }
  sub[x] = NULL;
  return sub;
}


char *** sep_pipe_cmd(char ** items){
  char ** args = items;
  char *** groups = malloc(sizeof(char**)*10);
  int num_groups = 0;
  int sep_start = 0;
  int i = 0;
  while(*items != NULL){
    if(!strcmp(*items,"|")){
      groups[num_groups] = subarr(sep_start,i,args);
      sep_start = i + 1;
      num_groups++;
    }
    i++;
    items++;
  }

  groups[num_groups] = subarr(sep_start,sizeary(args),args);
  groups[num_groups+1] = NULL;

  return groups;

}

void    loop_pipe(char ***cmd)
{
  int   p[2];
  pid_t pid;
  int   fd_in = 0;

  while (*cmd != NULL)
    {
      pipe(p);
      int pid = fork();
      if (pid == 0)
        {
          dup2(fd_in, 0); //change the input according to the old one
          if (*(cmd + 1) != NULL)
            dup2(p[1], 1);
          close(p[0]);
          execvp((*cmd)[0], *cmd);
          exit(0);
        }
      else
        {
          wait(NULL);
          close(p[1]);
          fd_in = p[0]; //save the input for the next command
          cmd++;
        }
    }
}


void cmd_check(char ** args){
  char ** filters = malloc(sizeof(char*) * 999);
  //add more filters here
  filters[0] = "cd";
  filters[1] = "|";
  filters[2] = ">";
  filters[3] = ">>";
  filters[4] = "2>";
  filters[5] = "<";
  filters[6] = "<<";
  filters[7] = "2<";
  int state = contains_ary(args, filters);
  if (state > -1){
    //add more cases here
    if (state == 0 && sizeary(args) > 1){
      chdir(args[1]);
    }
    if (state == 1 && sizeary(args) > 2){
      char *** cmd = sep_pipe_cmd(args);
      loop_pipe(cmd);
    }
  } else{
    printf("hi");
    int child = fork();
    if (!child){
      execvp(args[0], args);
    }
  }
}

int main(int argc, char * argv[]){
  while (1){
    pid_t wpid = 0;
    int status = 0; 
    char * str_args = calloc(sizeof(char), 9999);
    char cwd[PATH_MAX];
    getcwd(cwd,PATH_MAX);
    printf("%s$ ",cwd);
    fgets(str_args, 9999 + 1, stdin);
    str_args = remove_consec_ws(str_args);
    str_args[strcspn(str_args, "\n")] = '\0';
    //printf("%s\n",str_args);
    while(str_args){
      char * trunc_args = strsep(&str_args, ";");
      if (!isEmpty(trunc_args)){
	trunc_args = strip(trunc_args);
      }
      char ** trunc_ary;	
      trunc_ary = toAry(trunc_args);
      cmd_check(trunc_ary);	
      while ((wpid = wait(&status)) > 0);
	
    }
  }
    //while ((wpid = wait(&status)) > 0);
    printf("done\n");
    return 0;
}

#include "shell.h"

void signal_handler(int sig){
  if(sig == SIGINT){
    printf("\nIT'S DEAD NOW!!!\n");
    exit(0);
  }
}

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

char * strip(char *s){
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
  for (i = 0; s[i] != '\0'; i++){
      if (strstr(&s[i], oldW) == &s[i]){
	  cnt++;
	  // Jumping to index after the old word.
	  i += oldWlen - 1;
        }
    }
  // Making new string of enough length
  result = (char *)malloc(i + cnt * (newWlen - oldWlen) + 1);
  i = 0;
  while (*s){
      // compare the substring with the result
      if (strstr(s, oldW) == s){
	  strcpy(&result[i], newW);
      	  i += newWlen;
	  s += oldWlen;
      }else{
	result[i++] = *s++;
      }
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


char *** sep_symbol_cmd(char ** items,char * symbol){
  char ** args = items;
  char *** groups = malloc(sizeof(char**)*10);
  int num_groups = 0;
  int sep_start = 0;
  int i = 0;
  while(*items != NULL){
    if(!strcmp(*items,symbol)){
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

void pipes(char ***args){
  int p[2];
  pid_t pid;
  int in = 0;
  int status;
  while (*args){
      pipe(p);
      pid = fork();
      if (!pid){
          dup2(in, 0);
          if (*(args + 1)) dup2(p[1], 1);
          close(p[0]);
          execvp((*args)[0], *args);
          exit(0);
      }else{
          wait(&status);
          close(p[1]);
          in = p[0];
          args++;
      }
    }
}

void execute_redirect(char ** cmd, char ** files,  char ** direction){
  int in, out, w, status;
  int pid = fork();
  if (pid == 0){
    for(int i = 0; direction[i];i++){
      if(!strcmp(direction[i],"<")){
	in = open(files[i],O_RDONLY);
	dup2(in,STDIN_FILENO);
	close(in);
      }else if (!strcmp(direction[i],">")){
	out = open(files[i],O_WRONLY | O_CREAT, 0666);
	dup2(out,STDOUT_FILENO);
	close(out);
      }
    }
    execvp(cmd[0],cmd);
    exit(0);
  }else{
    w = wait(&status);
  }
}

void redirect(char ** args){
  char ** cmd = malloc(sizeof(char*)*20);
  char ** files = malloc(sizeof(char*)*20);
  char ** direction = malloc(sizeof(char*)*20);
  int c = 0;
  int f = 0;
  int d = 0;

  while(*args){
    if(strcmp(*args,">") && strcmp(*args,"<")){
      cmd[c] = *args;
      c++;
    }else{
      break;
    }
    args++;
  }

  while(*args){
    if(strcmp(*args,">") && strcmp(*args,"<")){
      files[f] = *args;
      f++;
    }else{
      direction[d] = *args;
      d++;
    }
    args++;
  }

  cmd[c] = NULL;
  files[f] = NULL;
  direction[d] = NULL;

  execute_redirect(cmd,files,direction);
}



void cmd_check(char ** args){
  char ** filters = malloc(sizeof(char*) * 999);
  //add more filters here
  filters[0] = "cd";
  filters[1] = "|";
  filters[2] = ">";
  filters[3] = "<";
  filters[4] = "exit";
  int state = contains_ary(args, filters);
  if (state > -1){
    //add more cases here
    if (state == 0 && sizeary(args) > 1){
      if (sizeary(args) > 2){
	printf("cd: Too many arguments\n");
      }else if (chdir(args[1]) < 0){
	printf("cd :' %s' : No such directory or file\n",args[1]);
      }
    }else if (state == 4){
      printf("\nKILLING SHELL\n");
      exit(0);
    }else if (state == 1 && sizeary(args) > 2){
      char *** cmd = sep_symbol_cmd(args,"|");
      pipes(cmd);
    }else if ((state == 2 || state == 3)  && sizeary(args) > 2){
      redirect(args);
    }
  }else{
    int child = fork();
    if (!child){
      execvp(args[0], args);
      exit(0);
    }
  }
}

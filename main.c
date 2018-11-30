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
    state|=help(ary, hey[i]);
  }
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

int main(int argc, char * argv[]){
  //printf("hello\n");
  while (1){
    pid_t wpid= 0;
    int status = 0;
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
	char ** trunc_ary;
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
	
	trunc_ary = toAry(trunc_args);
	if (contains_ary(trunc_ary, filters)){
	  //add more cases here
	  if (strcmp(trunc_ary[0], "cd") == 0 && sizeary(trunc_ary) > 1){
	    chdir(trunc_ary[1]);
	  }
	  if (strcmp(trunc_ary[0], "|") == 0 && sizeary(trunc_ary) > 2){
	    
	  }
	  if (strcmp(trunc_ary[0], ">") == 0 && sizeary(trunc_ary) > 2){
	    
	  }
	  if (strcmp(trunc_ary[0], ">>") == 0 && sizeary(trunc_ary) > 2){
	    
	  }
	  if (strcmp(trunc_ary[0], "2>") == 0 && sizeary(trunc_ary) > 2){
	    
	  }
	  if (strcmp(trunc_ary[0], "<") == 0 && sizeary(trunc_ary) > 2){
	    
	  }
	  if (strcmp(trunc_ary[0], "<<") == 0 && sizeary(trunc_ary) > 2){
	    
	  }
	  if (strcmp(trunc_ary[0], "2<") == 0 && sizeary(trunc_ary) > 2){
	    
	  }
	}
	else{
	  int child = fork();
	  if (!child){
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

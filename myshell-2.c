#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define DELIMITERS " \t\n"
#define MAX_ARG_LEN 16
#define MAX_LINE_LEN 80

char *which(char *, char **);
int parse_stov(char *, char *, int *, char **);
void prompt(void);
void getcmd(char *);

int main(int argc, char *argv[])
{
  int run=1;
  int i;
  int ndirs;
  char *dirs[128];
  int status;
  char cline[MAX_LINE_LEN];
  char *exitcmd = "exit";
  int  largc;
  char *largv[128];
  char *path;

  parse_stov((char *) getenv("PATH"), ":", &ndirs, dirs);
  do {
    prompt();
    getcmd(cline);
    largc = 0;
    /* parse command line */
    parse_stov(cline, DELIMITERS, &largc, largv);
    if (strcmp(largv[0],exitcmd)) { // for some reason, strcmp chokes on this if we give it a literal.
      path = which(largv[0],dirs);
      if (path == NULL) {
        printf("%s not found in $PATH\n",largv[0]);
      } else {
        switch (fork()) {
          case -1:
            printf("fork() returned an error!\n");
          case 0: {
          /* I am the child process */
            execv(path,largv);
            exit(0);
          }
        }
        wait();
      }
    } else run = 0;
  /* continue execution of parent shell process */
  } while (run);
  /*cleanup and exit*/
  return 0;
}

int parse_stov(char *s, char *D, int *c, char **v) {
  char **cline;
  int argc = 0;

  cline = &s;
  v[argc] = (char *) malloc(MAX_ARG_LEN);
  while((v[argc] = strsep(cline, D)) != NULL) {
    v[++argc] = (char *) malloc(MAX_ARG_LEN);
  }
  *c = --argc;
  return 1;
}

void prompt(void) {
  char *prompt = "Simple Shell> ";
  printf("%s",prompt);
}

void getcmd(char *buff) {
  gets(buff);
}

char *which(char *v, char **d) {
  char *result = (char *) malloc(MAX_ARG_LEN);
  int i=0;
  int test=-1;
  if (strncmp(v,"/", 1)==0) { //absolute pathname
    strcpy(result,v);
  } else { 
    do {
      strcpy(result,d[i++]);
      strcat(result,"/");
      strcat(result,v);
      test = access(result, X_OK);
    } while ((test == -1)&&(d[i]!=NULL));
    if (d[i]==NULL) {
      result = NULL;
    }
  }
  return result;
}


/*#include <iostream> */
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* #include <wait.h> */
#include "minishell.h"

/* using namespace std; */

char *lookup_command(char *, char **);
int parse_command(char *, struct command_t *);
int parse_path(char **);
void execute_command(struct command_t *);
void print_prompt();
void read_command(char *);

int main()
{
    char **dirs;
    char *cmd_line;
    struct command_t cmd;
    int num_paths, rc, i = 0;
    pid_t pid;

    // ***************************************************
    // Memory Allocation
    // ***************************************************

    dirs = (char **) malloc(MAX_PATHS * sizeof(char *));
    for (i = 0; i < MAX_PATHS; i++)
    {
        dirs[i] = (char *) malloc(MAX_PATH_LEN + 1);
        dirs[i][0] = '\0';
    }

    cmd_line = (char *) malloc(BUFFER_LEN + 1);

    cmd.name = (char *) malloc(MAX_PATH_LEN + 1);
    cmd.path = (char *) malloc(MAX_PATH_LEN + 1);
    cmd.redirect_type = (char *) malloc(1 + 1);
    cmd.redirect = (char *) malloc(MAX_PATH_LEN + 1);
    cmd.argv = (char **) malloc(MAX_ARGS * sizeof(char *));
    for (i = 0; i < MAX_ARGS; i++)
    {
        cmd.argv[i] = (char *) malloc(MAX_ARG_LEN + 1);
    }

    // ****************************************************
    // Done Memory Allocation
    // ****************************************************

    num_paths = parse_path(dirs);

    while (1)
    {
        print_prompt();
        read_command(cmd_line);

        if (strcmp(cmd_line, BUFFER_EXIT) == 0)
        {
            break;
        }

        if (!parse_command(cmd_line, &cmd) ||
            !(cmd.path = lookup_command(cmd.name, dirs)))
        {
            continue;
        }

        pid = fork();

        if (pid == 0)
        {
            execute_command(&cmd);
            exit(0);
        }
        else
        {
	  /*
            waitpid(pid, &rc, 0);

            if (!WIFEXITED(rc))
            {
                cout << "Child process exited with "
                     << WEXITSTATUS(rc)
                     << endl;
            }
	  */
        }
    }
}

/**
 * Returns the full path to the command.
 */
char *lookup_command(char *cmd_name, char **dirs)
{
    char *path_name;
    int i, rc;

    path_name = (char *) malloc(MAX_PATH_LEN + 1);

    if (cmd_name[0] == '/')
    {
        return cmd_name;
    }

    for (i = 0; i < MAX_PATHS; i++)
    {
        if (dirs[i][0])
        {
            strcpy(path_name, dirs[i]);
            strcat(path_name, "/");
            strcat(path_name, cmd_name);

            if (access(path_name, X_OK) == 0)
            {
                return path_name;
            }
        }
    }

    path_name[0] = '\0';
    /*cerr << cmd_name << ": command not found" << endl; */
    return path_name;
}

/**
 * Parses the command line and sets the command type.
 */
int parse_command(char *line, struct command_t *cmd)
{
    char *item;
    char *cmd_line;
    int i;

    item = (char *) malloc(MAX_ARG_LEN + 1);
    cmd_line = (char *) malloc(strlen(line) + 1);
    strcpy(cmd_line, line);

    // Reset command struct.
    cmd->name[0] = '\0';
    cmd->argc = 0;
    cmd->path[0] = '\0';
    cmd->redirect_type[0] = '\0';
    cmd->redirect[0] = '\0';
    for (i = 0; i < MAX_ARGS; i++)
    {
        cmd->argv[i] = (char *) 0;
    }

    if (line[0] == '\0')
    {
        return 0;
    }

    // Populate the arguments array
    item = strtok(cmd_line, WHITESPACE);
    while (item != NULL)
    {
        if (strcmp(item, ">") == 0)
        {
            strcpy(cmd->redirect_type, REDIRECT_TYPE_WRITE);
        }
        else if (strcmp(item, ">>") == 0)
        {
            strcpy(cmd->redirect_type, REDIRECT_TYPE_APPEND);
        }
        else if (strlen(cmd->redirect_type))
        {
            strcpy(cmd->redirect, item);
        }
        else
        {
            cmd->argv[cmd->argc] = item;
            cmd->argc++;
        }

        item = strtok(NULL, WHITESPACE);
    }

    // Set the command
    cmd->name = cmd->argv[0];

    return cmd->argc;
}

/**
 * Reads the PATH environment variable, parses it, and populates dirs
 * argument with the paths.
 */
int parse_path(char **dirs)
{
    char *path_name;
    char *path_env_var;
    int i;

    path_name = (char *) malloc(MAX_PATH_LEN + 1);
    path_name = NULL;
    path_env_var = (char *) getenv("PATH");

    i = 0;
    path_name = strtok(path_env_var, PATH_DELIMITER);
    while(path_name != NULL)
    {
        dirs[i] = path_name;
        path_name = strtok(NULL, PATH_DELIMITER);
        i++;
    }

    return i;
}


/**
 * Displays the shell prompt.
 */
void print_prompt()
{
    printf("%s ", "ashell$");
}

/**
 * Reads a line from standard in.
 */
void read_command(char *buf)
{
    fgets(buf, BUFFER_LEN, stdin);
    buf[strlen(buf)-1] = '\0';
}

/**
 * Executes the command.
 */
void execute_command(struct command_t *cmd)
{
    FILE *fp;

    if (strlen(cmd->redirect))
    {
        fp = freopen(cmd->redirect, cmd->redirect_type, stdout);
    }

    execv(cmd->path, cmd->argv);
}

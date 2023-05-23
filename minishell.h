#define LINE_LEN 80
#define MAX_ARGS 64
#define MAX_ARG_LEN 16
#define MAX_FILE_LEN 128
#define MAX_PATHS 64
#define MAX_PATH_LEN 96
#define WHITESPACE " \t"
#define PATH_DELIMITER ":"
#define BUFFER_LEN 256
#define BUFFER_EXIT "exit"
#define REDIRECT_TYPE_WRITE "w"
#define REDIRECT_TYPE_APPEND "a"

struct command_t
{
    char *name;
    char *path;
    char *redirect;
    char *redirect_type;
    int argc;
    char **argv;
};

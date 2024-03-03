#include <errno.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/stat.h>


#define DOT_CHAR '.'
#define PATH_MAX_LEN 4096

#define PATH_BUFFER() ((char *) malloc(sizeof(char) * PATH_MAX_LEN))


char * curr_wd(char * rel_path, char * buffer);

bool is_special_entry_name(const char *);
bool is_hidden_file(const char *);
bool is_dir(const char *);

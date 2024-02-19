#include <errno.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


#define PATH_MAX_LEN 4096
#define PATH_BUFFER() ((char *) malloc(sizeof(char) * PATH_MAX_LEN))


char * curr_wd(char * rel_path, char * buffer);

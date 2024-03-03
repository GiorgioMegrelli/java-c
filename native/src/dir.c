#include "dir.h"

#include "utils.h"


char * curr_wd(char * rel_path, char * buffer) {
    if(buffer == NULL) {
        buffer = MALLOC(char, PATH_MAX_LEN);
    }
    if(rel_path == NULL) {
        getcwd(buffer, PATH_MAX_LEN);
    } else {
        if(realpath(rel_path, buffer) == NULL) {
            error(strerror(errno), errno);
        }
    }
    return buffer;
}

bool
is_special_entry_name(const char * f_name)
{
    int d_name_len = strlen(f_name);
    if(d_name_len == 1) {
        return f_name[0] == DOT_CHAR;
    } else if(d_name_len == 2) {
        return f_name[0] == DOT_CHAR
            && f_name[1] == DOT_CHAR;
    }
    return false;
}

bool
is_hidden_file(const char * f_name)
{
    return f_name[0] == DOT_CHAR;
}

bool
is_dir(const char * path)
{
    struct stat path_stat;
    return stat(path, &path_stat) == 0
        && S_ISDIR(path_stat.st_mode);
}

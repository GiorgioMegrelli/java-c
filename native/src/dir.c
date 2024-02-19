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

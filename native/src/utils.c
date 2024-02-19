#include "utils.h"

#include <stdio.h>


void error(const char * msg, int code) {
    printf("Error: %s\n", msg);
    exit(code);
}

#include <stdlib.h>

#define MALLOC(type, size) ((type *) malloc(sizeof(type) * size))

void error(const char * msg, int code);

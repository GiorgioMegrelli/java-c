#include <stdlib.h>

#define MALLOC(type, size) ((type *) malloc(sizeof(type) * size))
#define CALLOC(type, size) ((type *) calloc(size, sizeof(type)))

#define MAX(a, b) ((a > b)? (a): (b))

void error(const char * msg, int code);

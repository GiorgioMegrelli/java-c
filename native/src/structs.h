#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct {
    bool allow_hidden;
    char * root;
} obj_fields_t;

void init_obj_fields_t(obj_fields_t *, bool, const char *);
void destroy_obj_fields_t(obj_fields_t *);

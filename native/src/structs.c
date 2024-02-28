#include "structs.h"


void
init_obj_fields_t(obj_fields_t * obj_fields, bool b, const char * str_src)
{
    obj_fields->allow_hidden = b;
    obj_fields->root = (str_src == NULL)? NULL: strdup(str_src);
}

void
destroy_obj_fields_t(obj_fields_t * obj_fields)
{
    if(obj_fields->root != NULL) {
        free(obj_fields->root);
    }
}

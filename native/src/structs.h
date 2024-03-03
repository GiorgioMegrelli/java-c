#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "utils.h"


#define CHAR_BUFFER_INIT_CAP 8
#define CHAR_BUFFER_SCALE 2


typedef struct {
    bool allow_hidden;
    char * root;
} obj_fields_t;

void init_obj_fields_t(obj_fields_t *, bool, const char *);
void destroy_obj_fields_t(obj_fields_t *);


typedef struct {
    char * data;
    int size;
    int capacity;
} CharBuffer_t;

void CharBuffer_init(CharBuffer_t *);
CharBuffer_t CharBuffer_create();
void CharBuffer_append(CharBuffer_t *, char);
void CharBuffer_append_str(CharBuffer_t *, char *);
char * CharBuffer_value_alloc(CharBuffer_t *);
int CharBuffer_size(CharBuffer_t *);
void CharBuffer_destroy(CharBuffer_t *);

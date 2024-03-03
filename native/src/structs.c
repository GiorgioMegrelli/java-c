#include "structs.h"


/**
* obj_fields_t
*/

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


/**
* CharBuffer_t
*/

static void
CharBuffer_check_capacity(CharBuffer_t * ch_buf)
{
    if(ch_buf->data == NULL) {
        ch_buf->capacity = CHAR_BUFFER_INIT_CAP;
        ch_buf->data = CALLOC(char, CHAR_BUFFER_INIT_CAP);
    } else if(ch_buf->size == ch_buf->capacity) {
        ch_buf->capacity *= CHAR_BUFFER_SCALE;
        ch_buf->data = (char *) realloc(ch_buf->data, ch_buf->capacity * sizeof(char));
    }
}

void
CharBuffer_init(CharBuffer_t * ch_buf)
{
    ch_buf->data = NULL;
    ch_buf->size = 0;
    ch_buf->capacity = 0;
}

CharBuffer_t
CharBuffer_create()
{
    CharBuffer_t ch_buf;
    CharBuffer_init(&ch_buf);
    return ch_buf;
}

void
CharBuffer_append(CharBuffer_t * ch_buf, char c)
{
    CharBuffer_check_capacity(ch_buf);
    ch_buf->data[ch_buf->size] = c;
    ch_buf->size++;
}

void
CharBuffer_append_str(CharBuffer_t * ch_buf, char * s)
{
    for(size_t i = 0; i < strlen(s); i++) {
        CharBuffer_append(ch_buf, s[i]);
    }
}

char *
CharBuffer_value_alloc(CharBuffer_t * ch_buf)
{
    int size = ch_buf->size;
    char * content = MALLOC(char, size + 1);
    strncpy(content, ch_buf->data, size);
    content[size] = '\0';
    return content;
}

int
CharBuffer_size(CharBuffer_t * ch_buf)
{
    return ch_buf->size;
}

void
CharBuffer_destroy(CharBuffer_t * ch_buf)
{
    if(ch_buf->data != NULL) {
        free(ch_buf->data);
        CharBuffer_init(ch_buf);
    }
}

#include "include/FileSys.h"

#include "src/utils.h"
#include "src/dir.h"
#include "src/structs.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>


#define CURR_DIR "."
#define UNIX_PATH_SEP "/"


static void store_in_obj_fields(obj_fields_t *, JNIEnv *, jobject);

static void iter_dir(const char *, CharBuffer_t *, const obj_fields_t *, int depth);


JNIEXPORT jstring
JNICALL Java_FileSys_printFiles(JNIEnv * env, jobject jobj, jboolean jb_recursive)
{
    obj_fields_t obj_fields;
    store_in_obj_fields(&obj_fields, env, jobj);
    char * curr_path = curr_wd(obj_fields.root, NULL);

    CharBuffer_t ch_buf = CharBuffer_create();
    iter_dir(curr_path, &ch_buf, &obj_fields, (jb_recursive)? INT_MAX: 1);
    char * content = CharBuffer_value_alloc(&ch_buf);
    jstring result = (*env)->NewStringUTF(env, content);
    free(content);
    CharBuffer_destroy(&ch_buf);

    free(curr_path);
    destroy_obj_fields_t(&obj_fields);
    return result;
}


static void
store_in_obj_fields(obj_fields_t * obj_fields_ptr, JNIEnv * env, jobject jobj)
{
    jclass cls = (*env)->GetObjectClass(env, jobj);

    jfieldID root_fid = (*env)->GetFieldID(env, cls, "root", "Ljava/lang/String;");
    if(root_fid == NULL) {
        error("Unable to get field ID for 'root'", EXIT_FAILURE);
    }

    jfieldID allow_hidden_fid = (*env)->GetFieldID(env, cls, "allowHidden", "Z");
    if(allow_hidden_fid == NULL) {
        error("Unable to get field ID for 'allowHidden'", EXIT_FAILURE);
    }

    jstring root_ptr = (*env)->GetObjectField(env, jobj, root_fid);
    jboolean allow_hidden_jb = (*env)->GetBooleanField(env, jobj, allow_hidden_fid);
    bool allow_hidden = (allow_hidden_jb)? true: false;

    if(root_ptr == NULL) {
        init_obj_fields_t(obj_fields_ptr, allow_hidden, NULL);
    } else {
        const char * root_val = (*env)->GetStringUTFChars(env, root_ptr, NULL);
        if(root_val == NULL) {
            init_obj_fields_t(obj_fields_ptr, allow_hidden, NULL);
        } else {
            init_obj_fields_t(
                obj_fields_ptr,
                allow_hidden,
                (strlen(root_val) == 0)? CURR_DIR: root_val
            );
            (*env)->ReleaseStringUTFChars(env, root_ptr, root_val);
        }
    }
}

static void iter_dir(
    const char * curr_path, CharBuffer_t * ch_buf, const obj_fields_t * obj_fields_ptr, int depth
) {
    if(depth <= 0) return;

    DIR *dir;
    if((dir = opendir(curr_path)) != NULL) {
        struct dirent *ent;

        char * buffer = PATH_BUFFER();
        while((ent = readdir(dir)) != NULL) {
            if(is_special_entry_name(ent->d_name)) continue;
            if(!obj_fields_ptr->allow_hidden && is_hidden_file(ent->d_name)) continue;

            snprintf(buffer, PATH_MAX_LEN, "%s%s%s", curr_path, UNIX_PATH_SEP, ent->d_name);
            if(is_dir(buffer)) {
                iter_dir(buffer, ch_buf, obj_fields_ptr, depth - 1);
            } else {
                CharBuffer_append_str(ch_buf, buffer);
                CharBuffer_append(ch_buf, '\n');
            }
        }
        free(buffer);

        closedir(dir);
    }
}

#include "include/FileSys.h"

#include "src/utils.h"
#include "src/dir.h"
#include "src/structs.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>


#define DOT_CHAR '.'
#define CURR_DIR "."
#define UNIX_PATH_SEP "/"


static void store_in_obj_fields(obj_fields_t *, JNIEnv *, jobject);

static void iter_dir(const char *, const obj_fields_t *, int depth);
static inline bool is_special_entry_name(const char *);
static inline bool is_hidden_file(const char *);
static inline bool is_dir(const char *);


JNIEXPORT void
JNICALL Java_FileSys_printFiles(JNIEnv * env, jobject jobj, jboolean jb_recursive)
{
    obj_fields_t obj_fields;
    store_in_obj_fields(&obj_fields, env, jobj);
    char * curr_path = curr_wd(obj_fields.root, NULL);

    iter_dir(curr_path, &obj_fields, (jb_recursive)? INT_MAX: 1);

    free(curr_path);
    destroy_obj_fields_t(&obj_fields);
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

static void
iter_dir(const char * curr_path, const obj_fields_t * obj_fields_ptr, int depth)
{
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
                iter_dir(buffer, obj_fields_ptr, depth - 1);
            } else {
                printf("%s\n", buffer);
            }
        }
        free(buffer);

        closedir(dir);
    }
}

static inline bool
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

static inline bool
is_hidden_file(const char * f_name)
{
    return f_name[0] == DOT_CHAR;
}

static inline bool
is_dir(const char * path)
{
    struct stat path_stat;
    return stat(path, &path_stat) == 0
        && S_ISDIR(path_stat.st_mode);
}

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


#define DOT_CHAR '.'
#define CURR_DIR "."


static void store_in_obj_fields(obj_fields_t *, JNIEnv *, jobject);

static void print_dir(const char *);
static void iter_dir(const char *, obj_fields_t *);
static inline bool is_special_entry_name(const char *);
static inline bool is_hidden_file(const char *);


JNIEXPORT void
JNICALL Java_FileSys_printFiles(JNIEnv * env, jobject jobj, jboolean jb_recursive)
{
    obj_fields_t obj_fields;
    store_in_obj_fields(&obj_fields, env, jobj);
    char * curr_path = curr_wd(obj_fields.root, NULL);

    if(jb_recursive) {
        iter_dir(curr_path, &obj_fields);
    } else {
        print_dir(curr_path);
    }

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
print_dir(const char * curr_path)
{
    DIR *dir;
    if((dir = opendir(curr_path)) != NULL) {
        struct dirent *ent;
        struct stat st;

        char * buffer = PATH_BUFFER();

        while((ent = readdir(dir)) != NULL) {
            if(stat(ent->d_name, &st) == 0 && S_ISREG(st.st_mode)) {
                realpath(ent->d_name, buffer);
                printf("%s\n", buffer);
            }
        }

        free(buffer);
        closedir(dir);
    }
}

static void
iter_dir(const char * curr_path, obj_fields_t * obj_fields_ptr)
{}

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

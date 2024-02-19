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


void store_in_obj_fields(obj_fields_t *, JNIEnv *, jobject);


JNIEXPORT void
JNICALL Java_FileSys_printFiles(JNIEnv * env, jobject jobj, jboolean jbool)
{
    obj_fields_t obj_fields;
    store_in_obj_fields(&obj_fields, env, jobj);
    char * curr_path = curr_wd(obj_fields.root, NULL);

    DIR *dir;
    struct dirent *ent;
    struct stat st;

    if((dir = opendir(curr_path)) != NULL) {
        while((ent = readdir(dir)) != NULL) {
            if(stat(ent->d_name, &st) == 0 && S_ISREG(st.st_mode)) {
                char * buffer = PATH_BUFFER();
                realpath(ent->d_name, buffer);
                printf("%s\n", buffer);
                free(buffer);
            }
        }
        closedir(dir);
    }

    free(curr_path);
    destroy_obj_fields_t(&obj_fields);
}


void
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
        init_obj_fields_t(obj_fields_ptr, allow_hidden, root_val);
        (*env)->ReleaseStringUTFChars(env, root_ptr, root_val);
    }
}

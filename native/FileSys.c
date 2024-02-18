#include "include/FileSys.h"
#include <stdio.h>


JNIEXPORT void JNICALL Java_FileSys_printFiles(JNIEnv * env, jobject jobj, jboolean jbool) {
    printf("Invoked: Java_FileSys_printFiles\n");
}

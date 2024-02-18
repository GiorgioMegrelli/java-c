#!/bin/bash

source globals.sh
source utils.sh
source clean.sh


echo_bold "Generating header (.h) files in '$INCLUDE_DIR'"

mkdir -p $INCLUDE_DIR
mkdir -p $TARGET_DIR

for java_file in $(find $SOURCE_DIR -name '*.java'); do
    f_name=$(basename "$java_file")
    cls_name="${f_name/.java/}"
    cls_header="$INCLUDE_DIR/$cls_name.h"

    echo "> $java_file"
    javac "$java_file" -d $TARGET_DIR
    javah -jni -o $cls_header -classpath $TARGET_DIR $cls_name
done


echo_bold "Generating shared library"

mkdir -p $LIBS_DIR

gcc $NATIVE_DIR/*.c             \
    -shared                     \
    -o "$LIBS_DIR/$LIB_NAME.so" \
    -I $JNI_H_DIRNAME           \
    -I $JNI_MD_H_DIRNAME

echo "Generated: '$LIBS_DIR/$LIB_NAME.so'"

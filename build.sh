#!/bin/bash

set -e

source globals.sh
source utils.sh
source clean.sh


TMP_DIR="$JAVA_DIR/tmp"


echo_bold "Generating header (.h) files in '$INCLUDE_DIR'"

mkdir -p $INCLUDE_DIR
mkdir -p $TMP_DIR

for java_file in $(find $SOURCE_DIR -name '*.java'); do
    f_name=$(basename "$java_file")
    cls_name="${f_name/.java/}"
    cls_header="$INCLUDE_DIR/$cls_name.h"

    echo "> $java_file"
    javac "$java_file" -d $TMP_DIR
    javah -jni -o $cls_header -classpath $TMP_DIR $cls_name
done

rm -rdf $TMP_DIR

echo


echo_bold "Generating shared library"

mkdir -p $LIBS_DIR

gcc $NATIVE_DIR/*.c         \
    $NATIVE_DIR/src/*.c     \
    -shared                 \
    -o $LIB_SO_OBJECT       \
    -I $JNI_H_DIRNAME       \
    -I $JNI_MD_H_DIRNAME

echo "Generated: '$LIB_SO_OBJECT'"
echo

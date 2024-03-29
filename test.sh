#!/bin/bash

set -e

source globals.sh
source utils.sh


echo_bold "Preparing test environment"

mkdir -p $TEST_ENV_DIR
cp "$TEST_DIR/Main.java" "$TEST_ENV_DIR/Main.java"

for java_file in $(find $TEST_DIR -maxdepth 1 -type f -name '*.java'); do
    f_name=$(basename $java_file)
    cp $java_file "$TEST_ENV_DIR/$f_name"
done

for cls_file in $(find $SOURCE_DIR -type f); do
    f_name=$(basename $cls_file)
    cp $cls_file "$TEST_ENV_DIR/$f_name"
done

echo


echo_bold "Building and running java classes with shared library"

javac $TEST_ENV_DIR/*.java
java -cp $TEST_ENV_DIR -Djava.library.path="$LIBS_DIR" Main

echo

#!/bin/bash

NATIVE_DIR="$(pwd)/native"
INCLUDE_DIR="$NATIVE_DIR/include"

JAVA_DIR="$(pwd)/java"
SOURCE_DIR="$JAVA_DIR/source"

JNI_H_DIRNAME=$(dirname $(find / -name 'jni.h'))
JNI_MD_H_DIRNAME=$(dirname $(find / -name 'jni_md.h'))

TEST_DIR="$(pwd)/test"
TEST_ENV_DIR="$TEST_DIR/env"

LIBS_DIR="$NATIVE_DIR/libs"

LIB_SO_OBJECT="$LIBS_DIR/libFileSys.so"

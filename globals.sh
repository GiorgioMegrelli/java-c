#!/bin/bash

NATIVE_DIR="$(pwd)/native"
INCLUDE_DIR="$NATIVE_DIR/include"

JAVA_DIR="$(pwd)/java"
SOURCE_DIR="$JAVA_DIR/source"
TARGET_DIR="$JAVA_DIR/target"

LIBS_DIR="$(pwd)/libs"

JNI_H_DIRNAME=$(dirname $(find / -name 'jni.h'))
JNI_MD_H_DIRNAME=$(dirname $(find / -name 'jni_md.h'))

TEST_DIR="test"

LIB_NAME="libFileSys"

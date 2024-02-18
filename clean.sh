#!/bin/bash

source globals.sh
source utils.sh

echo_bold "Cleaning output directories"
rm -rdf $INCLUDE_DIR
rm -rdf $TARGET_DIR
rm -rdf $LIBS_DIR

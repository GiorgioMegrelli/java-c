#!/bin/bash

set -e

source globals.sh
source utils.sh

echo_bold "Cleaning output directories"
rm -rdf $INCLUDE_DIR
rm -rdf $LIBS_DIR
rm -rdf $TEST_ENV_DIR
echo

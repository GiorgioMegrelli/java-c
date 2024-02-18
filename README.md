# java-c

## Description

C implementation of java methods

## Usage

**Build required shared library with command:**
```shell
./build.sh
```

The command steps:
- Reads java files in `java/source` and compiles them to class file.
- Converts classes to header files and copies them into `native/include`
- Generates shared library in `native/libs` directory

**Test library after building with command:**
```shell
./test.sh
```

The command steps:
- Copies required files from `java/source` into `test/env`
- Compiles copied files (with `Main.java`)
- Runs compiled files with shared library

## Setup Docker

### Windows

**Powershell:**

Build docker image:
```shell
docker build -t java-development .
```

Run container in interactive mode:
```shell
docker run -it --rm -v ${PWD}:/usr/src/app java-development
```

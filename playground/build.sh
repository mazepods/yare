#!/bin/bash

set echo on
mkdir -p ../bin

cFilenames=$(find . -type f -name "*.c")
assembly="playground"
compilerFlags="-g -fdeclspec -fPIC"
includeFlags="-Isrc -I../engine/src/"
linkerFlags="-L../bin/ -lengine -Wl,-rpath,."
defines="-D_DEBUG -DYIMPORT"

echo "Building $assembly..."
clang $cFilenames $compilerFlags -o ../bin/$assembly $defines $includeFlags $linkerFlags
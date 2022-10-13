#!/bin/bash
mkdir "build"
# shellcheck disable=SC2164
cd build
qmake -project ../src/
echo 'greaterThan(QT_MAJOR_VERSION, 4): QT += widgets' >> build.pro
qmake
make
./build
# Projet-Recherche-Documentaire

mkdir build

cd build

qmake -project ../src/

Ajouter la ligne suivante au fichier build.pro:   
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

qmake

make

./build

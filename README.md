# Projet-Recherche-Documentaire

## Par script

Le script project.sh permet de directement compiler et executer le programme.

> sh ./project.sh

## Par commandes

Dans le cas où le script ne fonctionnerait pas, voici les commandes à exécuter :

> mkdir build

> cd build

> qmake -project ../src/

Ajouter la ligne suivante au fichier build.pro :   
> greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

> qmake

> make

> ./build

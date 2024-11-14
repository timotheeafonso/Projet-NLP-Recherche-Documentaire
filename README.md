# Projet de recherche documentaire

Ce projet est un projet de recherche documentaire et de traitement du langage naturel implémenté en C++. Il implique la création d'un système de recherche capable de récupérer des informations pertinentes à partir de questions spécifiques, basé sur un ensemble de documents donné. Les fonctionnalités principales incluent la mise en œuvre de la racinisation pour réduire les mots à leur forme racine et l'utilisation d'une liste de mots vides pour filtrer les mots courants ayant une faible valeur informative. Le système prend en charge des requêtes de complexité variable, allant des unions ou conjonctions de termes de base aux requêtes avancées où les termes doivent apparaître de manière consécutive, en passant par des expressions logiques complexes, l'utilisation de jokers et la tolérance aux fautes d'orthographe. Une interface permet aux utilisateurs de visualiser les résultats, avec les termes de la requête mis en évidence directement dans les documents.

Trois types de requêtes sont possibles :
- REQUÊTE PAR DISJONCTION (TF-IDF)
- REQUÊTE PAR PRÉFIXE
- RECHERCHE EXACTE

Pour plus d'informations, voir le document "rapport.pdf".

# Lancement du projet
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

cmake_minimum_required(VERSION 3.22)
project(Projet_Recherche_Documentaire)

set(CMAKE_CXX_STANDARD 20)

add_executable(Projet_Recherche_Documentaire src/main.cpp src/Document.cc src/Document.hh src/Documents.cc src/Documents.hh src/BTree.cc src/BTree.hh src/BTreeNode.cc src/BTreeNode.hh src/Word.cc src/Word.hh src/Forest.cc src/Forest.hh src/Documents.hh src/SpellingCorrector.cc src/SpellingCorrector.hh src/NLP.cc src/NLP.hh)

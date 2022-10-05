cmake_minimum_required(VERSION 3.22)
project(Projet_Recherche_Documentaire)

set(CMAKE_CXX_STANDARD 20)

add_executable(Projet_Recherche_Documentaire  src/Document.cc src/Document.hh src/Documents.cc src/Documents.hh src/SpellingCorrector.cc src/SpellingCorrector.hh src/Query.cc src/Query.hh src/NLP.cc src/NLP.hh)

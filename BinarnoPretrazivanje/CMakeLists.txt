cmake_minimum_required(VERSION 3.8)
project(BinarnoPretrazivanje)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Lista.h NizLista.h BinarnoPretrazi.h NizListaImplementacija.h BinarnoPretraziImplementacija.h)
add_executable(BinarnoPretrazivanje ${SOURCE_FILES})
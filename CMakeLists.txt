cmake_minimum_required(VERSION 3.15)
project(TP-POO2024)

set(CMAKE_CXX_STANDARD 17) # Ou a versão que preferires

# Adiciona os ficheiros fonte
add_executable(TP-POO2024 main.cpp Buffer/Buffer.cpp Buffer/Cursor.cpp
        Caravanas/Caravana.cpp
       )

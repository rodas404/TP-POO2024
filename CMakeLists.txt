cmake_minimum_required(VERSION 3.30)
project(projeto)

set(CMAKE_CXX_STANDARD 20)

add_executable(projeto main.cpp
        Buffer/Buffer.cpp
        Buffer/Buffer.h
        Buffer/Cursor.cpp
        Buffer/Cursor.h
        Mapa/Mapa.cpp
        Mapa/Mapa.h
        Mapa/Celula.cpp
        Mapa/Celula.h
        Localizações/Cidade.cpp
        Localizações/Cidade.h
        Localizações/Item.cpp
        Localizações/Item.h
        Localizações/Caravana.cpp
        Localizações/Caravana.h
        Caravanas/CaravanaComercio.cpp
        Caravanas/CaravanaComercio.h
        Caravanas/CaravanaMilitar.cpp
        Caravanas/CaravanaMilitar.h
)

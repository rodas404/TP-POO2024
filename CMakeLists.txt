cmake_minimum_required(VERSION 3.28.1)
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
        Localizacoes/Cidade.cpp
        Localizacoes/Cidade.h
        Localizacoes/Item.cpp
        Localizacoes/Item.h
        Localizacoes/Caravana.cpp
        Localizacoes/Caravana.h
        Caravanas/CaravanaComercio.cpp
        Caravanas/CaravanaComercio.h
        Caravanas/CaravanaMilitar.cpp
        Caravanas/CaravanaMilitar.h
        Itens/CaixaPandora.cpp
        Itens/CaixaPandora.h
        Itens/ArcaTesouro.cpp
        Itens/ArcaTesouro.h
        Itens/Jaula.cpp
        Itens/Jaula.h
        Itens/Mina.cpp
        Itens/Mina.h
        Itens/PacoteSuspenso.cpp
        Itens/PacoteSuspenso.h
        Caravanas/CaravanaBarbara.cpp
        Caravanas/CaravanaBarbara.h
        Simulador/Simulador.cpp
        Simulador/Simulador.h
        Caravanas/CaravanaSecreta.cpp
        Caravanas/CaravanaSecreta.h
)

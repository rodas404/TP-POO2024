#include "Caravana.h"

// Define e gere os ids das caravanas
int Caravana::next_id = 0;




void Caravana::setId(int novo_id) {
	this->id = novo_id;
}
Caravana::Caravana()
: id(next_id++), quantAtualTripulantes(0), quantMaxTripulantes(0),
pesoMaxMercadoria(0), pesoAtualMercadoria(0), quantMaxAgua(0),
quantAtualAgua(0), isInCity(false) {}


// Define as propriedades das caravanas derivadas
CaravanaComercio::CaravanaComercio() : Caravana() {
	quantAtualTripulantes = 20;
	quantMaxTripulantes = 20;
	pesoMaxMercadoria = 40;
	quantMaxAgua = 200;
	quantAtualAgua = quantMaxAgua;
}

CaravanaMilitar::CaravanaMilitar() : Caravana() {
	quantAtualTripulantes = 40;
	quantMaxTripulantes = 40;
	pesoMaxMercadoria = 5;
	quantMaxAgua = 400;
	quantAtualAgua = quantMaxAgua;
}

// Funções das caravanas
int Caravana::getId() const {
	return id;
}

void Caravana::addTripulantes(int quantidade) {
	if (quantAtualTripulantes < quantMaxTripulantes && (quantAtualTripulantes + quantidade) <= quantMaxTripulantes) {
		this->quantAtualTripulantes = quantAtualTripulantes + quantidade;
	}
}

void Caravana::removeTripulantes(int quantidade) {
	if (quantAtualTripulantes > 0 && (quantAtualTripulantes - quantidade) >= 0) {
		this->quantAtualTripulantes = quantAtualTripulantes - quantidade;
	}
}

void Caravana::addMercadoria(int toneladas) {
	if (pesoAtualMercadoria < pesoMaxMercadoria && (pesoAtualMercadoria + toneladas) <= pesoMaxMercadoria) {
		this->pesoAtualMercadoria = pesoAtualMercadoria + toneladas;
	}
}

void Caravana::removeMercadoria(int toneladas) {
	if (pesoAtualMercadoria > 0 && (pesoAtualMercadoria - toneladas) >= 0) {
		this->pesoAtualMercadoria = pesoAtualMercadoria - toneladas;
	}
}
void CaravanaMilitar::consumeAgua() {
	if (quantAtualTripulantes > quantMaxTripulantes / 2) {
		quantAtualAgua -= 3;
	} else {
		quantAtualAgua -= 1;
	}
	if (quantAtualAgua < 0) quantAtualAgua = 0;
}

void CaravanaComercio::consumeAgua() {
	if (quantAtualTripulantes > 0) {
		if (quantAtualTripulantes > quantMaxTripulantes / 2) {
			quantAtualAgua -= 2;
		} else {
			quantAtualAgua -= 1;
		}
	}
	if (quantAtualAgua < 0) quantAtualAgua = 0;
}

void Caravana::addAgua() {
	quantAtualAgua = quantMaxAgua;
}

int Caravana::getTripulantes() const {
	return quantAtualTripulantes;
}

int Caravana::getAgua() const {
	return quantAtualAgua;
}

int Caravana::getMercadoria() const {
	return pesoAtualMercadoria;
}


void Caravana::consumeAgua() {
	// Implementação padrão vazia
}

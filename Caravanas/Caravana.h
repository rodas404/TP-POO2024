#ifndef CARAVANA_H
#define CARAVANA_H

class Caravana {
public:
	Caravana();
	virtual ~Caravana() = default;

	// Obter info das caravanas
	int getId() const;
	int getTripulantes() const; // Corrigido: adicionado parênteses
	int getAgua() const; // Renomeado para seguir convenção
	int getMercadoria() const; // Renomeado para seguir convenção
	int getPosX() const; // Renomeado para seguir convenção
	int getPosY() const; // Renomeado para seguir convenção


	void setId(int novo_id); // Renomeado para seguir convenção
	void addTripulantes(int quantidade);
	void removeTripulantes(int quantidade);
	void addMercadoria(int toneladas);
	void removeMercadoria(int toneladas); // Corrigido: removido 's' extra
	void addAgua();
	virtual void consumeAgua() =0; // Tornado virtual para permitir override

protected:
	static int next_id;
	int id; // Renomeado para minúscula
	int quantAtualTripulantes;
	int quantMaxTripulantes;
	double pesoMaxMercadoria;
	double pesoAtualMercadoria;
	double quantMaxAgua;
	double quantAtualAgua;
	int posX;
	int posY;
	bool isInCity;
	// Cidade* cidadeAtual; // Comentado como no original
};

class CaravanaComercio : public Caravana {
public:
	CaravanaComercio(); // Corrigido: primeira letra maiúscula
	~CaravanaComercio() override = default;
	void consumeAgua() override;

};

class CaravanaMilitar : public Caravana {
public:
	CaravanaMilitar();
	~CaravanaMilitar() override = default;
	void consumeAgua() override;
};

#endif // CARAVANA_H

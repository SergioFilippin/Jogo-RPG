//INTEGRANTES SERGIO LUIS FILIPPIN 2259500
//              IGOR LUIS DIAS 2199713
//              VINICIUS BRANQUINHO 2187258
#ifndef ITEM_H
#define ITEM_H

#include <string>

class Item {
private:
    std::string nome;
    int peso;

public:
    Item(const char* nomeInicial, int peso);

    const std::string& getNome() const;
    int getPeso() const;
    virtual void mostrarDetalhes() const;
    virtual ~Item() {}
};

class Arma : public Item {
private:
    int capacidadeDeAtaque;

public:
    Arma(const char* nomeInicial, int peso, int capacidadeDeAtaque);

    int getCapacidadeDeAtaque() const;
    void mostrarDetalhes() const override;
};

class Pocao : public Item {
private:
    int capacidadeDeCura;

public:
    Pocao(const char* nomeInicial, int peso, int capacidadeDeCura);

    int getCapacidadeDeCura() const;
    void mostrarDetalhes() const override;
};

#endif

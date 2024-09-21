// Item.h
#ifndef ITEM_H
#define ITEM_H

class Item {
private:
    static const int TAMANHO_MAX_NOME = 50;       // Tamanho máximo para o nome do item
    char nome[TAMANHO_MAX_NOME];                 // Nome do item
    int peso;                                    // Peso do item

public:
    // Construtor
    Item(const char* nomeInicial, int peso);

    // Métodos de status
    const char* getNome() const;                 // Retorna o nome do item
    int getPeso() const;                         // Retorna o peso do item
    virtual void mostrarDetalhes() const;        // Mostra os detalhes do item (sobrescrito em subclasses)

    // Destrutor virtual para garantir destruição adequada de subclasses
    virtual ~Item() {}
};

class Arma : public Item {
private:
    int capacidadeDeAtaque;                      // Capacidade de ataque da arma

public:
    // Construtor
    Arma(const char* nomeInicial, int peso, int capacidadeDeAtaque);

    // Métodos específicos para Arma
    int getCapacidadeDeAtaque() const;           // Retorna a capacidade de ataque
    void mostrarDetalhes() const override;       // Exibe os detalhes da arma
};

class Pocao : public Item {
private:
    int capacidadeDeCura;                        // Quantidade de pontos de vida que a poção cura

public:
    // Construtor
    Pocao(const char* nomeInicial, int peso, int capacidadeDeCura);

    // Métodos específicos para Poção
    int getCapacidadeDeCura() const;             // Retorna a quantidade de cura
    void mostrarDetalhes() const override;       // Exibe os detalhes da poção
};

#endif // ITEM_H

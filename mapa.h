#ifndef MAPA_H
#define MAPA_H

#include "inimigo.h"
#include "item.h"

// Definição da classe Sqm, que representa cada espaço no mapa
class Sqm {
private:
    Inimigo* inimigo;   // Ponteiro para um inimigo (pode ser nullptr)
    Item* item; // Ponteiro para um item (pode ser nullptr)
    bool vazio;         // Se está vazio

public:
    Sqm(); // Construtor padrão
    void gerarInimigo(Inimigo* novoInimigo);
    void gerarItem(Item* novoElemento);
    bool estaVazio() const;
    bool temInimigo() const;
    bool temItem() const;
    Inimigo* getInimigo() const;
    Item* getItem() const;
};

class Mapa {
private:
    Sqm* caminho;
    int tamanho;

public:
    Mapa(int tamanho); // Construtor que define o tamanho do mapa
    ~Mapa();           // Destrutor para liberar memória
    void gerarInimigos();  // Popula o mapa com inimigos aleatórios
    void gerarItem(); // Popula o mapa com itens (armas ou poções) aleatórios
    Sqm& getSqm(int posicao); // Feito para o heroi acessar e verificar se tem inimigo ou item
    int getTamanho() const;   // Retorna o tamanho do mapa
};

#endif
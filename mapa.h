#ifndef MAPA_H
#define MAPA_H

#include "inimigo.h"
#include "item.h"

// Definição da classe Sqm, que representa cada espaço no mapa
class Sqm {
private:
    Inimigo* inimigo;   // Ponteiro para um inimigo (pode ser nullptr)
    Item* item;         // Ponteiro para um item (pode ser nullptr)
    bool vazio;         // Indica se o sqm está vazio

public:
    Sqm();  // Construtor padrão

    // Métodos de manipulação
    void setInimigo(Inimigo* novoInimigo);  // Define o inimigo no sqm ; passado para esse script por Branquinho
    void setItem(Item* novoElemento);       // Define o item no sqm ; passado para esse script por Branquinho

    bool estaVazio() const;                 // Verifica se o sqm está vazio
    bool temInimigo() const;                // Verifica se há um inimigo
    bool temItem() const;                   // Verifica se há um item

    Inimigo* getInimigo() const;            // Retorna o inimigo no sqm
    Item* getItem() const;                  // Retorna o item no sqm
};

class Mapa {
private:
    Sqm* caminho;      // Array de sqms que representam o mapa
    int tamanho;       // Tamanho total do caminho

public:
    Mapa(int tamanho);  // Construtor que define o tamanho do mapa
    ~Mapa();            // Destrutor para liberar memória

    // Popula o mapa com inimigos e itens aleatórios
    void gerarInimigos();  
    void gerarItem();      

    Sqm& getSqm(int posicao);  // Retorna a referência de um sqm
    int getTamanho() const;    // Retorna o tamanho do mapa
};

#endif

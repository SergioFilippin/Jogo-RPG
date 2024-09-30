//INTEGRANTES SERGIO LUIS FILIPPIN 2259500
//              IGOR LUIS DIAS 2199713
//              VINICIUS BRANQUINHO 2187258

#ifndef HEROI_H
#define HEROI_H

#include "Item.h"

class Heroi {
private:
    std::string nome;
    int vida;
    int forca;
    Item* cinto[5]; // 5 slots no cinto
    Item** mochila; // Mochila será um array dinâmico de ponteiros para Item
    int capacidadeMochila; // Capacidade atual da mochila (tamanho do array)
    int topoMochila; // Índice do último item na mochila (-1 significa vazio)

public:
    Heroi(std::string nome, int vida, int forca);
    ~Heroi();

    // Funções para manipulação dos itens no cinto
    Item* remover_item_cinto(int slot); // Retorna o item removido
    bool adicionar_item_cinto(Item* item, int slot);
    Item* verItemCinto(int slot) const;
    bool temItemNoCinto(int slot) const;

    // Funções para manipulação dos itens na mochila
    bool adicionar_item_mochila(Item* item); // Adiciona um item no topo da mochila
    Item* usar_item_mochila(); // Retira o item no topo da mochila
    Item* verItemTopoMochila() const;
    Item* verItemSubTopoMochila() const;

    // Funções de batalha e atributos
    void ataque();
    void receberdano(int dano);
    int getVida() const;
    int getForca() const;
    void usarpocao(Item* pocao);
};

#endif

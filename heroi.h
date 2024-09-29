#ifndef HEROI_H
#define HEROI_H

#include <string>
#include "Item.h" // Certifique-se de incluir o header de Item

class Heroi {
public:
    // Construtor
    Heroi(const std::string& nome, int vida, int forca);

    // Gerenciamento de Item
    bool adicionar_item_mochila(Item* item);   // Adiciona item à mochila
    bool adicionar_item_cinto(Item* item);     // Adiciona item ao cinto
    Item* remover_item_cinto(int indice);      // Remove item do cinto por índice
    Item* usar_item_mochila();                 // Usa o item no topo da mochila

    // Métodos de combate
    void ataque();                             // Herói ataca
    void receberdano(int dano);                // Herói recebe dano
    void usarpocao(Item* pocao);               // Herói usa uma poção

    // Métodos de acesso (getters)
    int getVida() const;                       // Retorna a vida atual do herói
    int getForca() const;                      // Retorna a força do herói

private:
    std::string nome;                          // Nome do herói
    int vida;                                  // Pontos de vida do herói
    int forca;                                 // Força do herói

    // Definição das constantes de capacidade
    static const int VIDA_MAXIMA = 200;             // Vida máxima do herói
    static const int CAPACIDADE_MAX_CINTO = 5;      // Capacidade máxima do cinto
    static const int CAPACIDADE_MAX_MOCHILA = 10;   // Capacidade máxima da mochila
    static const int CAPACIDADE_MAX_PESO_MOCHILA = 100; // Peso máximo que a mochila pode carregar

    // Cinto e Mochila
    Item* cinto[CAPACIDADE_MAX_CINTO];        // Array de ponteiros para itens no cinto
    Item* mochila[CAPACIDADE_MAX_MOCHILA];    // Array de ponteiros para itens na mochila
    int topoMochila;                          // Controle do topo da mochila (usado como uma pilha)
    int pesoAtualMochila;                     // Peso atual da mochila
};

#endif // HEROI_H

// Mapa.h
#ifndef MAPA_H
#define MAPA_H

#include "Inimigo.h"
#include "Item.h"

class Mapa {
private:
    static const int MAX_TAMANHO_MAPA = 20;       // Tamanho máximo do mapa (número de sqms)
    struct Sqm {                                  // Estrutura para cada posição do mapa
        bool vazio;                               // Indica se o sqm está vazio
        Inimigo* inimigo;                         // Ponteiro para o inimigo (se houver)
        Item* item;                               // Ponteiro para o item (se houver)
    };

    Sqm caminho[MAX_TAMANHO_MAPA];                // Array de sqms que formam o caminho do mapa
    int tamanhoCaminho;                           // Tamanho do caminho atual
    int posicaoAtual;                             // Posição atual do jogador no caminho

public:
    // Construtor
    Mapa(int tamanhoCaminho);

    // Métodos de manipulação do mapa
    void adicionarInimigo(int posicao, Inimigo* inimigo);  // Adiciona um inimigo no sqm especificado
    void adicionarItem(int posicao, Item* item);           // Adiciona um item no sqm especificado
    bool moverParaProximaPosicao();                        // Move o jogador para o próximo sqm
    Sqm getPosicaoAtual() const;                           // Retorna a posição atual do jogador no mapa
    bool fimDoMapa() const;                                // Verifica se o jogador chegou ao fim do mapa

    // Destrutor
    ~Mapa();
};

#endif // MAPA_H

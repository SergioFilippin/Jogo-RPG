// Jogo.h
#ifndef JOGO_H
#define JOGO_H

#include "Heroi.h"
#include "Inimigo.h"
#include "Item.h"

class Jogo {
private:
    Heroi* heroi;                                 // O herói controlado pelo jogador
    static const int MAX_INIMIGOS = 10;           // Número máximo de inimigos em um nível
    static const int MAX_ITENS = 10;              // Número máximo de itens em um nível
    static const int MAX_NIVEIS = 5;              // Número máximo de níveis no jogo

    Inimigo* inimigos[MAX_INIMIGOS];              // Array de ponteiros para inimigos em cada nível
    Item* itens[MAX_ITENS];                       // Array de ponteiros para itens em cada nível
    int numInimigos;                              // Número de inimigos no nível atual
    int numItens;                                 // Número de itens no nível atual
    int nivelAtual;                               // Índice do nível atual (começa no 0)

    void gerarInimigos();                         // Gera os inimigos do nível
    void gerarItens();                            // Gera os itens do nível
    void batalha(Inimigo* inimigo);               // Método para executar batalhas
    void interagirComItem(Item* item);            // Método para interagir com itens

public:
    // Construtor
    Jogo(Heroi* heroi);

    // Método para iniciar o jogo
    void iniciar();

    // Métodos de controle de níveis
    void avancarNivel();                          // Avança para o próximo nível
    bool nivelCompleto() const;                   // Verifica se o nível atual foi completado

    // Destrutor
    ~Jogo();
};

#endif // JOGO_H

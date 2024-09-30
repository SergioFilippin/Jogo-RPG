//INTEGRANTES SERGIO LUIS FILIPPIN 2259500
//              IGOR LUIS DIAS 2199713
//              VINICIUS BRANQUINHO 2187258
#ifndef JOGO_H
#define JOGO_H

#include "Heroi.h"
#include "Inimigo.h"
#include "Item.h"
#include "Mapa.h"

class Jogo {
private:
    Heroi* heroi;
    static const int MAX_INIMIGOS = 10;
    static const int MAX_ITENS = 10;
    static const int MAX_NIVEIS = 5;

    Inimigo* inimigos[MAX_INIMIGOS];
    Item* itens[MAX_ITENS];
    int numInimigos;
    int numItens;
    int nivelAtual;

    void gerarInimigos();
    void gerarItens();
    void batalha(Inimigo* inimigo);
    void interagirComItem(Item* item);
    void organizarItens();  // Declaração de organizarItens()
    void usarPocao();       // Declaração de usarPocao()

public:
    Jogo(Heroi* heroi);
    void iniciar();
    void avancarNivel();
    ~Jogo();
};

#endif

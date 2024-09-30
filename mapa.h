//INTEGRANTES SERGIO LUIS FILIPPIN 2259500
//              IGOR LUIS DIAS 2199713
//              VINICIUS BRANQUINHO 2187258
#ifndef MAPA_H
#define MAPA_H

#include "Inimigo.h"
#include "Item.h"

class Mapa {
public:
    struct Sqm {
        bool vazio;
        Inimigo* inimigo;
        Item* item;
    };

    Mapa(bool aleatorio = true, int tamanhoFixo = 20);
    void adicionarInimigo(int posicao, Inimigo* inimigo);
    void adicionarItem(int posicao, Item* item);
    bool moverParaProximaPosicao();
    Sqm getPosicaoAtual() const;
    bool fimDoMapa() const;
    ~Mapa();

private:
    static const int MAX_TAMANHO_MAPA = 20;
    static const int MIN_TAMANHO_MAPA = 5;
    Sqm* caminho;
    int tamanhoCaminho;
    int posicaoAtual;
};

#endif

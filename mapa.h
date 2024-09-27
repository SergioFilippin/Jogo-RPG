// Mapa.cpp
#include "Mapa.h"
#include <iostream>

// Construtor
Mapa::Mapa(int tamanhoCaminho) : tamanhoCaminho(tamanhoCaminho), posicaoAtual(0) {
    if (tamanhoCaminho > MAX_TAMANHO_MAPA) {
        this->tamanhoCaminho = MAX_TAMANHO_MAPA;
    }
    for (int i = 0; i < this->tamanhoCaminho; ++i) {
        caminho[i] = Sqm();
    }
}

// Adiciona um inimigo no sqm especificado
void Mapa::adicionarInimigo(int posicao, Inimigo* inimigo) {
    if (posicao >= 0 && posicao < tamanhoCaminho) {
        caminho[posicao].inimigo = inimigo;
        caminho[posicao].vazio = false;
    }
}

// Adiciona um item no sqm especificado
void Mapa::adicionarItem(int posicao, Item* item) {
    if (posicao >= 0 && posicao < tamanhoCaminho) {
        caminho[posicao].item = item;
        caminho[posicao].vazio = false;
    }
}

// Move o jogador para o próximo sqm
bool Mapa::moverParaProximaPosicao() {
    if (posicaoAtual < tamanhoCaminho - 1) {
        ++posicaoAtual;
        return true;
    }
    return false;
}

// Retorna a posição atual do jogador no mapa
Mapa::Sqm Mapa::getPosicaoAtual() const {
    return caminho[posicaoAtual];
}

// Verifica se o jogador chegou ao fim do mapa
bool Mapa::fimDoMapa() const {
    return posicaoAtual == tamanhoCaminho - 1;
}

// Destrutor
Mapa::~Mapa() {
    for (int i = 0; i < tamanhoCaminho; ++i) {
        delete caminho[i].inimigo;
        delete caminho[i].item;
    }
}

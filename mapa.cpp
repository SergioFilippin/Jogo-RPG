#include "mapa.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

// Implementação da classe Sqm

Sqm::Sqm() : inimigo(nullptr), item(nullptr), vazio(true) {}

void Sqm::gerarInimigo(Inimigo* novoInimigo) {
    inimigo = novoInimigo;
    vazio = false;
}

void Sqm::gerarItem(Item* novoElemento) {
    item = novoElemento;
    vazio = false;
}

bool Sqm::estaVazio() const {
    return vazio;
}

bool Sqm::temInimigo() const {
    return inimigo != nullptr;
}

bool Sqm::temItem() const {
    return item != nullptr;
}

Inimigo* Sqm::getInimigo() const {
    return inimigo;
}

Item* Sqm::getItem() const {
    return item;
}

Mapa::Mapa(int tamanho) : tamanho(tamanho) {
    caminho = new Sqm[tamanho]; // Aloca o array de sqms
    srand(time(0)); // Inicializa o gerador de números aleatórios
}

Mapa::~Mapa() {
    delete[] caminho; // Libera a memória do array de sqms
}

void Mapa::gerarInimigos() {
    // Gera inimigos aleatórios no mapa
    for (int i = 0; i < tamanho; i++) {
        if (rand() % 2 == 0) { // 50% de chance de ter um inimigo
            char nome[] = "Inimigo";
            int vida = 50 + (rand() % 50); // Vida entre 50 e 100
            int ataque = 10 + (rand() % 10); // Ataque entre 10 e 20
            caminho[i].setInimigo(new Inimigo(nome, vida, ataque));
        }
    }
}

void Mapa::gerarItem() {
    // Gera itens aleatórios no mapa (armas e poções)
    for (int i = 0; i < tamanho; i++) {
        if (rand() % 2 == 0) { // 50% de chance de ter um item
            if (rand() % 2 == 0) { // 50% de chance de ser uma arma
                char nome[] = "Espada";
                int peso = 5;
                int ataque = 20;
                caminho[i].setElemento(new Arma(nome, peso, ataque));
            } else { // 50% de chance de ser uma poção
                char nome[] = "Poção de Vida";
                int peso = 2;
                int cura = 30;
                caminho[i].setElemento(new Pocao(nome, peso, cura));
            }
        }
    }
}

Sqm& Mapa::getSqm(int posicao) {
    return caminho[posicao];
}

int Mapa::getTamanho() const {
    return tamanho;
}
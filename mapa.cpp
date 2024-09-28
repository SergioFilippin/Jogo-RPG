// Mapa.cpp
#include "mapa.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

// Construtor padrão ; passado para esse script por Branquinho
Sqm::Sqm() : inimigo(nullptr), item(nullptr), vazio(true) {}

// Define o inimigo no sqm ; passado para esse script por Branquinho
void Sqm::setInimigo(Inimigo* novoInimigo) {
    inimigo = novoInimigo;
    vazio = false;  // O sqm não está mais vazio
}

// Define o item no sqm ; passado para esse script por Branquinho
void Sqm::setItem(Item* novoElemento) {
    item = novoElemento;
    vazio = false;  // O sqm não está mais vazio
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

// Construtor da classe Mapa ; passado para esse script por Branquinho
Mapa::Mapa(int tamanho) : tamanho(tamanho) {
    caminho = new Sqm[tamanho]; // Aloca o array de sqms
    srand(time(0)); // Inicializa o gerador de números aleatórios
}

// Destrutor da classe Mapa ; passado para esse script por Branquinho
Mapa::~Mapa() {
    delete[] caminho; // Libera a memória do array de sqms
}

// Gera inimigos aleatórios no mapa ; já implementado por Branquinho
void Mapa::gerarInimigos() {
    for (int i = 0; i < tamanho; i++) {
        if (rand() % 2 == 0) {  // 50% de chance de ter um inimigo
            char nome[] = "Inimigo";
            int vida = 50 + (rand() % 50);  // Vida entre 50 e 100
            int ataque = 10 + (rand() % 10);  // Ataque entre 10 e 20
            caminho[i].setInimigo(new Inimigo(nome, vida, ataque));  // Adiciona o inimigo ao sqm
        }
    }
}

// Gera itens aleatórios no mapa (armas e poções) ; já implementado por Branquinho
void Mapa::gerarItem() {
    for (int i = 0; i < tamanho; i++) {
        if (rand() % 2 == 0) {  // 50% de chance de ter um item
            if (rand() % 2 == 0) {  // 50% de chance de ser uma arma
                char nome[] = "Espada";
                int peso = 5;
                int ataque = 20;
                caminho[i].setItem(new Arma(nome, peso, ataque));  // Adiciona a arma ao sqm
            } else {  // 50% de chance de ser uma poção
                char nome[] = "Poção de Vida";
                int peso = 2;
                int cura = 30;
                caminho[i].setItem(new Pocao(nome, peso, cura));  // Adiciona a poção ao sqm
            }
        }
    }
}

// Retorna a referência de um sqm no mapa ; já implementado por Branquinho
Sqm& Mapa::getSqm(int posicao) {
    return caminho[posicao];
}

int Mapa::getTamanho() const {
    return tamanho;
}

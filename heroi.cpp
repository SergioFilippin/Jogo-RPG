// INTEGRANTES SERGIO LUIS FILIPPIN 2259500
//              IGOR LUIS DIAS 2199713
//              VINICIUS BRANQUINHO 2187258

#include "heroi.h"
#include <iostream>
#include <string>

#ifndef HEROI_H
#define HEROI_H

using namespace std;

// Construtor classe herói ; Sergio
Heroi::Heroi(const string& nome, int vida, int forca)
    : nome(nome), vida(vida), pesomochila(0), capacidademochila(100), topomochila(0) {
    // Inicializar cinto e mochila com ponteiros nulos ; Sergio
    for (int i = 0; i < CAPACIDADE_MAX_CINTO; i++) {
        cinto[i] = nullptr;
    }

    // Inicializar a mochila com tamanho inicial grande ; Igor
    mochila = new Item*[capacidademochila];
    for (int i = 0; i < capacidademochila; i++) {
        mochila[i] = nullptr;
    }
}

// Destrutor para liberar a memória alocada dinamicamente ; Vinicius
Heroi::~Heroi() {
    delete[] mochila;  // Libera a memória alocada dinamicamente para a mochila
}

// Adicionar item à mochila ; Sergio
bool Heroi::adicionar_item_mochila(Item* item) {
    if (topomochila < capacidademochila) {
        mochila[topomochila++] = item;
        return true;
    }
    return false; // Retorna false quando mochila cheia (não deve acontecer com expansão infinita) ; Igor
}

// Adicionar item ao cinto ; Sergio
bool Heroi::adicionar_item_cinto(Item* item) {
    for (int i = 0; i < CAPACIDADE_MAX_CINTO; i++) {
        if (cinto[i] == nullptr) {
            cinto[i] = item;
            return true;
        }
    }
    return false; // Retorna false quando o cinto está cheio ; Sergio
}

// Remover item do cinto ; Sergio
Item* Heroi::remover_item_cinto(int indice) {
    if (indice >= 0 && indice < CAPACIDADE_MAX_CINTO && cinto[indice] != nullptr) {
        Item* retirado = cinto[indice];
        cinto[indice] = nullptr;
        return retirado;
    }
    return nullptr; // Posição vazia ou índice inválido do cinto ; Sergio
}

// Usar item da mochila ; Sergio
Item* Heroi::usar_item_mochila() {
    if (topomochila > 0) {
        return mochila[--topomochila]; // Remove o item do topo da mochila ; Sergio
    }
    return nullptr; // Mochila vazia ; Sergio
}

// Getter para pontos de vida do herói ; passado para esse script por Branquinho
int Heroi::getVida() const {
    return vida;
}

// Exibir o status atual do herói ; passado para esse script por Branquinho
void Heroi::displayStatus() const {
    cout << "===== Status do Herói =====" << endl;
    cout << "Nome: " << nome << ", Vida: " << vida << "/" << VIDA_MAXIMA << endl;
    cout << "Itens no cinto: ";
    
    // Exibir os itens no cinto
    for (int i = 0; i < CAPACIDADE_MAX_CINTO; ++i) {
        if (cinto[i] != nullptr) {
            cout << cinto[i]->getNome() << " ";
        } else {
            cout << "[Vazio] ";
        }
    }
    cout << endl;

    // Mostrar o item no topo da mochila
    if (topomochila > 0) {
        cout << "Item no topo da mochila: " << mochila[topomochila - 1]->getNome() << endl;
    } else {
        cout << "Mochila está vazia." << endl;
    }
    cout << "============================" << endl;
}

// Ataque do herói ; Sergio
void Heroi::ataque() {
    cout << nome << " está atacando!" << endl;
}

// Receber dano ; Sergio
void Heroi::receberdano(int dano) {
    vida -= dano;
    if (vida < 0) vida = 0;
    cout << nome << " recebeu " << dano << " de dano. Pontos de vida atual: " << vida << endl;
}

// Usar poção ; Sergio
void Heroi::usarpocao(Item* pocao) {
    vida += 30;  // Cura 30 pontos de vida ; Sergio
    if (vida > VIDA_MAXIMA) {
        vida = VIDA_MAXIMA;  // Limita a vida ao valor máximo ; Sergio
    }
    cout << nome << " usou uma poção! Pontos de vida restaurados para: " << vida << endl;
}

#endif

#include "Heroi.h"
#include <iostream>

// Construtor para inicializar o herói com nome, vida e força
Heroi::Heroi(const std::string& nome, int vida, int forca)
    : nome(nome), vida(vida), forca(forca), topoMochila(0), pesoAtualMochila(0) {
    // Inicializar o cinto e a mochila como vazios
    for (int i = 0; i < CAPACIDADE_MAX_CINTO; ++i) {
        cinto[i] = nullptr;
    }
    for (int i = 0; i < CAPACIDADE_MAX_MOCHILA; ++i) {
        mochila[i] = nullptr;
    }
}

// Método para adicionar um item na mochila
bool Heroi::adicionar_item_mochila(Item* item) {
    if (pesoAtualMochila + item->getPeso() <= CAPACIDADE_MAX_PESO_MOCHILA) {
        if (topoMochila < CAPACIDADE_MAX_MOCHILA) {
            mochila[topoMochila++] = item;
            pesoAtualMochila += item->getPeso(); // Atualiza o peso da mochila
            return true;
        }
    }
    return false; // Mochila cheia ou peso excedido
}

// Método para adicionar um item ao cinto
bool Heroi::adicionar_item_cinto(Item* item) {
    for (int i = 0; i < CAPACIDADE_MAX_CINTO; ++i) {
        if (cinto[i] == nullptr) {
            cinto[i] = item;
            return true;
        }
    }
    return false; // Cinto cheio
}

// Método para remover um item do cinto
Item* Heroi::remover_item_cinto(int indice) {
    if (indice >= 0 && indice < CAPACIDADE_MAX_CINTO && cinto[indice] != nullptr) {
        Item* item = cinto[indice];
        cinto[indice] = nullptr;
        return item;
    }
    return nullptr; // Nenhum item na posição especificada
}

// Método para usar um item da mochila (remover do topo)
Item* Heroi::usar_item_mochila() {
    if (topoMochila > 0) {
        Item* item = mochila[--topoMochila];
        pesoAtualMochila -= item->getPeso(); // Atualiza o peso da mochila
        return item;
    }
    return nullptr; // Mochila vazia
}

// Método para o herói atacar
void Heroi::ataque() {
    std::cout << nome << " está atacando!" << std::endl;
}

// Método para o herói receber dano
void Heroi::receberdano(int dano) {
    vida -= dano;
    if (vida < 0) vida = 0;
    std::cout << nome << " recebeu " << dano << " de dano. Pontos de vida restantes: " << vida << std::endl;
}

// Método para o herói usar uma poção e recuperar vida
void Heroi::usarpocao(Item* pocao) {
    vida += 30; // Exemplo de quanto a vida aumenta ao usar uma poção
    if (vida > VIDA_MAXIMA) {
        vida = VIDA_MAXIMA;
    }
    std::cout << nome << " usou uma poção! Vida restaurada para: " << vida << std::endl;
}

// Método para obter a vida do herói
int Heroi::getVida() const {
    return vida;
}

// Método para obter a força do herói
int Heroi::getForca() const {
    return forca;
}

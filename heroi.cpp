//INTEGRANTES SERGIO LUIS FILIPPIN 2259500
//              IGOR LUIS DIAS 2199713
//              VINICIUS BRANQUINHO 2187258

#include "Heroi.h"
#include <iostream>
using namespace std;

Heroi::Heroi(string nome, int vida, int forca) : nome(nome), vida(vida), forca(forca), capacidadeMochila(10), topoMochila(-1) {
    // Inicializar o cinto com NULL (vazio)
    for (int i = 0; i < 5; ++i) {
        cinto[i] = NULL;
    }

   
    mochila = new Item*[capacidadeMochila];
    for (int i = 0; i < capacidadeMochila; ++i) {
        mochila[i] = NULL;
    }
}

// Destrutor para limpar a memória
Heroi::~Heroi() {
    for (int i = 0; i < 5; ++i) {
        if (cinto[i] != NULL) {
            delete cinto[i];
        }
    }

    for (int i = 0; i <= topoMochila; ++i) {
        if (mochila[i] != NULL) {
            delete mochila[i];
        }
    }
    delete[] mochila;
}

// Adicionar item no cinto em um slot específico
bool Heroi::adicionar_item_cinto(Item* item, int slot) {
    if (slot >= 0 && slot < 5 && cinto[slot] == NULL) {
        cinto[slot] = item;
        return true;
    }
    return false;
}

// Remover item do cinto e retornar o item
Item* Heroi::remover_item_cinto(int slot) {
    if (slot >= 0 && slot < 5 && cinto[slot] != NULL) {
        Item* itemRemovido = cinto[slot];
        cinto[slot] = NULL;
        return itemRemovido; // Retorna o item removido
    }
    return NULL;
}

// Verificar o item em um slot específico do cinto
Item* Heroi::verItemCinto(int slot) const {
    if (slot >= 0 && slot < 5) {
        return cinto[slot];  // Apenas retornando o item, sem removê-lo
    }
    return NULL;
}

// Verificar se há um item em um slot específico do cinto
bool Heroi::temItemNoCinto(int slot) const {
    return slot >= 0 && slot < 5 && cinto[slot] != NULL;
}

// Adicionar um item ao topo da mochila
bool Heroi::adicionar_item_mochila(Item* item) {
    // Verificar se a mochila está cheia
    if (topoMochila >= capacidadeMochila - 1) {
        // Expandir a mochila se necessário
        capacidadeMochila *= 2;
        Item** novaMochila = new Item*[capacidadeMochila];
        for (int i = 0; i <= topoMochila; ++i) {
            novaMochila[i] = mochila[i];
        }
        delete[] mochila;
        mochila = novaMochila;
    }

    // Adicionar o item ao topo da mochila
    topoMochila++;
    mochila[topoMochila] = item;
    return true;
}

// Usar o item no topo da mochila (remover do topo)
Item* Heroi::usar_item_mochila() {
    if (topoMochila >= 0) {
        Item* item = mochila[topoMochila];
        mochila[topoMochila] = NULL;
        topoMochila--;
        return item;
    }
    return NULL;
}

// Verificar o item no topo da mochila (não remove)
Item* Heroi::verItemTopoMochila() const {
    if (topoMochila >= 0) {
        return mochila[topoMochila];  // Apenas retornando o item no topo, sem removê-lo
    }
    return NULL;
}

// Verificar o item logo abaixo do topo da mochila (não remove)
Item* Heroi::verItemSubTopoMochila() const {
    if (topoMochila > 0) {
        return mochila[topoMochila - 1];
    }
    return NULL;
}

// Funções de batalha
void Heroi::ataque() {
    cout << nome << " esta atacando!" << endl;
}

void Heroi::receberdano(int dano) {
    vida -= dano;
    cout << nome << " recebeu " << dano << " de dano. Pontos de vida restantes: " << vida << endl;
}

int Heroi::getVida() const {
    return vida;
}

int Heroi::getForca() const {
    return forca;
}

// Usar poção para recuperar vida
void Heroi::usarpocao(Item* item) {
    Pocao* pocao = dynamic_cast<Pocao*>(item);  // Verifica se o item é uma poção
    if (pocao != NULL) {
        int cura = pocao->getCapacidadeDeCura();
        vida += cura;  // Aplica a cura à vida do herói
        cout << "Voce usou uma pocao. Vida restaurada em " << cura << " pontos. Vida atual: " << vida << endl;
    } else {
        cout << "Este item nao e uma pocao." << endl;
    }
}

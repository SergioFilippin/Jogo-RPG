//INTEGRANTES SERGIO LUIS FILIPPIN 2259500
//              IGOR LUIS DIAS 2199713
//              VINICIUS BRANQUINHO 2187258
#include "Mapa.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;

Mapa::Mapa(bool aleatorio, int tamanhoFixo) : posicaoAtual(0), caminho(NULL) {
    srand(static_cast<unsigned int>(time(nullptr)));  // Semente para a geração aleatória
    

    if (aleatorio) {
        tamanhoCaminho = MIN_TAMANHO_MAPA + rand() % (MAX_TAMANHO_MAPA - MIN_TAMANHO_MAPA + 1);
        cout << "Tamanho do mapa gerado aleatoriamente: " << tamanhoCaminho << endl;
    } else {
        tamanhoCaminho = tamanhoFixo;
        cout << "Tamanho do mapa definido: " << tamanhoCaminho << endl;
    }

    caminho = new Sqm[tamanhoCaminho];
    for (int i = 0; i < tamanhoCaminho; ++i) {
        caminho[i].vazio = true;
        caminho[i].inimigo = NULL;
        caminho[i].item = NULL;
    }
    cout << "Mapa inicializado com sucesso. Tamanho do caminho: " << tamanhoCaminho << endl;
}

void Mapa::adicionarInimigo(int posicao, Inimigo* inimigo) {
    if (posicao >= 0 && posicao < tamanhoCaminho) {
        caminho[posicao].vazio = false;
        caminho[posicao].inimigo = inimigo;
        cout << "Inimigo adicionado no sqm " << posicao << endl;
    } else {
        cout << "Erro: posicao invalida para adicionar inimigo!" << endl;
    }
}

void Mapa::adicionarItem(int posicao, Item* item) {
    if (posicao >= 0 && posicao < tamanhoCaminho) {
        caminho[posicao].vazio = false;
        caminho[posicao].item = item;
        cout << "Item adicionado no sqm " << posicao << endl;
    } else {
        cout << "Erro: posicao invalida para adicionar item!" << endl;
    }
}

bool Mapa::moverParaProximaPosicao() {
    if (posicaoAtual < tamanhoCaminho - 1) {
        ++posicaoAtual;
        cout << "Movendo para a posicao " << posicaoAtual << endl;

        int eventoAleatorio = rand() % 4;
        cout << "Gerando evento para o sqm " << posicaoAtual << endl;

        if (eventoAleatorio == 0) 
        {
        int chanceInimigo = rand() % 100;

        if (chanceInimigo < 30) {
        adicionarInimigo(posicaoAtual, new Inimigo("Zumbi", 30, 5));  // 30% chance
        } else if (chanceInimigo < 60) {
        adicionarInimigo(posicaoAtual, new Inimigo("Morcego Mutante", 20, 10));  // 30% chance
        } else if (chanceInimigo < 70) {
        adicionarInimigo(posicaoAtual, new Inimigo("Bruxa", 30, 13));  // 10% chance
        } else if (chanceInimigo < 80) {
        adicionarInimigo(posicaoAtual, new Inimigo("Golem", 50, 8));  // 10% chance
        } else if (chanceInimigo < 90) {
        adicionarInimigo(posicaoAtual, new Inimigo("Mutante", 40, 12));  // 10% chance
        } else if (chanceInimigo < 95) {
        adicionarInimigo(posicaoAtual, new Inimigo("Dragao de Fogo", 70, 15));  // 5% chance
        } else {
        adicionarInimigo(posicaoAtual, new Inimigo("Gaz'Haragoth, OMG TIBIA REFFERENCE?!", 70, 15));  // 5% chance
        }
        } 
    else if (eventoAleatorio == 1) {
        int tipoArma = rand() % 3;
        if (tipoArma == 0) {
        adicionarItem(posicaoAtual, new Arma("Machado", 5, 15));
        } else if (tipoArma == 1) {
        adicionarItem(posicaoAtual, new Arma("Espada", 3, 10));
        } else {
        adicionarItem(posicaoAtual, new Arma("Arco", 7, 20));
    }
} else if (eventoAleatorio == 2) {
    int tipoPocao = rand() % 2;
    if (tipoPocao == 0) {
        adicionarItem(posicaoAtual, new Pocao("Pocao Pequena", 1, 10));
    } else {
        adicionarItem(posicaoAtual, new Pocao("Pocao Grande", 3, 30));
    }
} else {
    caminho[posicaoAtual].vazio = true;
    cout << "Voce encontrou um nivel vazio." << endl;
}

return true;
    }

    cout << "Fim do mapa atingido." << endl;
    return false;
}

Mapa::Sqm Mapa::getPosicaoAtual() const {
    return caminho[posicaoAtual];
}

bool Mapa::fimDoMapa() const {
    return posicaoAtual == tamanhoCaminho - 1;
}

Mapa::~Mapa() {
    if (caminho) {
        for (int i = 0; i < tamanhoCaminho; ++i) {
            delete caminho[i].inimigo;
            delete caminho[i].item;
        }
        delete[] caminho;
        cout << "Mapa destruido com sucesso." << endl;
    }
}
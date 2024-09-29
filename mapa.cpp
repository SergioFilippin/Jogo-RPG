#include "Mapa.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

Mapa::Mapa(bool aleatorio, int tamanhoFixo) : posicaoAtual(0), caminho(nullptr) {
    srand(static_cast<unsigned int>(time(nullptr))); // Semente para a geração aleatória

    if (aleatorio) {
        // Gera tamanho aleatório do caminho
        tamanhoCaminho = MIN_TAMANHO_MAPA + rand() % (MAX_TAMANHO_MAPA - MIN_TAMANHO_MAPA + 1);
        cout << "Tamanho do mapa gerado aleatoriamente: " << tamanhoCaminho << endl;
    } else {
        // Define o tamanho fixo
        tamanhoCaminho = tamanhoFixo;
        cout << "Tamanho do mapa escolhido: " << tamanhoCaminho << endl;
    }

    // Verificação de alocação do caminho
    if (tamanhoCaminho <= 0) {
        cout << "Erro: tamanho do caminho inválido!" << endl;
        return;
    }

    // Aloca dinamicamente o array do caminho
    caminho = new Sqm[tamanhoCaminho];
    for (int i = 0; i < tamanhoCaminho; ++i) {
        caminho[i].vazio = true;
        caminho[i].inimigo = nullptr;
        caminho[i].item = nullptr;
    }
    cout << "Mapa inicializado com sucesso. Tamanho do caminho: " << tamanhoCaminho << endl;
}

void Mapa::adicionarInimigo(int posicao, Inimigo* inimigo) {
    if (posicao >= 0 && posicao < tamanhoCaminho) {
        caminho[posicao].vazio = false;
        caminho[posicao].inimigo = inimigo;
        cout << "Inimigo adicionado no sqm " << posicao << endl;
    } else {
        cout << "Erro: posição inválida para adicionar inimigo!" << endl;
    }
}

void Mapa::adicionarItem(int posicao, Item* item) {
    if (posicao >= 0 && posicao < tamanhoCaminho) {
        caminho[posicao].vazio = false;
        caminho[posicao].item = item;
        cout << "Item adicionado no sqm " << posicao << endl;
    } else {
        cout << "Erro: posição inválida para adicionar item!" << endl;
    }
}

bool Mapa::moverParaProximaPosicao() {
    if (posicaoAtual < tamanhoCaminho - 1) {
        ++posicaoAtual;
        cout << "Movendo para a posição " << posicaoAtual << endl;

        // Aleatoriedade para definir o evento neste sqm
        int eventoAleatorio = rand() % 4;  // Valores 0 a 3
        cout << "Gerando evento para o sqm " << posicaoAtual << endl;
        
        if (eventoAleatorio == 0) {
            // Gera um inimigo aleatório
            int tipoInimigo = rand() % 3;  // 0, 1 ou 2 para tipos de inimigos
            cout << "Inimigo gerado no sqm " << posicaoAtual << endl;
            if (tipoInimigo == 0) {
                adicionarInimigo(posicaoAtual, new Inimigo("Morcego Mutante", 50, 10));
            } else if (tipoInimigo == 1) {
                adicionarInimigo(posicaoAtual, new Inimigo("Zumbi", 30, 5));
            } else {
                adicionarInimigo(posicaoAtual, new Inimigo("Pincher", 40, 7));
            }
        } else if (eventoAleatorio == 1) {
            // Gera uma arma aleatória
            int tipoArma = rand() % 2;
            cout << "Arma gerada no sqm " << posicaoAtual << endl;
            if (tipoArma == 0) {
                adicionarItem(posicaoAtual, new Arma("Machado", 5, 15));
            } else {
                adicionarItem(posicaoAtual, new Arma("Espada", 3, 10));
            }
        } else if (eventoAleatorio == 2) {
            // Gera uma poção aleatória
            int tipoPocao = rand() % 2;
            cout << "Poção gerada no sqm " << posicaoAtual << endl;
            if (tipoPocao == 0) {
                adicionarItem(posicaoAtual, new Pocao("Poção Pequena", 1, 10));
            } else {
                adicionarItem(posicaoAtual, new Pocao("Poção Grande", 3, 30));
            }
        } else {
            // O sqm fica vazio
            caminho[posicaoAtual].vazio = true;
            cout << "Você encontrou um sqm vazio." << endl;
        }

        return true;
    }
    cout << "Fim do mapa atingido." << endl;
    return false; // Se não houver mais posições, retorna falso
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
        cout << "Mapa destruído com sucesso." << endl;
    }
}

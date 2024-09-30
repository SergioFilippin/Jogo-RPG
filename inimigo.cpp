//INTEGRANTES SERGIO LUIS FILIPPIN 2259500
//              IGOR LUIS DIAS 2199713
//              VINICIUS BRANQUINHO 2187258

#include "Inimigo.h"
#include <iostream>

Inimigo::Inimigo(const char* nomeInicial, int pontosDeVida, int capacidadeDeAtaque)
    : nome(nomeInicial), pontosDeVida(pontosDeVida), capacidadeDeAtaque(capacidadeDeAtaque) {}

void Inimigo::atacar() {
    std::cout << nome << " ataca com forca de " << capacidadeDeAtaque << " pontos de dano!" << std::endl;
}

void Inimigo::receberDano(int dano) {
    pontosDeVida -= dano;
    if (pontosDeVida < 0) pontosDeVida = 0;
    std::cout << nome << " recebeu " << dano << " pontos de dano. Vida restante: " << pontosDeVida << std::endl;
}

bool Inimigo::estaVivo() const {
    return pontosDeVida > 0;
}

void Inimigo::mostrarStatus() const {
    std::cout << "Inimigo: " << nome << ", Vida: " << pontosDeVida << ", Ataque: " << capacidadeDeAtaque << std::endl;
}

int Inimigo::getPontosDeVida() const {
    return pontosDeVida;
}

int Inimigo::getCapacidadeDeAtaque() const {
    return capacidadeDeAtaque;
}

const std::string& Inimigo::getNome() const {
    return nome;
}

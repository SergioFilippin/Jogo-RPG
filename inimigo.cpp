#include "Inimigo.h"
#include <iostream>

// Construtor para Inimigo
Inimigo::Inimigo(const char* nomeInicial, int pontosDeVida, int capacidadeDeAtaque)
    : nome(nomeInicial), pontosDeVida(pontosDeVida), capacidadeDeAtaque(capacidadeDeAtaque) {}

// Realiza o ataque do inimigo
void Inimigo::atacar() {
    std::cout << nome << " ataca com força de " << capacidadeDeAtaque << " pontos de dano!" << std::endl;
}

// O inimigo recebe dano
void Inimigo::receberDano(int dano) {
    pontosDeVida -= dano;
    if (pontosDeVida < 0) pontosDeVida = 0;
    std::cout << nome << " recebeu " << dano << " pontos de dano. Vida restante: " << pontosDeVida << std::endl;
}

// Verifica se o inimigo ainda está vivo
bool Inimigo::estaVivo() const {
    return pontosDeVida > 0;
}

// Mostra o status do inimigo
void Inimigo::mostrarStatus() const {
    std::cout << "Inimigo: " << nome << ", Vida: " << pontosDeVida << ", Ataque: " << capacidadeDeAtaque << std::endl;
}

// Retorna os pontos de vida do inimigo
int Inimigo::getPontosDeVida() const {
    return pontosDeVida;
}

// Retorna a capacidade de ataque do inimigo
int Inimigo::getCapacidadeDeAtaque() const {
    return capacidadeDeAtaque;
}

// Retorna o nome do inimigo
const std::string& Inimigo::getNome() const {
    return nome;
}

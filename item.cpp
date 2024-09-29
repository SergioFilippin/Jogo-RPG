#include "Item.h"
#include <iostream>

// Construtor para Item
Item::Item(const char* nomeInicial, int peso)
    : nome(nomeInicial), peso(peso) {}

// Retorna o nome do item
const std::string& Item::getNome() const {
    return nome;
}

// Retorna o peso do item
int Item::getPeso() const {
    return peso;
}

// Mostra os detalhes do item (pode ser sobrescrito por subclasses)
void Item::mostrarDetalhes() const {
    std::cout << "Item: " << nome << ", Peso: " << peso << std::endl;
}

// Construtor para Arma
Arma::Arma(const char* nomeInicial, int peso, int capacidadeDeAtaque)
    : Item(nomeInicial, peso), capacidadeDeAtaque(capacidadeDeAtaque) {}

// Retorna a capacidade de ataque da arma
int Arma::getCapacidadeDeAtaque() const {
    return capacidadeDeAtaque;
}

// Mostra os detalhes da arma
void Arma::mostrarDetalhes() const {
    std::cout << "Arma: " << getNome() << ", Ataque: " << capacidadeDeAtaque << ", Peso: " << getPeso() << std::endl;
}

// Construtor para Poção
Pocao::Pocao(const char* nomeInicial, int peso, int capacidadeDeCura)
    : Item(nomeInicial, peso), capacidadeDeCura(capacidadeDeCura) {}

// Retorna a capacidade de cura da poção
int Pocao::getCapacidadeDeCura() const {
    return capacidadeDeCura;
}

// Mostra os detalhes da poção
void Pocao::mostrarDetalhes() const {
    std::cout << "Poção: " << getNome() << ", Cura: " << capacidadeDeCura << ", Peso: " << getPeso() << std::endl;
}

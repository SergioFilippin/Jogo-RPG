#include <iostream>
#include "Heroi.h"   // Inclui a definição da classe Heroi
#include "Jogo.h"    // Inclui a definição da classe Jogo
#include "Mapa.h"    // Inclui a definição da classe Mapa
#include "Item.h"    // Inclui a definição da classe Item
#include "Inimigo.h" // Inclui a definição da classe Inimigo

int main() {
    // Bem-vindo ao jogo
    std::cout << "Bem-vindo ao RPG!\n";

    // Criar o herói (nome, vida e força podem ser personalizadas)
    std::string nomeHeroi;
    std::cout << "Digite o nome do seu herói: ";
    std::cin >> nomeHeroi;

    int vidaHeroi = 100;  // Definimos um valor padrão para os pontos de vida do herói
    int forcaHeroi = 10;  // Definimos um valor padrão para a força do herói

    // Instanciação do herói
    Heroi* heroi = new Heroi(nomeHeroi, vidaHeroi, forcaHeroi);

    // Criar o jogo e passar o herói para ele
    Jogo jogo(heroi);

    // Iniciar o jogo
    jogo.iniciar();

    // Ao finalizar o jogo, liberar memória
    delete heroi;

    return 0;
}
  
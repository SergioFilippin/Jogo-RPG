//INTEGRANTES SERGIO LUIS FILIPPIN 2259500
//              IGOR LUIS DIAS 2199713
//              VINICIUS BRANQUINHO 2187258
#include "Heroi.h"
#include "Jogo.h"
#include "Mapa.h"
#include "Item.h"
#include "Inimigo.h"
#include <iostream>

using namespace std;

int main() {

    cout << "Bem-vindo ao RPG!\n";

    string nomeHeroi;
    cout << "Digite o nome do seu heroi: ";
    cin >> nomeHeroi;

    Heroi* heroi = new Heroi(nomeHeroi, 100, 10);
    Jogo jogo(heroi);

    jogo.iniciar();

    delete heroi;
    return 0;
}

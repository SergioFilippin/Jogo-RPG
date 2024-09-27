// INTEGRANTES SERGIO LUIS FILIPPIN 2259500
//              IGOR LUIS DIAS 2199713
//              VINICIUS BRANQUINHO 2187258

#ifndef HEROI_H
#define HEROI_H

#include <string>
using namespace std;

class Item;

class Heroi {
public:
    Heroi(const string& nome, int vida, int forca);
    ~Heroi();  // Destrutor adicionado; sergio

    // Gerenciamento de Item ; sergio
    bool adicionar_item_mochila(Item* item);
    bool adicionar_item_cinto(Item* item);
    Item* remover_item_cinto(int indice);
    Item* usar_item_mochila();

    // Modo de combate ; sergio
    void ataque();
    void receberdano(int dano);
    void usarpocao(Item* pocao);

    int getVida() const;  // Adiciona um getter para vida ; alterado por Branquinho
    void displayStatus() const;  // Mostra o status do herói ; passado para esse script por Branquinho

private:
    string nome;   // Nome do herói ; sergio
    int vida;           // Pontos de vida do herói ; sergio

    static const int VIDA_MAXIMA = 200; // Vida máxima do herói ; sergio
    static const int CAPACIDADE_MAX_CINTO = 5; // Capacidade máxima do cinto ; sergio
    Item* cinto[CAPACIDADE_MAX_CINTO];  // Array de ponteiros para itens no cinto ; sergio
    
    int pesomochila;   // Peso atual dos itens na mochila ; sergio
    Item** mochila;    // Array dinâmico ponteiro para mochila ; sergio
    int capacidademochila;  // Capacidade da mochila ; sergio
    int topomochila;        // Topo e acesso da mochila ; sergio


};

#endif 

#ifndef HEROI_H
#define HEROI_H
#include <string>

using namespace std;

class Item;

class Heroi {

public:
    Heroi(const string& nome, int vida, int forca);

    // Gerenciamento de Item
    bool adicionar_item_mochila(Item* item);
    bool adicionar_item_cinto(Item* item);
    Item* remover_item_cinto (int remove);
    Item* usar_item_mochila();

    // Modo de combate
    void ataque();
    void receberdano(int dano);
    void usarpocao(Item* pocao);

    // Status
    void vivo() const;
    void mostrarstatus() const;

    // Inventario
    void editarinventario();

    int ganharvida() const;
    const string& nome() const;

private:

    string nome;    // Nome do herói
    int vida;    // Pontos de vida do herói

    static const int VIDA_MAXIMA = 200; // Vida máxima do herói; sergio
    static const int CAPACIDADE_MAX_CINTO = 5; // Capacidade máxima do cinto
    Item* cinto[CAPACIDADE_MAX_CINTO];  // Array de ponteiros para itens no cinto
    int pesoAtualMochila;   // Peso atual dos itens no cinto


    static const int CAPACIDADE_MAX_MOCHILA = 10;   // Capacidade máxima da mochila
    Item* mochila[CAPACIDADE_MAX_MOCHILA];  // Array de ponteiros para itens na mochila
    int topoMochila;
};

#endif
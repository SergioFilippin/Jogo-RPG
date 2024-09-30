//INTEGRANTES SERGIO LUIS FILIPPIN 2259500
//              IGOR LUIS DIAS 2199713
//              VINICIUS BRANQUINHO 2187258
#ifndef INIMIGO_H
#define INIMIGO_H

#include <string>

class Inimigo {
private:
    std::string nome;
    int pontosDeVida;
    int capacidadeDeAtaque;

public:
    Inimigo(const char* nomeInicial, int pontosDeVida, int capacidadeDeAtaque);

    void atacar();
    void receberDano(int dano);
    bool estaVivo() const;
    void mostrarStatus() const;

    int getPontosDeVida() const;
    int getCapacidadeDeAtaque() const;
    const std::string& getNome() const;
};

#endif

#ifndef INIMIGO_H
#define INIMIGO_H

class Inimigo {
private:
    static const int TAMANHO_MAX_NOME = 50;        // Tamanho máximo para o nome do inimigo
    char nome[TAMANHO_MAX_NOME];                  // Nome do inimigo
    int pontosDeVida;                             // Pontos de vida do inimigo
    int capacidadeDeAtaque;                       // Capacidade de ataque do inimigo

public:
    // Construtor
    Inimigo(const char* nomeInicial, int pontosDeVida, int capacidadeDeAtaque);

    // Métodos de combate
    void atacar();                                // Realiza o ataque do inimigo (implementar no .cpp)
    void receberDano(int dano);                   // Reduzir os pontos de vida ao receber dano

    // Métodos de status
    bool estaVivo() const;                        // Verificar se o inimigo ainda está vivo
    void mostrarStatus() const;                   // Mostrar status do inimigo

    // Acessores
    int getPontosDeVida() const;
    int getCapacidadeDeAtaque() const;
    const char* getNome() const;
};

#endif // INIMIGO_H

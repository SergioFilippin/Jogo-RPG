// Jogo.cpp
// INTEGRANTES SERGIO LUIS FILIPPIN 2259500
//              IGOR LUIS DIAS 2199713
//              VINICIUS BRANQUINHO 2187258

#include "Jogo.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;  // Simplifica a manipulação de strings e streams

// Construtor do Jogo ; passado para esse script por Branquinho
Jogo::Jogo(Heroi* heroi) : heroi(heroi), numInimigos(0), numItens(0), nivelAtual(0), mapaAtual(nullptr) {
    srand(time(0)); // Inicializa a semente para números randômicos
    gerarInimigos();  // Gera inimigos para o jogo
    gerarItens();     // Gera itens para o jogo
}

// Função de batalha ; já implementada por Branquinho
void Jogo::batalha(Inimigo* inimigo) {
    cout << "Batalha iniciada contra o inimigo: " << inimigo->getNome() << "!" << endl;

    while (heroi->getVida() > 0 && inimigo->estaVivo()) {
        // Mostrar status do herói e inimigo
        heroi->displayStatus();
        inimigo->mostrarStatus();

        // Escolher arma (cinto ou mochila)
        cout << "Escolha uma arma do cinto (1) ou mochila (2): ";
        int escolha;
        cin >> escolha;

        Item* arma = nullptr;

        if (escolha == 1) {
            cout << "Escolha a posição do cinto (0 a 4): ";
            int posicao;
            cin >> posicao;
            arma = heroi->remover_item_cinto(posicao);
        } else if (escolha == 2) {
            arma = heroi->usar_item_mochila();  // Acessa o item no topo da mochila
        }

        if (arma != nullptr) {
            Arma* armaEscolhida = dynamic_cast<Arma*>(arma);
            if (armaEscolhida) {
                // Herói ataca o inimigo
                int danoHeroi = armaEscolhida->getCapacidadeDeAtaque();
                cout << "Você atacou com " << danoHeroi << " de dano!" << endl;
                inimigo->receberDano(danoHeroi);
            }
        } else {
            cout << "Nenhuma arma foi selecionada!" << endl;
        }

        // Se o inimigo ainda estiver vivo, ele contra-ataca
        if (inimigo->estaVivo()) {
            int danoInimigo = inimigo->getCapacidadeDeAtaque();
            cout << inimigo->getNome() << " atacou com " << danoInimigo << " de dano!" << endl;
            heroi->receberdano(danoInimigo);
        }
    }

    // Verificar o resultado da batalha
    if (heroi->getVida() <= 0) {
        cout << "Você foi derrotado! Fim de jogo." << endl;
        salvarPontuacao();  // Salva a pontuação antes de finalizar ; passado para esse script por Branquinho
        exit(0);  // Finaliza o jogo se o herói morrer
    } else {
        cout << "Você venceu a batalha contra " << inimigo->getNome() << "!" << endl;
    }
}

// Função para interagir com um item encontrado ; já implementada por Branquinho
void Jogo::interagirComItem(Item* item) {
    cout << "Você encontrou um item: " << item->getNome() << endl;
    cout << "Deseja guardar o item no cinto (1), na mochila (2) ou descartá-lo (3)?" << endl;
    
    int escolha;
    cin >> escolha;

    if (escolha == 1) {
        // Adicionar item ao cinto
        if (!heroi->adicionar_item_cinto(item)) {
            cout << "O cinto está cheio, item não pode ser adicionado." << endl;
        } else {
            cout << "Item adicionado ao cinto!" << endl;
        }
    } else if (escolha == 2) {
        // Adicionar item à mochila
        if (!heroi->adicionar_item_mochila(item)) {
            cout << "A mochila está cheia, item não pode ser adicionado." << endl;
        } else {
            cout << "Item adicionado à mochila!" << endl;
        }
    } else {
        // Descartar o item
        cout << "Você descartou o item: " << item->getNome() << endl;
    }
}

// Função para mover o herói de um sqm para outro ; passado para esse script por Branquinho
void Jogo::mover() {
    int posicaoAtual = 0;
    mapaAtual = new Mapa(10); // Exemplo com 10 sqms no mapa ; passado para esse script por Branquinho
    mapaAtual->gerarInimigos();  // Popula o mapa com inimigos
    mapaAtual->gerarItem();  // Popula o mapa com itens

    while (posicaoAtual < mapaAtual->getTamanho()) {
        Sqm& sqmAtual = mapaAtual->getSqm(posicaoAtual);
        cout << "Você está no sqm " << posicaoAtual << endl;

        // Verifica se o sqm tem um inimigo
        if (sqmAtual.temInimigo()) {
            Inimigo* inimigo = sqmAtual.getInimigo();
            cout << "Você encontrou um inimigo: " << inimigo->getNome() << endl;
            batalha(inimigo);  // Inicia uma batalha com o inimigo
        }

        // Verifica se o sqm tem um item
        if (sqmAtual.temItem()) {
            Item* item = sqmAtual.getItem();
            cout << "Você encontrou um item: " << item->getNome() << endl;
            interagirComItem(item);  // Interage com o item
        }

        // Se o sqm estiver vazio
        if (sqmAtual.estaVazio()) {
            cout << "Este sqm está vazio. Avance para o próximo." << endl;
        }

        posicaoAtual++;
    }

    cout << "Você completou o nível!" << endl;
    avancarNivel();  // Avança para o próximo nível ; passado para esse script por Branquinho
}

// Função para avançar para o próximo nível ; passado para esse script por Branquinho
void Jogo::avancarNivel() {
    nivelAtual++;
    cout << "Você avançou para o nível " << nivelAtual << "!" << endl;

    // Recalcular dificuldade, aumentar inimigos ou tornar os inimigos mais fortes
    gerarInimigos();
    gerarItens();
}

// Função para salvar as pontuações no arquivo ; passado para esse script por Branquinho
void Jogo::salvarPontuacao() {
    ofstream arquivo("high_scores.txt", ios::app);  // Abre o arquivo em modo de append
    if (arquivo.is_open()) {
        arquivo << heroi->getNome() << " - Nível alcançado: " << nivelAtual << endl;
        arquivo.close();
    } else {
        cout << "Não foi possível abrir o arquivo high_scores.txt." << endl;
    }
}

// Função para iniciar o jogo e gerenciar as interações ; já implementada por Branquinho
void Jogo::iniciar() {
    cout << "Bem-vindo ao jogo! O herói está pronto para a aventura!" << endl;
    heroi->displayStatus();

    mover();  // Chama a função para mover o herói pelo mapa ; passado para esse script por Branquinho
}

// Gerar inimigos aleatoriamente ; já implementada por Branquinho
void Jogo::gerarInimigos() {
    for (int i = 0; i < MAX_INIMIGOS; ++i) {
        int vida = rand() % 50 + 50;  // Vida entre 50 e 100
        int ataque = rand() % 10 + 10;  // Ataque entre 10 e 20
        inimigos[i] = new Inimigo("Inimigo", vida, ataque);
        numInimigos++;
    }
}

// Gerar itens aleatoriamente ; já implementada por Branquinho
void Jogo::gerarItens() {
    for (int i = 0; i < MAX_ITENS; ++i) {
        int tipo = rand() % 2;  // 0 para arma, 1 para poção
        if (tipo == 0) {
            itens[i] = new Arma("Espada", 10, rand() % 10 + 5);  // Capacidade de ataque entre 5 e 15
        } else {
            itens[i] = new Pocao("Poção de Cura", 5, rand() % 20 + 10);  // Cura entre 10 e 30
        }
        numItens++;
    }
}

// Destrutor do Jogo ; já implementada por Branquinho
Jogo::~Jogo() {
    delete heroi;
    delete mapaAtual;  // Liberar a memória alocada para o mapa ; passado para esse script por Branquinho
    for (int i = 0; i < numInimigos; ++i) {
        delete inimigos[i];
    }
    for (int i = 0; i < numItens; ++i) {
        delete itens[i];
    }
}

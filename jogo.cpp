#include "Jogo.h"
#include "Mapa.h"
#include <iostream>
#include <cstdlib> // Para rand e srand
#include <ctime>   // Para time

using namespace std;

Jogo::Jogo(Heroi* heroi) : heroi(heroi), numInimigos(0), numItens(0), nivelAtual(0) {
    srand(static_cast<unsigned int>(time(nullptr))); // Semente para geração aleatória
}

void Jogo::iniciar() {
    cout << "Bem-vindo ao RPG! \n";

    // Inicializar o mapa
    int tamanhoMapa;
    cout << "Escolha o tamanho do mapa (1 a 20): ";
    cin >> tamanhoMapa;
    if (tamanhoMapa < 1 || tamanhoMapa > 20) {
        tamanhoMapa = 20; // Tamanho padrão se o valor estiver fora do intervalo
    }

    cout << "Criando o mapa...\n";
    Mapa mapa(tamanhoMapa); // Criar o mapa

    cout << "Mapa criado com sucesso!\n";
    cout << "Iniciando o loop do jogo...\n";

    // Loop do jogo
    while (!nivelCompleto()) {
        cout << "Você está no nível " << nivelAtual + 1 << endl;
        
        while (!mapa.fimDoMapa()) {
            cout << "Movendo para o próximo sqm...\n";
            if (!mapa.moverParaProximaPosicao()) {
                cout << "Fim do mapa atingido!\n";
                break;
            }
            Mapa::Sqm posicaoAtual = mapa.getPosicaoAtual();

            if (posicaoAtual.vazio) {
                cout << "Você encontrou um sqm vazio." << endl;
            } 
            else if (posicaoAtual.item != nullptr) {
                cout << "Você encontrou um item: " << posicaoAtual.item->getNome() << endl;
                interagirComItem(posicaoAtual.item);
            } 
            else if (posicaoAtual.inimigo != nullptr) {
                cout << "Você encontrou um inimigo: " << posicaoAtual.inimigo->getNome() << endl;
                batalha(posicaoAtual.inimigo);
            }
        }

        cout << "Você completou o nível!" << endl;
        avancarNivel();
    }
}

void Jogo::avancarNivel() {
    cout << "Avançando para o próximo nível...\n";
    
    // Incrementa o nível atual
    nivelAtual++;

    // Se o jogador completar todos os níveis, finalizar o jogo
    if (nivelAtual >= MAX_NIVEIS) {
        cout << "Parabéns! Você completou todos os níveis!" << endl;
        exit(0); // Finaliza o jogo
    } else {
        cout << "Gerando inimigos e itens para o próximo nível...\n";

        // Libera os itens e inimigos anteriores
        for (int i = 0; i < numInimigos; ++i) {
            cout << "Liberando memória do inimigo...\n";
            delete inimigos[i];
        }
        numInimigos = 0;

        for (int i = 0; i < numItens; ++i) {
            cout << "Liberando memória do item...\n";
            delete itens[i];
        }
        numItens = 0;

        // Gera novos inimigos e itens para o próximo nível
        gerarInimigos();
        gerarItens();
        cout << "Novo nível gerado!\n";
    }
}

bool Jogo::nivelCompleto() const {
    return numInimigos == 0; // Verifica se ainda existem inimigos
}

void Jogo::gerarInimigos() {
    // Exemplo de geração de inimigos
    for (int i = 0; i < MAX_INIMIGOS; ++i) {
        Inimigo* novoInimigo = nullptr;
        int tipo = rand() % 3; // Aleatório entre 0 e 2

        if (tipo == 0) {
            novoInimigo = new Inimigo("Morcego Mutante", 50, 10); // Exemplo de atributos
        } else if (tipo == 1) {
            novoInimigo = new Inimigo("Zumbi", 30, 5);
        } else {
            novoInimigo = new Inimigo("Pincher", 40, 7);
        }

        inimigos[numInimigos++] = novoInimigo; // Adicionar o novo inimigo ao array
    }
}

void Jogo::gerarItens() {
    // Exemplo de geração de itens
    for (int i = 0; i < MAX_ITENS; ++i) {
        Item* novoItem = nullptr;
        int tipo = rand() % 2; // Aleatório entre 0 e 1

        if (tipo == 0) {
            novoItem = new Arma("Machado", 5, 15); // Exemplo de atributos
        } else {
            novoItem = new Arma("Espada", 3, 10);
        }

        itens[numItens++] = novoItem; // Adicionar o novo item ao array
    }
}

void Jogo::batalha(Inimigo* inimigo) {
    // Exemplo de lógica de batalha
    cout << "Você está em batalha contra " << inimigo->getNome() << "!" << endl;

    // Loop da batalha até que um dos dois perca todos os pontos de vida
    while (heroi->getVida() > 0 && inimigo->estaVivo()) {
        heroi->ataque();
        inimigo->receberDano(heroi->getForca());

        if (!inimigo->estaVivo()) {
            cout << "Você derrotou o inimigo!" << endl;
            numInimigos--; // Reduz o número de inimigos restantes no nível
            break;
        }

        inimigo->atacar();
        heroi->receberdano(inimigo->getCapacidadeDeAtaque());

        if (heroi->getVida() <= 0) {
            cout << "Você foi derrotado!" << endl;
            exit(0); // Finaliza o jogo se o herói perder
        }
    }
}

void Jogo::interagirComItem(Item* item) {
    // Exemplo de lógica para interagir com um item encontrado
    cout << "Você encontrou um item: " << item->getNome() << endl;
    cout << "Deseja pegar o item? (1 - Sim, 0 - Não): ";
    int escolha;
    cin >> escolha;

    if (escolha == 1) {
        // Pergunta onde o jogador quer colocar o item
        cout << "Colocar o item no cinto (1) ou na mochila (2)?: ";
        int escolhaLocal;
        cin >> escolhaLocal;

        if (escolhaLocal == 1) {
            // Tenta adicionar ao cinto
            if (heroi->adicionar_item_cinto(item)) {
                cout << "Você adicionou o item ao cinto!" << endl;
            } else {
                cout << "Cinto cheio! Não foi possível adicionar o item." << endl;
            }
        } else if (escolhaLocal == 2) {
            // Tenta adicionar à mochila
            if (heroi->adicionar_item_mochila(item)) {
                cout << "Você adicionou o item à sua mochila!" << endl;
            } else {
                cout << "Mochila cheia! Não foi possível pegar o item." << endl;
            }
        } else {
            cout << "Opção inválida! O item foi descartado." << endl;
        }
    } else {
        cout << "Você ignorou o item." << endl;
    }
}

Jogo::~Jogo() {
    // Libera a memória alocada para os inimigos e itens
    for (int i = 0; i < numInimigos; ++i) {
        delete inimigos[i];
    }

    for (int i = 0; i < numItens; ++i) {
        delete itens[i];
    }

    delete heroi; // Libera a memória alocada para o herói
}

//INTEGRANTES SERGIO LUIS FILIPPIN 2259500
//              IGOR LUIS DIAS 2199713
//              VINICIUS BRANQUINHO 2187258
#include "Jogo.h"
#include "Mapa.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

using namespace std;

Jogo::Jogo(Heroi* heroi) : heroi(heroi), numInimigos(0), numItens(0), nivelAtual(0) {
    srand(static_cast<unsigned int>(time(NULL))); // Semente para geração aleatória
}

void limparConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void Jogo::iniciar() {
    cout << "Bem-vindo ao mundo da Forja! \n";

    string nomeHeroi;
    cout << "Digite o nome do seu pequenino heroi: ";
    getline(cin, nomeHeroi);

    limparConsole();

    string resposta;
    cout << "Deseja iniciar sua jornada, " << nomeHeroi << "? (sim/nao): ";
    cin >> resposta;

    if (resposta != "sim") {
        cout << "A jornada foi encerrada. Ate a proxima!" << endl;
        return;
    }

    int tamanhoMapa;
    cout << "Escolha o tamanho da terra intermedia (1 a 20):";
    cin >> tamanhoMapa;
    if (tamanhoMapa < 1 || tamanhoMapa > 20) {
        cout << "Tamanho do mapa invalido! Definindo para 20 por padrao.\n";
        tamanhoMapa = 20;
    }

    Mapa mapa(false, tamanhoMapa);
    limparConsole();

    while (!mapa.fimDoMapa()) {
        cout << "Gostaria de prosseguir em frente, pequeno aventureiro? (sim/nao): ";
        cin >> resposta;

        if (resposta != "sim") {
            cout << "A jornada foi encerrada. Ate a proxima!" << endl;
            return;
        }

        limparConsole();

        if (!mapa.moverParaProximaPosicao()) {
            break;
        }

        Mapa::Sqm posicaoAtual = mapa.getPosicaoAtual();

        if (posicaoAtual.vazio) {
            cout << "Voce encontrou um caminho vazio." << endl;
            organizarItens();
        } else if (posicaoAtual.item != NULL) {
            cout << "O item encontrado foi: " << posicaoAtual.item->getNome() << endl;
            interagirComItem(posicaoAtual.item);
        } else if (posicaoAtual.inimigo != NULL) {
            cout << "O inimigo " << posicaoAtual.inimigo->getNome() << " emergiu das sombras!" << endl;
            cout << "Prepare-se para a batalha!" << endl;
            batalha(posicaoAtual.inimigo);
        }
    }

    cout << "Você completou o mapa!\n";
    avancarNivel();
}

void Jogo::batalha(Inimigo* inimigo) {
    cout << "Voce esta em batalha contra " << inimigo->getNome() << endl;

    while (heroi->getVida() > 0 && inimigo->estaVivo()) {
        string escolha;
        cout << "Deseja atacar ou usar uma pocao? (atacar/pocao): ";
        cin >> escolha;

        limparConsole();

        if (escolha == "pocao") {
            usarPocao();
        } else {
            cout << "Escolha uma arma do seu cinto (indice de 0 a 4) ou use a arma no topo da mochila (5): ";
            int escolhaArma;
            cin >> escolhaArma;

            Item* arma = NULL;

            if (escolhaArma >= 0 && escolhaArma < 5) {
                arma = heroi->verItemCinto(escolhaArma);
            } else if (escolhaArma == 5) {
                arma = heroi->verItemTopoMochila();
            }

            if (arma != NULL && dynamic_cast<Arma*>(arma)) {
                Arma* armaEscolhida = dynamic_cast<Arma*>(arma);
                cout << "Voce esta atacando com a arma: " << armaEscolhida->getNome() << endl;
                heroi->ataque();
                inimigo->receberDano(armaEscolhida->getCapacidadeDeAtaque());
            } else {
                cout << "Voce atacou sem arma!" << endl;
                heroi->ataque();
                inimigo->receberDano(heroi->getForca());
            }

            if (!inimigo->estaVivo()) {
                cout << "Voce derrotou o inimigo!" << endl;
                numInimigos--;
                break;
            }

            inimigo->atacar();
            heroi->receberdano(inimigo->getCapacidadeDeAtaque());

            if (heroi->getVida() <= 0) {
                cout << "Voce foi derrotado! Fim do jogo!" << endl;
                exit(0);
            }
        }
    }
}

void Jogo::usarPocao() {
    // Primeiro, verifica se há poção no cinto
    Item* pocaoCinto = NULL;
    int indiceCinto = -1;

    for (int i = 0; i < 5; ++i) {
        Item* itemCinto = heroi->verItemCinto(i);
        if (itemCinto != NULL && dynamic_cast<Pocao*>(itemCinto)) {
            pocaoCinto = itemCinto;
            indiceCinto = i;
            break;
        }
    }

    // Verifica se há poção na mochila
    Item* pocaoMochila = heroi->verItemTopoMochila();

    // Verifica se há poção disponível
    if (pocaoCinto == NULL && pocaoMochila == NULL) {
        cout << "Voce nao tem pocoes disponiveis!" << endl;
        return;
    }

    // Se houver poções tanto no cinto quanto na mochila, dá a opção de escolher
    if (pocaoCinto != NULL && pocaoMochila != NULL) {
        cout << "Voce tem pocoes no cinto e na mochila. Deseja usar a pocao do cinto (1) ou da mochila (2)?" << endl;
        int escolhaPocao;
        cin >> escolhaPocao;

        if (escolhaPocao == 1) {
            heroi->usarpocao(pocaoCinto);
            heroi->remover_item_cinto(indiceCinto);  // Remove a poção do cinto
        } else if (escolhaPocao == 2) {
            heroi->usarpocao(pocaoMochila);
            heroi->usar_item_mochila();  // Remove a poção da mochila
        } else {
            cout << "Opcao invalida, nenhuma pocao usada." << endl;
        }
    }
    // Caso só tenha poção no cinto
    else if (pocaoCinto != NULL) {
        heroi->usarpocao(pocaoCinto);
        heroi->remover_item_cinto(indiceCinto);  // Remove a poção do cinto
    }
    // Caso só tenha poção na mochila
    else if (pocaoMochila != NULL) {
        heroi->usarpocao(pocaoMochila);
        heroi->usar_item_mochila();  // Remove a poção da mochila
    }
}

void Jogo::interagirComItem(Item* item) {
    string escolha;
    cout << "Deseja guardar o item ou deixa-lo descansando na terra? (guardar/deixar): ";
    cin >> escolha;

    limparConsole();

    if (escolha == "guardar") {
        cout << "Onde deseja guardar o item? (1 - Cinto, 2 - Mochila): ";
        int escolhaLocal;
        cin >> escolhaLocal;

        if (escolhaLocal == 1) {
            cout << "Estado atual do cinto: " << endl;
            for (int i = 0; i < 5; ++i) {
                if (heroi->temItemNoCinto(i)) {
                    cout << "Slot " << i << ": " << heroi->verItemCinto(i)->getNome() << endl;
                } else {
                    cout << "Slot " << i << ": vazio" << endl;
                }
            }

            cout << "Escolha um slot para guardar o item (0 a 4): ";
            int escolhaSlot;
            cin >> escolhaSlot;

            limparConsole();

            if (escolhaSlot >= 0 && escolhaSlot < 5) {
                if (heroi->adicionar_item_cinto(item, escolhaSlot)) {
                    cout << "Item adicionado ao cinto no slot " << escolhaSlot << "!" << endl;
                } else {
                    cout << "Cinto cheio! Não foi possivel adicionar o item." << endl;
                }
            } else {
                cout << "Opção invalida! O item foi descartado." << endl;
            }
        } else if (escolhaLocal == 2) {
            if (heroi->adicionar_item_mochila(item)) {
                cout << "Item adicionado a mochila!" << endl;
            } else {
                cout << "Mochila cheia! Não foi possivel pegar o item." << endl;
            }
        } else {
            cout << "Opcao invalida! O item foi descartado." << endl;
        }
    } else {
        cout << "Voce deixou o item descansando na terra." << endl;
    }
}

void Jogo::organizarItens() {
    string escolha;
    cout << "Deseja organizar seus itens (descartar algo)? (sim/nao): ";
    cin >> escolha;

    limparConsole();

    if (escolha == "sim") {
        cout << "Estado atual do cinto: " << endl;
        for (int i = 0; i < 5; ++i) {
            if (heroi->temItemNoCinto(i)) {
                cout << "Slot " << i << ": " << heroi->verItemCinto(i)->getNome() << endl;
            } else {
                cout << "Slot " << i << ": vazio" << endl;
            }
        }

        cout << "Item no topo da mochila: " << (heroi->verItemTopoMochila() ? heroi->verItemTopoMochila()->getNome() : "Nenhum") << endl;
        cout << "Item embaixo do topo da mochila: " << (heroi->verItemSubTopoMochila() ? heroi->verItemSubTopoMochila()->getNome() : "Nenhum") << endl;

        cout << "Escolha de onde deseja remover um item:\n1 - Cinto\n2 - Mochila\n3 - Cancelar\n";
        int opcao;
        cin >> opcao;

        limparConsole();

        if (opcao == 1) {
            int indice;
            cout << "Escolha o indice do item no cinto (0 a 4): ";
            cin >> indice;
            heroi->remover_item_cinto(indice);
        } else if (opcao == 2) {
            heroi->usar_item_mochila();
            cout << "Item removido do topo da mochila." << endl;
        }
    } else {
        cout << "Voce escolheu continuar a jornada." << endl;
    }
}

void Jogo::avancarNivel() {
    string resposta;
    cout << "Deseja avancar para o proximo nivel? (sim/nao): ";
    cin >> resposta;

    if (resposta == "sim") {
        nivelAtual++;
        if (nivelAtual >= MAX_NIVEIS) {
            cout << "Voce completou todos os niveis! Parabens!\n";
            exit(0);
        }
        gerarInimigos();
        gerarItens();
    } else {
        cout << "Voce escolheu encerrar a jornada. Ate a proxima!\n";
        exit(0);
    }
}

void Jogo::gerarInimigos() {
    for (int i = 0; i < MAX_INIMIGOS; ++i) {
        int tipo = rand() % 3;
        Inimigo* novoInimigo = NULL;
        if (tipo == 0) novoInimigo = new Inimigo("Morcego Mutante", 50, 10);
        else if (tipo == 1) novoInimigo = new Inimigo("Zumbi", 30, 5);
        else novoInimigo = new Inimigo("Pincher", 40, 7);

        inimigos[numInimigos++] = novoInimigo;
    }
}

void Jogo::gerarItens() {
    for (int i = 0; i < MAX_ITENS; ++i) {
        int tipo = rand() % 2;
        Item* novoItem = NULL;
        if (tipo == 0) novoItem = new Arma("Machado", 5, 15);
        else novoItem = new Arma("Espada", 3, 10);

        itens[numItens++] = novoItem;
    }
}

Jogo::~Jogo() {
    for (int i = 0; i < numInimigos; ++i) {
        delete inimigos[i];
    }
    for (int i = 0; i < numItens; ++i) {
        delete itens[i];
    }
    delete heroi;
}

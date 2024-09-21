#include "heroi.h"
#include <iostream>
#include <string>

using namespace std;

#ifndef HEROI_H
#define HEROI_H


// construtor classe heroi ; Sergio
Heroi::Heroi(const char* nome, int vida, int forca){
    :nome(nome), vida(vida), topoMochila(0), pesoAtualMochila(0){
       // inicializar cinto e mochila com ponteiros nulos ; sergio
        for (int i = 0; i < CAPACIDADE_MAX_CINTO; i++){
            cinto[i] = NULL;
        }
        for (int i = 0; i < CAPACIDADE_MAX_MOCHILA; i++){
            mochila[i] = NULL;
        }
    }
}

//adicionando mochila; sergio

bool Heroi::adicionar_item_mochila(Item* item){
    if (topoMochila < CAPACIDADE_MAX_MOCHILA){
        mochila[topoMochila++] = item;
        return true;
    }
    return false; // retorna false quando mochila cheia  ; sergio
}

//adicionando cinto; sergio
bool Heroi::adicionar_item_cinto(Item* item){
    for(int i = 0; i < CAPACIDADE_MAX_CINTO){
        if(cinto [i] == NULL)
        cinto [i] = item;
        return true;
    }
}
return false; // retorna false quando cinto cheio ; sergio 

//removendo item cinto ; sergio

bool Heroi::remover_item_cinto(int remove){
    if(remove >= 0 && remove < CAPACIDADE_MAX_CINTO && cinto[remove] != NULL);
    Item* retirado = cinto [remove];
    cinto[indice] = nullptr;
    return retirado;
}
return nullptr; // posição vazia ou indice do cinto invalido ; sergio

Item* Heroi::usar_item_mochila(){
    if(topoMochila > 0){
        return mochila[--topoMochila]; // faz a remocao do item do topo da mochila ; sergio
    }
    return nullptr; // mochila vazia; sergio
}

// combate do heroi

void Heroi::ataque(){
    cout << nome << "esta atacando!" << endl;
}
 void Heroi::receberdano(int dano) {
    vida -= dano;
    if (vida < 0) vida = 0;
    cout << nome << "recebeu " << dano << "de dano. Pontos vida atual:" << vida <<endl;   
 }

void Heroi::usarpocao(Item* pocao){
    vida += 30;
    if(vida > VIDA_MAXIMA){
        vida = VIDA_MAXIMA;
    }
        cout << nome << "Voce usou uma pocao! Uma parcela dos pontos de vida foi restaurada! " << vida << endl; 
}

#endif

























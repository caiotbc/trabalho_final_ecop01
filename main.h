#ifndef MAIN_H
#define MAIN_H
#include <QApplication>
#include <QTimer>
#include <fstream>
#include <QFile>
#include <time.h>
#include <unistd.h>
#include "mainwindow.h"
#include "pokemons.h"
#include "qpokemon.h"

void anda_jogador();
void loop_principal();
void checa_posicao_valida(int a);
void inicializa_mapa();
void modo_de_batalha();


int x_1; //posição do personagem no mapa
int y_1;

sprite *boneco; //personagem principal
QPokemon *pokemon_spr;
QPokemon *pokemon_spr_2;
QPokemon *pokemon_spr_3;
QPokemon *pokemon_spr_4;
QPokemon *pokemon_spr_5;

QImage mapa_obstaculos;
QColor cor_chao;

int estado_boneco;
int andando; //variável para saber se o personagem está andando
int mapa_ativado;
int poke_atual;
int evolucao_poke;
int modo_de_jogo;

pokedex pokemon_selvagem;
#endif // MAIN_H

#ifndef MAIN_H
#define MAIN_H
#include <QApplication>
#include <QTimer>
#include <fstream>
#include <QFile>
#include "mainwindow.h"

void anda_boneco();
void loop_principal();
void abre_arquivo(std::string a);
void imprime_matriz(int n, int m);
void checa_posicao_valida(int a);

int x_1; //posição do personagem no mapa
int y_1;

sprite *boneco; //personagem principal

int estado_boneco;
int andando; //variável para saber se o personagem está andando

int mapa_petalburg_obstaculos[768][700];

#endif // MAIN_H

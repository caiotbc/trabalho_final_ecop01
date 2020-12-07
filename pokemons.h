#ifndef POKEMONS_H
#define POKEMONS_H

#ifdef _WIN32
#define banco_de_dados "C:\\Users\\Usuario\\Documents\\GitHub\\trabalho_final_ecop01\\recursos\\data\\pokedex.db"
#endif

#ifdef linux
#define banco_de_dados "./pokedex.db"
#endif

#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlError>
#include <QDebug>

typedef struct
{
  QString nome;
  QString tipo;
  int id;
  int geracao;
  int nivel_evolui;
  int id_evolui;
  int imagem_x;
  int imagem_y;
}pokemon_catalogo_t;

struct pokedex
{
    int nivel;
    int hp;
    int id;
    int posicao;
};

int conecta_banco_de_dados();
void carrega_pokemons();




#endif // POKEMONS_H

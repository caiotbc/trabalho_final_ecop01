#ifndef POKEMONS_H
#define POKEMONS_H
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

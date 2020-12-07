#include "pokemons.h"

pokemon_catalogo_t poke_cat[40];

int conecta_banco_de_dados()
{
    QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./pokedex.db");
    if (!db.open())
    {
        qDebug() << db.lastError().text();
        return -1;
    }
    return 0;
}

void carrega_pokemons()
{
    QSqlQuery query;
    query.prepare("SELECT * from geracao1");
    query.exec();
    qDebug()<<query.executedQuery();
    int i = 0;
    while(query.next())
    {
        poke_cat[i].id = query.value(0).toInt();
        poke_cat[i].tipo = query.value(1).toString();
        poke_cat[i].nome = query.value(2).toString();
        poke_cat[i].imagem_x = query.value(3).toInt();
        poke_cat[i].imagem_y = query.value(4).toInt();
        poke_cat[i].nivel_evolui = query.value(5).toInt();
        poke_cat[i].id_evolui = query.value(6).toInt();
        poke_cat[i].geracao = query.value(7).toInt();
        switch (poke_cat[i].geracao)
        {
            case 1:
                poke_cat[i].imagem_x = 5 + (poke_cat[i].imagem_x-1)*69;
                poke_cat[i].imagem_y = 5 + (poke_cat[i].imagem_y-1)*69;
                break;
            case 2:
                poke_cat[i].imagem_x = 2149 + (poke_cat[i].imagem_x-1)*69;
                poke_cat[i].imagem_y = 5 + (poke_cat[i].imagem_y-1)*69;
                break;
            case 3:
                poke_cat[i].imagem_x = 3580 + (poke_cat[i].imagem_x-1)*69;
                poke_cat[i].imagem_y = 5 + (poke_cat[i].imagem_y-1)*69;
                break;
        }
        i++;
    }
}


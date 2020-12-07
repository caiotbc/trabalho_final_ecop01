#include "main.h"

#define VELOCIDADE_ANIMACAO 100
#define VELOCIDADE_PERSONAGEM 1
#define QTD_POKEMONS 30
#define DIFICULDADE 10

QGraphicsScene *cena;
extern pokemon_catalogo_t poke_cat[QTD_POKEMONS];
pokedex mochila_jogador[2];
QString bonus_mapa;
QString tipos[18] = {"BUG","DARK","DRAGON","ELECTRIC","FAIRY","FIGHT","FIRE","FLYING","GHOST","GRASS","GROUND","ICE","NORMAL","POISON","PSYCHIC","ROCK","STEEL","WATER"};

int main(int argc, char *argv[])
{
    srand(time(NULL));
    qDebug() << conecta_banco_de_dados();
    carrega_pokemons();
    QApplication a(argc, argv);
    MainWindow w;
    QPixmap fundo;

    w.show();
    mapa_ativado=0;
    modo_de_jogo = 0;

    poke_atual = 0;
    estado_boneco = 0;
    andando = 0;
    x_1 = 238; //Coordenadas de spawn
    y_1 = 59;

    int cena_x = 0;
    int cena_y = 0;

    int cena_largura =768;
    int cena_altura = 700;


    cena = new QGraphicsScene(cena_x,cena_y,cena_largura,cena_altura);
    w.set_scene(*cena); //configura a cena

    fundo.load(":/new/prefix1/recursos/images/login.png");
    cena->setBackgroundBrush(fundo);

    pokemon_spr = new QPokemon(&w);
    pokemon_spr_2 = new QPokemon(&w);
    pokemon_spr_3 = new QPokemon(&w);
    pokemon_spr_4 = new QPokemon(&w);
    pokemon_spr_5 = new QPokemon(&w);

    boneco = new sprite(&w,0); //sprite

    cena->addItem(pokemon_spr);
    pokemon_spr->setPos(562,299);

    cena->addItem(pokemon_spr_2);
    pokemon_spr_2->setPos(95,612);
    pokemon_spr_2->set_imagem_x(416);
    pokemon_spr_2->set_imagem_y(2078);

    cena->addItem(pokemon_spr_3);
    pokemon_spr_3->setPos(432,612);
    pokemon_spr_3->set_imagem_x(416);
    pokemon_spr_3->set_imagem_y(2078);

    QPixmap *obs= new QPixmap(":/new/prefix1/recursos/sprites/mapas/petalburg_woods_obstaculos.png");
    mapa_obstaculos = obs->toImage();

    return a.exec();
}

void loop_principal()
{
    if(poke_atual<0)
          poke_atual=0;
      switch (poke_cat[poke_atual].nivel_evolui)
      {
          case 10:
              evolucao_poke = 1;
              break;
          case 20:
              evolucao_poke = 2;
              break;
          case -1:
              evolucao_poke = 3;
              break;
      }
    if(mapa_ativado)
    {
        mapa_ativado=0;
        inicializa_mapa();
    }
    else
    {
        pokemon_spr->set_imagem_x(poke_cat[poke_atual].imagem_x);
        pokemon_spr->set_imagem_y(poke_cat[poke_atual].imagem_y);
        pokemon_spr->atualiza_imagem();
    }
    anda_jogador();
    if(cor_chao.value()==128 && andando && ta_na_hora() && modo_de_jogo==0)
    {
        //qDebug()<<"VAMO LUTA";
        bonus_mapa = "";
        modo_de_batalha();
    }
    for(int i = 0 ; i < 2 ; i++)
    {
        if(mochila_jogador[i].nivel>=poke_cat[mochila_jogador[i].posicao].nivel_evolui && poke_cat[mochila_jogador[i].posicao].id_evolui!=-1)
        {
            //qDebug()<<"evoluiu";
            mochila_jogador[i].id=poke_cat[mochila_jogador[i].posicao].id_evolui;

            mochila_jogador[i].posicao++;
        }
    }
}

void anda_jogador()
{
    if(modo_de_jogo==1)
        return;
    if(!andando && estado_boneco>0) //Se o boneco estiver parado, ativa a animação de movimento
    {
        andando = 1;
        boneco->start_timer(VELOCIDADE_ANIMACAO);
    }
    if(estado_boneco==0)
    {
        andando = 0;
        boneco->stop_timer();
    }
    switch (estado_boneco)
    {
        case 83:
            y_1+=VELOCIDADE_PERSONAGEM;
            boneco->set_orientation("down");
            checa_posicao_valida(1);
            break;
        case 87:
            y_1-=VELOCIDADE_PERSONAGEM;
            boneco->set_orientation("up");
            checa_posicao_valida(2);
            break;
        case 65:
            x_1-=VELOCIDADE_PERSONAGEM;
            boneco->set_orientation("left");
            checa_posicao_valida(3);
            break;
        case 68:
            x_1+=VELOCIDADE_PERSONAGEM;
            boneco->set_orientation("right");
            checa_posicao_valida(4);
            break;
    }
    boneco->setPos(x_1,y_1);
}


void checa_posicao_valida(int a)
{
    cor_chao.setRgb(mapa_obstaculos.pixel(x_1,y_1));
    //qDebug()<<cor_chao.value();
    while (cor_chao.value()==0) //Detecta parede
    {
        switch (a)
        {
            case 1:
            y_1-=VELOCIDADE_PERSONAGEM;
            break;
            case 2:
            y_1+=VELOCIDADE_PERSONAGEM;
            break;
            case 3:
            x_1+=VELOCIDADE_PERSONAGEM;
            break;
            case 4:
            x_1-=VELOCIDADE_PERSONAGEM;
            break;
        }
        cor_chao.setRgb(mapa_obstaculos.pixel(x_1,y_1));
        //qDebug()<<cor_chao.value();
    }
    while((y_1>660) || (y_1<0)){
        switch (a)
        {
            case 1:
            y_1-=VELOCIDADE_PERSONAGEM;
            break;
            case 2:
            y_1+=VELOCIDADE_PERSONAGEM;
            break;
        }
    }
}

void inicializa_mapa()
{
    QPixmap fundo;
    fundo.load(":/new/prefix1/recursos/sprites/mapas/petalburg_woods.png");
    cena->setBackgroundBrush(fundo);
    cena->addItem(boneco);
    cena->removeItem(pokemon_spr);
    cena->removeItem(pokemon_spr_2);
    cena->removeItem(pokemon_spr_3);
    cena->removeItem(pokemon_spr_4);
    cena->removeItem(pokemon_spr_5);
    boneco->setPos(200,200);
}

bool ta_na_hora()
{
    return rand()%100<(DIFICULDADE/5);
}

void modo_de_batalha()
{
    pokemon_selvagem.posicao = rand()%QTD_POKEMONS;
    modo_de_jogo = 1;
    QPixmap fundo;
    fundo.load(":/new/prefix1/recursos/sprites/battle/castle_2.png");
    cena->removeItem(boneco);
    cena->setBackgroundBrush(fundo);

    cena->addItem(pokemon_spr_4);
    pokemon_spr_4->setPos(168,500);

    cena->addItem(pokemon_spr_5);
    pokemon_spr_5->setPos(644,540);

    pokemon_spr_4->set_imagem_x(poke_cat[mochila_jogador[0].posicao].imagem_x);
    pokemon_spr_4->set_imagem_y(poke_cat[mochila_jogador[0].posicao].imagem_y);
    pokemon_spr_4->atualiza_imagem();

    pokemon_spr_5->set_imagem_x(poke_cat[pokemon_selvagem.posicao].imagem_x);
    pokemon_spr_5->set_imagem_y(poke_cat[pokemon_selvagem.posicao].imagem_y);
    pokemon_spr_5->atualiza_imagem();

    pokemon_selvagem.nivel = abs((rand()%2)==0 ? mochila_jogador[0].nivel+rand()%3 : mochila_jogador[0].nivel-rand()%2);


    mochila_jogador[0].hp = 10 + mochila_jogador[0].nivel*2;
    mochila_jogador[1].hp = 10 + mochila_jogador[1].nivel*2;
    pokemon_selvagem.hp = ((mochila_jogador[0].hp + mochila_jogador[1].hp)/3) + 10 + pokemon_selvagem.nivel*2;

    if(bonus_mapa=="")
    {
        int chance = rand()%18;
        bonus_mapa = tipos[chance];
        if(poke_cat[pokemon_selvagem.posicao].tipo==bonus_mapa)
            pokemon_selvagem.hp+=10;
        if(poke_cat[mochila_jogador[0].posicao].tipo==bonus_mapa)
            mochila_jogador[0].hp+=10;
        if(poke_cat[mochila_jogador[1].posicao].tipo==bonus_mapa)
            mochila_jogador[1].hp+=10;
    }

}


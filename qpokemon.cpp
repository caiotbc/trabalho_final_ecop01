#include "qpokemon.h"

QPokemon::QPokemon(QObject *parent) : QObject(parent)
{
    timer = new QTimer();
    //imagem_linha = 5;
    //imagem_coluna = 5;

    pixmap = new QPixmap(":/new/prefix1/recursos/sprites/pokemons/generation1.png"); //folha de sprites

    //tamanho de cada imagem
    largura = 63;
    altura = 63;

    //refresh rate da animação
    //timer->start(250);

    //connect(timer, &QTimer::timeout, this , &QPokemon::atualiza_imagem); //Conectar o timer na função de atualização
}

QRectF QPokemon::boundingRect() const
{
    return QRectF(-largura/2,-altura/2,largura,altura);
}

void QPokemon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-largura/2,-altura/2,*pixmap,imagem_coluna,imagem_linha,largura,altura);
}

void QPokemon::set_imagem_x(int x)
{
    imagem_linha = x;
}

void QPokemon::set_imagem_y(int y)
{
    imagem_coluna = y;
}

void QPokemon::atualiza_imagem()
{
   this->update(-largura/2,-altura/2,largura,altura);
}

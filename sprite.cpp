#include "sprite.h"

sprite::sprite(QObject *parent, float i_c) : QObject(parent)
{
    timer = new QTimer();
    imagem_linha = 0;
    imagem_coluna = i_c;

    pixmap = new QPixmap(":/new/prefix1/recursos/sprites/movement/male.png"); //folha de sprites

    //tamanho de cada imagem
    largura = 14;
    altura = 21;

    //refresh rate da animação
    timer->start(250);

    connect(timer, &QTimer::timeout, this , &sprite::atualiza_imagem); //Conectar o timer na função de atualização

}


void sprite::atualiza_imagem()
{
   imagem_linha += altura+1;
   if(imagem_linha >= 65)
   {
       imagem_linha = 0;
   }
   this->update(-largura/2,-altura/2,largura,altura);
}

QRectF sprite::boundingRect() const
{
    return QRectF(-largura/2,-altura/2,largura,altura);
}

void sprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-largura/2,-altura/2,*pixmap,imagem_coluna,imagem_linha,largura,altura);
}

void sprite::start_timer(int n)
{
    timer->start(n);
}

void sprite::stop_timer()
{
    timer->stop();
}

void sprite::set_orientation(QString s)
{
    if(s=="up")
        imagem_coluna=15;
    else if(s=="left")
        imagem_coluna=30;
    else if(s=="down")
        imagem_coluna=0;
    else if(s=="right")
        imagem_coluna=47;
}

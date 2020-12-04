#ifndef QPOKEMON_H
#define QPOKEMON_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>
#include <QtDebug>

class QPokemon : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit QPokemon(QObject *parent = nullptr);

    QTimer *timer;
    QPixmap *pixmap;    //Mapa de bits

    float imagem_linha,imagem_coluna; //Variáveis para iterar pelo mapa de bits

    float largura, altura; //Tamanho de cada sprite

    //funções para pintar os sprites
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void set_imagem_x(int x);
    void set_imagem_y(int y);

    void atualiza_imagem();

};

#endif // QPOKEMON_H

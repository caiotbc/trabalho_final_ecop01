#ifndef SPRITE_H
#define SPRITE_H

#include <QObject>
#include <QGraphicsItem>
#include <QTimer>
#include <QPixmap>
#include <QPainter>
#include <QKeyEvent>

class sprite : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit sprite(QObject *parent = nullptr, float i_c = 0);

    QTimer *timer;
    QPixmap *pixmap;    //Mapa de bits

    float imagem_linha,imagem_coluna; //Variáveis para iterar pelo mapa de bits

    float largura, altura; //Tamanho de cada sprite

    //funções para pintar os sprites
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void start_timer(int n);
    void stop_timer();
    void set_orientation(QString s);
signals:

public slots:
    void atualiza_imagem(); //Função da animação

};

#endif // SPRITE_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QGraphicsItem>
#include <QRectF>
#include <QDesktopWidget>
#include <QDebug>
#include <QKeyEvent>
#include <QGraphicsScene>
#include "sprite.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
private:
    Ui::MainWindow *ui;
    QGraphicsScene *cena;

    sprite *Brendan;
    sprite *Banana;

    float cena_x,cena_y,cena_largura,cena_altura;
    int x_1 = 0;
    int y_1 = 0;

    int tecla, tecla_anteior, pressionada;
};
#endif // MAINWINDOW_H

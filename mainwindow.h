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
#include "pokemons.h"
#include "qpokemon.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void set_scene(QGraphicsScene &a);
    void keyPressEvent(QKeyEvent *e);
    void keyReleaseEvent(QKeyEvent *e);
protected:

public slots:
    void temporizador();

private:
    Ui::MainWindow *ui;
    int x_1 = 0;
    int y_1 = 0;

    int tecla, tecla_anteior, pressionada;
    QTimer *temporizador_principal;
};
#endif // MAINWINDOW_H

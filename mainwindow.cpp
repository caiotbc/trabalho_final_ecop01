#include "mainwindow.h"
#include "ui_mainwindow.h"

extern void teste_referencia(QGraphicsScene &p, sprite &b);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pokebola->setGeometry(0,0,17,18);

    //QRect Desktop = QGUIApplication::screens();
    cena_x = 0;
    cena_y = 0;

    cena_largura =768;
    cena_altura = 700;

    pressionada = 0;

    cena = new QGraphicsScene(cena_x,cena_y,cena_largura,cena_altura);

    QPixmap fundo(":/new/prefix1/recursos/sprites/mapas/petalburg_woods.png");

    ui->graphicsView->setScene(cena);

    Brendan = new sprite(this,0);
    Banana = new sprite(this,30);

    cena->setBackgroundBrush(fundo);
    cena->addItem(Brendan);
    teste_referencia(*cena,*Banana);
    Brendan->setPos(200,200);


    //Brendan->stop_timer();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->isAutoRepeat() && !pressionada)
    {
        qDebug()<<"tecla pressionada";
        Brendan->start_timer(250);
        pressionada=1;
    }
    else if(!e->isAutoRepeat())
    {
        Brendan->stop_timer();
        pressionada=0;
    }
    tecla = e->key();
    qDebug()<<tecla;
    switch (tecla)
    {
        case 83:
            y_1+=5;
            Brendan->set_orientation("down");
            break;
        case 87:
            y_1-=5;
            Brendan->set_orientation("up");
            break;
        case 65:
            x_1-=5;
            Brendan->set_orientation("left");
            break;
        case 68:
            x_1+=5;
            Brendan->set_orientation("right");
            break;
    }
    //ui->pokebola->setGeometry(x_1,y_1,17,18);
    Brendan->setPos(x_1,y_1);
    tecla_anteior = tecla;
}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{
    if(!e->isAutoRepeat())
        qDebug() <<"Tecla solta";
}


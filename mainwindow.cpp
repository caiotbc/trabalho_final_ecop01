#include "mainwindow.h"
#include "ui_mainwindow.h"

extern void loop_principal();
extern int estado_boneco;

void MainWindow::set_scene(QGraphicsScene &a)
{
    ui->graphicsView->setScene(&a);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    temporizador_principal = new QTimer(this); //temporizador do loop principal
    connect(temporizador_principal, SIGNAL(timeout()), this, SLOT(temporizador()));
    temporizador_principal->start(10);
}

void MainWindow::temporizador()
{
    loop_principal();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e) //Tecla pressionada
{
    estado_boneco = e->key();
}

void MainWindow::keyReleaseEvent(QKeyEvent *e) //Tecla solta
{
    if(!e->isAutoRepeat())
    {
        estado_boneco=0;
    }
}


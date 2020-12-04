#include "mainwindow.h"
#include "ui_mainwindow.h"

extern void loop_principal();
extern int estado_boneco;
extern int poke_atual;
extern int evolucao_poke;
extern int mapa_ativado;
extern pokedex mochila_jogador[2];
extern pokemon_catalogo_t poke_cat[25];
extern QPokemon *pokemon_spr_2;
extern QPokemon *pokemon_spr_3;

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
    ui->nome_poke  ->setStyleSheet("color : rgb(255, 255, 255);\nfont: 14pt \"Pokemon Generation 1\";");
    ui->nome_poke_2->setStyleSheet("color : rgb(255, 255, 255);\nfont: 14pt \"Pokemon Generation 1\";");
    ui->nome_poke_3->setStyleSheet("color : rgb(255, 255, 255);\nfont: 14pt \"Pokemon Generation 1\";");
    ui->nome_poke_4->setStyleSheet("color : rgb(255, 255, 255);\nfont: 14pt \"Pokemon Generation 1\";");
    ui->nome_poke_5->setStyleSheet("color : rgb(255, 255, 255);\nfont: 14pt \"Pokemon Generation 1\";");
    ui->nome_poke_6->setStyleSheet("color : rgb(255, 255, 255);\nfont: 14pt \"Pokemon Generation 1\";");
}

void MainWindow::temporizador()
{
    loop_principal();
    ui->nome_poke->setText(poke_cat[poke_atual].nome);
    ui->nome_poke_2->setText(poke_cat[poke_atual].tipo);
    ui->nome_poke_3->setText(QString::number(poke_cat[poke_atual].geracao));
    ui->nome_poke_4->setText(QString::number(evolucao_poke));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e) //Tecla pressionada
{
    estado_boneco = e->key();
    if(e->key()==76)
    {
        poke_atual++;
    }
    else if(e->key()==74)
    {
        poke_atual--;
    }
    else if(e->key()==89)
    {
        ui->nome_poke_5->setText(poke_cat[poke_atual].nome + "\n" + poke_cat[poke_atual].tipo);
        mochila_jogador[0].posicao = poke_atual;
        mochila_jogador[0].id = poke_cat[poke_atual].id;
        pokemon_spr_2->set_imagem_x(poke_cat[mochila_jogador[0].posicao].imagem_x);
        pokemon_spr_2->set_imagem_y(poke_cat[mochila_jogador[0].posicao].imagem_y);
        pokemon_spr_2->atualiza_imagem();
    }
    else if(e->key()==72)
    {
        ui->nome_poke_6->setText(poke_cat[poke_atual].nome + "\n" + poke_cat[poke_atual].tipo);
        mochila_jogador[1].posicao = poke_atual;
        mochila_jogador[1].id = poke_cat[poke_atual].id;
        pokemon_spr_3->set_imagem_x(poke_cat[mochila_jogador[1].posicao].imagem_x);
        pokemon_spr_3->set_imagem_y(poke_cat[mochila_jogador[1].posicao].imagem_y);
        pokemon_spr_3->atualiza_imagem();
    }
    else if(e->key()==84 && mochila_jogador[0].id>0 && mochila_jogador[1].id>0)
    {
        mapa_ativado=1;
        ui->nome_poke->setVisible(0);
        ui->nome_poke_2->setVisible(0);
        ui->nome_poke_3->setVisible(0);
        ui->nome_poke_4->setVisible(0);
        ui->nome_poke_5->setVisible(0);
        ui->nome_poke_6->setVisible(0);
    }

}

void MainWindow::keyReleaseEvent(QKeyEvent *e) //Tecla solta
{
    if(!e->isAutoRepeat())
    {
        estado_boneco=0;
    }
}


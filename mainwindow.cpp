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
extern QPokemon *pokemon_spr;
extern QPokemon *pokemon_spr_3;
extern QPokemon *pokemon_spr_4;
extern QPokemon *pokemon_spr_5;

extern int modo_de_jogo;
extern pokedex pokemon_selvagem;
int pokemon_lutando = 0;

extern QString bonus_mapa;

void inicializa_mapa();

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
    ui->nome_poke_7->setStyleSheet("color : rgb(0, 0, 0);\nfont: 12pt \"Pokemon Generation 1\";");
    ui->nome_poke_8->setStyleSheet("color : rgb(0, 0, 0);\nfont: 12pt \"Pokemon Generation 1\";");
    ui->nome_poke_9->setStyleSheet("color : rgb(0, 0, 0);\nfont: 9pt \"Pokemon Generation 1\";");
    ui->health_1->setStyleSheet("border-image: url(:/new/prefix1/recursos/sprites/battle/vida.png);");
    ui->health_2->setStyleSheet("border-image: url(:/new/prefix1/recursos/sprites/battle/vida.png);");
    ui->health_1->setGeometry(160,405,100,40);
    ui->health_2->setGeometry(160,405,100,40);
    ui->health_1->setVisible(0);
    ui->health_2->setVisible(0);
    ui->nome_poke_7->setVisible(0);
    ui->nome_poke_8->setVisible(0);
    ui->nome_poke_9->setVisible(0);
    ui->victory->setVisible(0);
}

void MainWindow::temporizador()
{
    loop_principal();
    ui->nome_poke->setText(poke_cat[poke_atual].nome);
    ui->nome_poke_2->setText(poke_cat[poke_atual].tipo);
    ui->nome_poke_3->setText(QString::number(poke_cat[poke_atual].geracao));
    ui->nome_poke_4->setText(QString::number(evolucao_poke));
    if(modo_de_jogo==1)
    {
        ui->health_1->setVisible(1);
        ui->health_2->setVisible(1);

        int vida_total = 10 + mochila_jogador[pokemon_lutando].nivel*2 + (poke_cat[mochila_jogador[pokemon_lutando].posicao].tipo==bonus_mapa ? 10 : 0);
        int vida_total_2 = 10 + pokemon_selvagem.nivel*2 + (poke_cat[pokemon_selvagem.posicao].tipo==bonus_mapa ? 10 : 0);

        ui->health_1->setGeometry(177-40*((double)mochila_jogador[pokemon_lutando].hp/(double)vida_total),405,100*((double)mochila_jogador[pokemon_lutando].hp/(double)vida_total),40);
        ui->health_2->setGeometry(637-40*((double)pokemon_selvagem.hp/(double)vida_total_2),446,100*((double)pokemon_selvagem.hp/(double)vida_total_2),40);
        ui->nome_poke_7->setVisible(1);
        ui->nome_poke_8->setVisible(1);
        ui->nome_poke_9->setVisible(1);

        ui->nome_poke_9->setText("Bonus de mapa para o tipo " + bonus_mapa);
        QString texto_batalha, texto_oponente;
        texto_batalha = "Hora da batalha! Aperte G para atacar\n";
        texto_batalha+="\nSeu Pokemon: \n" + poke_cat[mochila_jogador[pokemon_lutando].posicao].nome;
        texto_batalha+=" (" + poke_cat[mochila_jogador[pokemon_lutando].posicao].tipo + ")";
        texto_batalha+="\nHP:" + QString::number(mochila_jogador[pokemon_lutando].hp);
        texto_batalha+="\nNivel: " + QString::number(mochila_jogador[pokemon_lutando].nivel+1);

        texto_oponente+="\n\nPokemon do oponente: \n" + poke_cat[pokemon_selvagem.posicao].nome;
        texto_oponente+=" (" + poke_cat[pokemon_selvagem.posicao].tipo + ")";
        texto_oponente+="\nHP:" + QString::number(pokemon_selvagem.hp);
        texto_oponente+="\nNivel: " + QString::number(pokemon_selvagem.nivel+1);

        ui->nome_poke_7->setText(texto_batalha);
        ui->nome_poke_8->setText(texto_oponente);

        if(estado_boneco==65 && pokemon_selvagem.hp<=0)
        {
            modo_de_jogo=0;
            inicializa_mapa();
            ui->nome_poke_7->setVisible(0);
            ui->nome_poke_8->setVisible(0);

            ui->health_1->setVisible(0);
            ui->health_2->setVisible(0);
            ui->victory->setVisible(0);

            if(rand()%2==0){
                mochila_jogador[pokemon_lutando].nivel++;
            }
            if(rand()%2==0){
                mochila_jogador[pokemon_lutando+1].nivel++;
            }

        }
        else if(pokemon_selvagem.hp<=0)
        {
            texto_batalha = "PARABENS, VOCE VENCEU!\nAperte A para continuar";
            texto_oponente = "";
            ui->nome_poke_7->setText(texto_batalha);
            ui->nome_poke_8->setText(texto_oponente);
            ui->nome_poke_9->setVisible(0);
            pokemon_lutando = 0;
        }

        if(estado_boneco==65 && mochila_jogador[1].hp<=0)
        {
            modo_de_jogo=0;
            inicializa_mapa();
            ui->nome_poke_7->setVisible(0);
            ui->nome_poke_8->setVisible(0);
            ui->nome_poke_9->setVisible(0);
            ui->health_1->setVisible(0);
            ui->health_2->setVisible(0);
            ui->victory->setVisible(0);

            if(pokemon_lutando==0){
                mochila_jogador[pokemon_lutando].nivel++;
                mochila_jogador[pokemon_lutando+1].nivel++;
            }else{
                mochila_jogador[pokemon_lutando].nivel++;
                mochila_jogador[pokemon_lutando+1].nivel++;
            }
        }
        else if(mochila_jogador[1].hp<=0)
        {
            texto_batalha = "Que pena, voce perdeu!\nAperte A para continuar";
            texto_oponente = "";
            ui->nome_poke_7->setText(texto_batalha);
            ui->nome_poke_8->setText(texto_oponente);
            ui->nome_poke_9->setVisible(0);
            pokemon_lutando = 0;
        }

    }

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
    else if(e->key()==84 && mochila_jogador[0].id>0 && mochila_jogador[1].id>0 && modo_de_jogo==0)
    {
        mapa_ativado=1;
        ui->nome_poke->setVisible(0);
        ui->nome_poke_2->setVisible(0);
        ui->nome_poke_3->setVisible(0);
        ui->nome_poke_4->setVisible(0);
        ui->nome_poke_5->setVisible(0);
        ui->nome_poke_6->setVisible(0);
    }
    if(modo_de_jogo && e->key()==71)
    {
        calcula_danos();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *e) //Tecla solta
{
    if(!e->isAutoRepeat())
    {
        estado_boneco=0;
    }
}

void MainWindow::calcula_danos()
{
    pokemon_selvagem.hp-=mochila_jogador[pokemon_lutando].nivel+1;
    mochila_jogador[pokemon_lutando].hp-=pokemon_selvagem.nivel+1;

    if(pokemon_selvagem.hp<=0)
    {
        ui->victory->setVisible(1);
        ui->victory->setStyleSheet("border-image: url(:/new/prefix1/recursos/sprites/battle/win.png);");
    }

    if(mochila_jogador[0].hp<=0)
    {
        pokemon_lutando = 1;
        pokemon_spr_4->set_imagem_x(poke_cat[mochila_jogador[pokemon_lutando].posicao].imagem_x);
        pokemon_spr_4->set_imagem_y(poke_cat[mochila_jogador[pokemon_lutando].posicao].imagem_y);
        pokemon_spr_4->atualiza_imagem();
    }

    if(mochila_jogador[1].hp<=0)
    {
        ui->victory->setVisible(1);
        ui->victory->setStyleSheet("border-image: url(:/new/prefix1/recursos/sprites/battle/lose.png);");
    }
}

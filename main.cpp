#include "main.h"
#define VELOCIDADE_ANIMACAO 100
#define VELOCIDADE_PERSONAGEM 1

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    estado_boneco = 0;
    andando = 0;
    x_1 = 200;
    y_1 = 200;

    int cena_x = 0;
    int cena_y = 0;

    int cena_largura =768;
    int cena_altura = 700;

    QGraphicsScene *cena;
    cena = new QGraphicsScene(cena_x,cena_y,cena_largura,cena_altura);

    QPixmap fundo(":/new/prefix1/recursos/sprites/mapas/petalburg_woods.png"); //background

    w.set_scene(*cena); //configura a cena

    boneco = new sprite(&w,0);
    cena->setBackgroundBrush(fundo);
    cena->addItem(boneco);
    boneco->setPos(200,200);

    abre_arquivo(":/new/prefix1/recursos/sprites/mapas/petalburg_woods.dat");
    imprime_matriz(4,4);
    return a.exec();
}

void imprime_matriz(int n, int m)
{
    for(int i =0 ; i < n ; i++)
    {
        for(int j = 0; j < m ;j++)
        {
            qDebug("%d",mapa_petalburg_obstaculos[i][j]);
        }
    }
}

void abre_arquivo(std::string a)
{
    QFile arquivo(":/new/prefix1/recursos/sprites/mapas/petalburg_woods.dat");
    //arquivo.open(QIODevice::ReadWrite);

    if(arquivo.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&arquivo);
        int n=0,m=0;
        QString line = in.readLine();
        n = line.toInt();
        line = in.readLine();
        m = line.toInt();
        qDebug()<<n<<m;

        for(int i = 0 ; i < n ; i++)
        {
            line = in.readLine();
            for(int j = 0 ; j < m ; j++)
            {
                mapa_petalburg_obstaculos[i][j] = line[j].digitValue();
                //qDebug()<<line[j];
            }
            //qDebug()<<line;
        }
    }
    else
    {
        qDebug()<<"Arquivo nao abriu";
    }
    arquivo.close();
}

void loop_principal()
{
    anda_boneco();
}

void anda_boneco()
{
    if(!andando && estado_boneco>0) //Se o boneco estiver parado, ativa a animação de movimento
    {
        andando = 1;
        boneco->start_timer(VELOCIDADE_ANIMACAO);
    }
    if(estado_boneco==0)
    {
        andando = 0;
        boneco->stop_timer();
    }
    //qDebug()<<estado_boneco;
    switch (estado_boneco)
    {
        case 83:
            y_1+=VELOCIDADE_PERSONAGEM;
            boneco->set_orientation("down");
            break;
        case 87:
            y_1-=VELOCIDADE_PERSONAGEM;
            boneco->set_orientation("up");
            break;
        case 65:
            x_1-=VELOCIDADE_PERSONAGEM;
            boneco->set_orientation("left");
            break;
        case 68:
            x_1+=VELOCIDADE_PERSONAGEM;
            boneco->set_orientation("right");
            break;
    }
    boneco->setPos(x_1,y_1);
}

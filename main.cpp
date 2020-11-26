#include "main.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    variavel = 0;
    teste = new sprite(&w, 30);

    return a.exec();
}

void teste_referencia(QGraphicsScene &p, sprite &b)
{
    p.addItem(&b);
    b.setPos(300,300);
}

#include "pictureshrinkerwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PictureShrinkerWidget w;
    w.show();

    return a.exec();
}

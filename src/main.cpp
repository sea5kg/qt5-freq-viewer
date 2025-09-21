#include "qt5freqviewer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Qt5FreqViewer w;
    w.show();
    return a.exec();
}

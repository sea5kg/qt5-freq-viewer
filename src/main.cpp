#include <QGuiApplication>
#include <QQuickView>
#include <QtQml>
#include <QUrl>

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQuickView view;
    view.setSource(QUrl("qrc:/res/qt5freqviewer.qml")); // Assuming main.qml is in your Qt Resources
    view.show();

    return app.exec();
}
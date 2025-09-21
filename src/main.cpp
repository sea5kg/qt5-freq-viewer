#include <QGuiApplication>
#include <QQuickView>
#include <QtQml>
#include <QUrl>

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qml/qt5freqviewer.qml")); // Assuming main.qml is in a Qt resource file
    // Alternatively, if main.qml is in the same directory as main.cpp:
    // const QUrl url(QStringLiteral("main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();

    // QGuiApplication app(argc, argv);

    // QQuickView view;
    // view.setSource(QUrl::fromLocalFile("qml/qt5freqviewer.qml"));
    // //view.setSource(QUrl("qrc:/qml/qt5freqviewer.qml")); // Assuming main.qml is in your Qt Resources
    // view.show();

    // return app.exec();
}
/*
MIT License

Copyright (c) 2025 Evgenii Sopov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <QGuiApplication>
#include <QApplication>
#include <QFontDatabase>
#include <QQuickView>
#include <QtQml>
#include <QMessageBox>
#include <QUrl>
#include <iostream>

#include "mytextcontroller.h"
#include "all_controllers.h"
#include "canvascontroller.h"
#include "datareader.h"

void InstallDefaultFont()
{
  QString resourcePath = ":/fonts/CruNattapong-XyOd.ttf";
  qint32 fontId = QFontDatabase::addApplicationFont(resourcePath);
  if (fontId != -1) {
    QStringList fontList = QFontDatabase::applicationFontFamilies(fontId);
    QString family = fontList.first();
    std::cout << "Applied custom font: " << family.toStdString() << std::endl;
    QFont font(family, 18);
    QGuiApplication::setFont(font);
  }
}



int main(int argc, char *argv[]) {
  // QGuiApplication app(argc, argv);
  // Don't use a Gui application because will be crash on FileDialog open
  QApplication app(argc, argv);

  InstallDefaultFont();

  QQmlApplicationEngine engine;

  // Expose to QML
  for (const auto& pair : *g_pControllers) { // 'pair' will be a const reference to std::pair<const std::string, int>
    engine.rootContext()->setContextProperty(QString::fromStdString(pair.first), pair.second);
  }

  if (argc > 1) {
    QString sFilePath(argv[1]);
    std::cout << sFilePath.toStdString() << std::endl;
    DataReader reader;
    if (!reader.tryRead(sFilePath)) {
      QMessageBox msgBox;
      msgBox.setIcon(QMessageBox::Critical);
      msgBox.setInformativeText(reader.getErrorMessage());
      msgBox.setWindowTitle("Error");
      msgBox.setStandardButtons(QMessageBox::Ok);
      msgBox.exec();
      return -1;
    }
    auto *canvas = findController<CanvasController>();
    canvas->applyFromReader(reader);
  }

  // view.setSource(QUrl::fromLocalFile("qml/main.qml"));
  const QUrl url(QStringLiteral("qml/main.qml")); // Assuming main.qml is in a Qt resource file

  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                   &app, [url](QObject *obj, const QUrl &objUrl) {
      if (!obj && url == objUrl)
          QCoreApplication::exit(-1);
  }, Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
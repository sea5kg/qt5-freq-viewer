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

#include "menucontroller.h"

#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include "all_controllers.h"
#include "canvascontroller.h"
#include "datareader.h"

REGISTRY_SINGLE_CONTROLLER(MenuController)

MenuController::MenuController(QObject *parent)
  : QObject(parent) {

}

void MenuController::performActionOpen() {
  QString filePath = QFileDialog::getOpenFileName(nullptr,
    tr("Open File With Frequirencies"), ".", tr("All Files (*.*)"));
  // std::cout << "Selected file: " << filePath.toStdString() << std::endl;

  DataReader reader;
  if (!reader.tryRead(filePath)) {
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setInformativeText(reader.getErrorMessage());
    msgBox.setWindowTitle("Error");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.exec();
    return;
  }

  auto *canvas = findController<CanvasController>();
  canvas->applyFromReader(reader);
  canvas->setRequestRepaint(true);
}

void MenuController::performActionClose() {
  QCoreApplication::exit(-1);
}

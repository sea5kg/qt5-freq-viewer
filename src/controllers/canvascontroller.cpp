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

#include "canvascontroller.h"

#include <QApplication>
#include <QFileDialog>
#include <iostream>
#include "all_controllers.h"

REGISTRY_SINGLE_CONTROLLER(CanvasController)

CanvasController::CanvasController(QObject *parent)
    : QObject(parent), m_bRequestRepaint(false) {
}

QString CanvasController::getHeader1() const {
    return m_sHeader1;
}

void CanvasController::setHeader1(const QString &header1) {
    if (m_sHeader1 == header1)
        return;
    m_sHeader1 = header1;
    emit header1Changed();
}

QString CanvasController::getHeader2() const {
    return m_sHeader2;
}

void CanvasController::setHeader2(const QString &header2) {
    if (m_sHeader2 == header2)
        return;
    m_sHeader2 = header2;
    emit header2Changed();
}

void CanvasController::onPaint() {
    std::cout << "CanvasController::onPaint()" << std::endl;
    // TODO
}

bool CanvasController::hasRequestRepaint() {
    return m_bRequestRepaint;
}

void CanvasController::setRequestRepaint(bool bValue) {
    m_bRequestRepaint = bValue;
}
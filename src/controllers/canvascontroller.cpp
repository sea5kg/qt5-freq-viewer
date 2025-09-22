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
#include <cmath>

#include "all_controllers.h"

REGISTRY_SINGLE_CONTROLLER(CanvasController)

CanvasController::CanvasController(QObject *parent)
    : QObject(parent), m_bRequestRepaint(false) {
}

void CanvasController::applyFromReader(const DataReader &reader) {
    setHeader1(reader.getHeader1());
    setHeader2(reader.getHeader2());

    // TODO: use a move semantic or shared ptr
    m_vFreq = reader.getFreq();
    m_vlFreq.clear();
    for (int i = 0; i < m_vFreq.size(); i++) {
        m_vlFreq.append(m_vFreq[i]);
    }

    m_vS11 = reader.getS11();
    m_vLogMag.clear();
    m_vlLogMag.clear();
    for (int  i = 0; i < m_vS11.size(); i++) {
        double real = m_vS11[i].first;
        double imag = m_vS11[i].second;
        double s11 = std::sqrt(real*real + imag*imag);
        // 𝑆11𝑙𝑜𝑔𝑚𝑎𝑔 = 20 * 𝑙𝑜𝑔10(|𝑆11|)
        double y = 20 * std::log10(std::fabs(s11));
        m_vLogMag.push_back(y);
        m_vlLogMag.append(y);
    }
    m_bRequestRepaint = true;
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

QVariantList CanvasController::getValuesX(int width, int height) {
    // TODO optimization for big lengths
    // std::cout << "getValuesX " << width << " " << height << std::endl;
    return m_vlFreq;
}

QVariantList CanvasController::getValuesY(int width, int height) {
    // TODO optimization for big lengths
    // std::cout << "getValuesX " << width << " " << height << std::endl;
    return m_vlLogMag;
}

bool CanvasController::hasRequestRepaint() {
    return m_bRequestRepaint;
}

void CanvasController::setRequestRepaint(bool bValue) {
    m_bRequestRepaint = bValue;
}

// QArray<double> get

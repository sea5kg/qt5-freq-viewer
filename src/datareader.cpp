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

#include "datareader.h"

#include <QFile>
#include <QTextStream>
#include <iostream>

bool DataReader::tryRead(const QString &sFilePath, QString &sErrorMessage) {
    header1 = "";
    header2 = "";
    m_vFreq.clear();
    m_vS11.clear();

    QFile file(sFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        sErrorMessage = "Error opening file:" + file.errorString();
        return false;
    }

    QTextStream in(&file);
    QString sLine;

    int nLineNumber = 0;
    while (!in.atEnd()) {
        sLine = in.readLine(); // Read one line at a time
        nLineNumber++;
        sLine = sLine.trimmed();
        if (sLine == "") {
            continue;
        }
        if (sLine.startsWith("#")) {
            header1 += sLine + "\n";
            // std::cout << "title: " << line.toStdString() << std::endl;
        } else if (sLine.startsWith("!")) {
            header2 += sLine + "\n";
            // std::cout << "title2: " << line.toStdString() << std::endl;
        } else if (sLine[0] >= '0' && sLine[0] <= '9') {
            QStringList listNumbers = sLine.split(" ");
            if (listNumbers.size() != 3) {
                sErrorMessage = "Expexted 3 number at line " + QString::number(nLineNumber) + ": '" + sLine + "'";
                return false;
            }
            // TODO reserve lines
            bool ok;
            m_vFreq.push_back(listNumbers[0].toDouble(&ok));
            if (!ok) {
                sErrorMessage = "Expexted 0 item as number at line " + QString::number(nLineNumber) + ": '" + sLine + "'";
                return false;
            }

            double nS11Real = listNumbers[1].toDouble(&ok);
            if (!ok) {
                sErrorMessage = "Expexted 1 item as number at line " + QString::number(nLineNumber) + ": '" + sLine + "'";
                return false;
            }

            double nS11Imag = listNumbers[2].toDouble(&ok);
            if (!ok) {
                sErrorMessage = "Expexted 2 item as number at line " + QString::number(nLineNumber) + ": '" + sLine + "'";
                return false;
            }
            m_vS11.push_back(std::pair<double,double>(nS11Real, nS11Imag));
            std::cout << "    " << sLine.toStdString() << std::endl;
        } else {
            sErrorMessage = "Unexpected start character at line " + QString::number(nLineNumber) + ": '" + sLine + "'";
            return false;
        }
    }
    // file.close();
    return true;
}
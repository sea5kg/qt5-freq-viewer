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
#include "timeprofiler.h"

bool DataReader::tryRead(const QString &sFilePath) {

  // TimeProfiler tp("DataReader::tryRead");
  m_sFilePath = sFilePath;
  m_sHeader1 = "";
  m_sHeader2 = "";
  m_sErrorMessage = "";
  m_vFreq.clear();
  m_vS11.clear();

  QFile file(m_sFilePath);

  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    m_sErrorMessage = "Error opening file: '" + sFilePath + "'\nError: " + file.errorString();
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
      m_sHeader1 += sLine + "\n";
      // std::cout << "title: " << line.toStdString() << std::endl;
    } else if (sLine.startsWith("!")) {
      m_sHeader2 += sLine + "\n";
      // std::cout << "title2: " << line.toStdString() << std::endl;
    } else if (sLine[0] >= '0' && sLine[0] <= '9') {
      QStringList listNumbers = sLine.split(" ");
      if (listNumbers.size() != 3) {
        m_sErrorMessage = "Expexted 3 number at line " + QString::number(nLineNumber) + ": '" + sLine + "'";
        return false;
      }
      // TODO reserve lines
      bool ok;
      m_vFreq.push_back(listNumbers[0].toDouble(&ok));
      if (!ok) {
        m_sErrorMessage = "Expexted 0 item as number at line " + QString::number(nLineNumber) + ": '" + sLine + "'";
        return false;
      }

      double nS11Real = listNumbers[1].toDouble(&ok);
      if (!ok) {
        m_sErrorMessage = "Expexted 1 item as number at line " + QString::number(nLineNumber) + ": '" + sLine + "'";
        return false;
      }

      double nS11Imag = listNumbers[2].toDouble(&ok);
      if (!ok) {
        m_sErrorMessage = "Expexted 2 item as number at line " + QString::number(nLineNumber) + ": '" + sLine + "'";
        return false;
      }
      m_vS11.push_back(std::pair<double,double>(nS11Real, nS11Imag));
      // std::cout << "    " << sLine.toStdString() << std::endl;
    } else {
      m_sErrorMessage = "Unexpected start character at line " + QString::number(nLineNumber) + ": '" + sLine + "'";
      return false;
    }
  }
  // file.close();
  return true;
}


QString DataReader::getErrorMessage() {
  return m_sErrorMessage;
}

const QString &DataReader::getHeader1() const {
  return m_sHeader1;
}

const QString &DataReader::getHeader2() const {
  return m_sHeader2;
}

const std::vector<double> &DataReader::getFreq() const {
  return m_vFreq;
}

const std::vector<std::pair<double,double>> &DataReader::getS11() const {
  return m_vS11;
}
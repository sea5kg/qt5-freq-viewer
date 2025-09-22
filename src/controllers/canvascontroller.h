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

#pragma once

#include <QObject>

class CanvasController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString header1 READ getHeader1 WRITE setHeader1 NOTIFY header1Changed)
    Q_PROPERTY(QString header2 READ getHeader2 WRITE setHeader2 NOTIFY header2Changed)
    Q_PROPERTY(bool hasRequestRepaint READ hasRequestRepaint WRITE setRequestRepaint)

public:
    explicit CanvasController(QObject *parent = nullptr);

    QString getHeader1() const;
    void setHeader1(const QString &header1);

    QString getHeader2() const;
    void setHeader2(const QString &header2);

    bool hasRequestRepaint();
    void setRequestRepaint(bool bValue);

    Q_INVOKABLE void onPaint();

signals:
    void header1Changed();
    void header2Changed();

private:
    QString m_sHeader1;
    QString m_sHeader2;
    bool m_bRequestRepaint;
};


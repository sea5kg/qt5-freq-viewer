#ifndef QT5FREQVIEWER_H
#define QT5FREQVIEWER_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Qt5FreqViewer; }
QT_END_NAMESPACE

class Qt5FreqViewer : public QMainWindow
{
    Q_OBJECT

public:
    Qt5FreqViewer(QWidget *parent = nullptr);
    ~Qt5FreqViewer();

private:
    Ui::Qt5FreqViewer *ui;
};
#endif // QT5FREQVIEWER_H

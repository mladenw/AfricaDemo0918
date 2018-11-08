#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF8"));
    QApplication::setOverrideCursor(Qt::BlankCursor);

    MainWindow *w = new MainWindow("MainWindow", 640, 480, 0, 0);
    w->move((QApplication::desktop()->width() - w->width())/2,(QApplication::desktop()->height() - w->height())/2);
    w->show();

    return a.exec();
}

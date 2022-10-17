#include "mainwindow.h"
#include<QMessageBox>
#include <QApplication>
#include<QtDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();



    QFile res_file(":/advanced.qss");
        if(res_file.open(QIODevice::ReadOnly))
        {
            a.setStyleSheet(res_file.readAll());
            qDebug() << "qss file load succes";
        }
        res_file.close();
        QPalette pal(w.palette());
        pal.setColor(QPalette::Background, QColor(30, 30, 25));
        w.setAutoFillBackground(true);
        w.setPalette(pal);


    return a.exec();
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"mps.h"
#include"equation.h"
#include <QMainWindow>
#include<QStandardItemModel>
#include<QVector>
#include<QList>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QMessageBox>
#include"timeline.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Add_clicked();

    void on_minus_clicked();

    void on_change_clicked();

    void on_calculate_clicked();

    void on_equation_clicked();

private:

    void Import_Data();
    Ui::MainWindow *ui;
    equation *equationwindow;
    QVector<MPS> input;
    QVector<request> output;
    QStandardItemModel* model;
    QStandardItemModel* model_out;
    QSqlQuery *query, *query2,*query3;
    QSqlDatabase db;
    timeline process;

};
#endif // MAINWINDOW_H

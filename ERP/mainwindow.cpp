#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->calendar->setStyleSheet("QDateTimeEdit{border:1px ;border-image: url(:/new/prefix1/resource/dropbox_normal.png);}\
                                    QDateTimeEdit:hover{border:1px ;border-image: url(:/new/prefix1/resource/dropbox_press.png);}\
                                    QDateTimeEdit::down-arrow{image:url(:/new/prefix1/resource/droptime_normal.png);}\
                                    QDateTimeEdit::down-arrow:hover{image:url(:/new/prefix1/resource/droptime_press.png);}\
                                    QDateTimeEdit::drop-down{width:25px; border:0px solid red;\
                                    subcontrol-origin: padding;subcontrol-position: top right;}");

    model=new QStandardItemModel();
    model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("Product-Name")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("Number")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("Finish-Date")));
    ui->table->setModel(model);



    model_out=new QStandardItemModel();
    model_out->setHorizontalHeaderItem(0, new QStandardItem(QString::fromLocal8Bit("Way-to-Product")));
    model_out->setHorizontalHeaderItem(1, new QStandardItem(QString::fromLocal8Bit("PartNo")));
    model_out->setHorizontalHeaderItem(2, new QStandardItem(QString::fromLocal8Bit("Name")));
    model_out->setHorizontalHeaderItem(3, new QStandardItem(QString::fromLocal8Bit("Number")));
    model_out->setHorizontalHeaderItem(4, new QStandardItem(QString::fromLocal8Bit("ConfirmDate")));
    model_out->setHorizontalHeaderItem(5, new QStandardItem(QString::fromLocal8Bit("FinishDate")));
    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->output->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->output->setModel(model_out);

    db = QSqlDatabase::addDatabase("QODBC");
        db.setHostName("127.0.0.1");
        db.setPort(3306);
        db.setDatabaseName("mysql");
        db.setUserName("root");
        db.setPassword("root");
        bool ok = db.open();
        if (!ok){
            QMessageBox::information(this, "infor", "link failed");
        }
    Import_Data();

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_Add_clicked()
{
    QList<QStandardItem*> t;
    t.push_back(new QStandardItem(ui->selectItem->currentText()));
    t.push_back(new QStandardItem(QString::number(ui->spinBox->value())));
    t.push_back(new QStandardItem(ui->calendar->selectedDate().toString()));
    input.push_back(MPS(*(ui->selectItem->currentText().split("---").end()-1),ui->spinBox->value(),ui->calendar->selectedDate()));
    model->appendRow(t);
}

void MainWindow::on_minus_clicked()
{
    if(input.empty() || ui->table->selectionModel()->currentIndex().row()<0 ||ui->table->selectionModel()->currentIndex().row()>input.size()) return;
    input.erase(input.begin()+ui->table->selectionModel()->currentIndex().row());
    model->removeRow(ui->table->selectionModel()->currentIndex().row());
}



void MainWindow::on_change_clicked()
{
    if(input.empty() || ui->table->selectionModel()->currentIndex().row()<0 ||ui->table->selectionModel()->currentIndex().row()>input.size()) return;
    input[ui->table->selectionModel()->currentIndex().row()].Input(ui->selectItem->currentText(),ui->spinBox->value(),ui->calendar->selectedDate());
    model->setItem(ui->table->selectionModel()->currentIndex().row(),0,new QStandardItem(ui->selectItem->currentText()));
    model->setItem(ui->table->selectionModel()->currentIndex().row(),1,new QStandardItem(QString::number(ui->spinBox->value())));
    model->setItem(ui->table->selectionModel()->currentIndex().row(),2,new QStandardItem(ui->calendar->selectedDate().toString()));
}


void MainWindow::on_calculate_clicked()
{
    for(int i=0;i<input.size();i++){
        process.Insert_Request(input[i].Get_Name(),input[i].Get_Date(),input[i].Get_Number());
    }
    output=process.Calculate();
    for(int i=0;i<output.size();i++){
        QString way;
        if(process.Check_Part(output[i].Get_part()).Get_Way()==method::product)way="生产";
           else way="采购";
        model_out->setItem(i,0,new QStandardItem(way));
        model_out->setItem(i,1,new QStandardItem(output[i].Get_part()));
        model_out->setItem(i,2,new QStandardItem(process.Check_Part(output[i].Get_part()).Get_Name()));
        model_out->setItem(i,3,new QStandardItem(QString::number(output[i].Get_Num())));
        model_out->setItem(i,4,new QStandardItem(output[i].Get_Date().addDays(-output[i].Get_ahead()).toString()));
        model_out->setItem(i,5,new QStandardItem(output[i].Get_Date().toString()));
    }
}

void MainWindow::Import_Data()
{
    query=new QSqlQuery();
    query2=new QSqlQuery();
    query3=new QSqlQuery();
        QString partNo,name,unit,way;
        double lossrate;
        int beforedate,moveremain,purchaseremain;
        method mm;
        query->prepare("select partNo,name,unit,way,lossrate,beforedate from part");
        bool res = query->exec();
        if(!res){qDebug()<<query->lastQuery();}
        while(query->next()){
            partNo = query->value("partNo").toString();
            name = query->value("name").toString();
            unit = query->value("unit").toString();
            way = query->value("way").toString();
            lossrate = query->value("lossrate").toDouble();
            beforedate = query->value("beforedate").toInt();
            ui->selectItem->addItem(name+"---"+partNo);
            if(way=="采购"){
                mm=method::purchase;
                int move_date=0,before_date=0;
                query2->prepare("select movedate,beforedate from compose where compose.child_no=:partNo");
                query2->bindValue(":partNo",partNo);
                bool res = query2->exec();
                if(!res){qDebug()<<query2->lastQuery();}
                while(query2->next()){
                    move_date=query2->value("movedate").toInt();
                    before_date=query2->value("beforedate").toInt();
                }
                process.Insert_Part(partNo,name,unit,mm,lossrate,beforedate,
                                    QVector<detail>(1,detail("",0,move_date,before_date)));

            }else{
                mm=method::product;
                QString child_no;
                int num,movedate,before_date;
                query2->prepare("select child_no,num,movedate,beforedate from compose where compose.father_no=:partNo");
                query2->bindValue(":partNo",partNo);
                bool res = query2->exec();
                if(!res){qDebug()<<query2->lastQuery();}
                QVector<detail> temp;
                while(query2->next()){
                    child_no=query2->value("child_no").toString();
                    num=query2->value("num").toInt();
                    movedate=query2->value("movedate").toInt();
                    before_date=query2->value("beforedate").toInt();
                    temp.push_back(detail(child_no,num,movedate,before_date));
                }
                process.Insert_Part(partNo,name,unit,mm,lossrate,beforedate,temp);
            }
        }
        query3->prepare("select partNo,moveremain,purchaseremain from store");
        res = query3->exec();
        if(!res){qDebug()<<query3->lastQuery();}
        while(query3->next()){
            partNo = query3->value("partNo").toString();
            moveremain=query3->value("moveremain").toInt();
            purchaseremain=query3->value("purchaseremain").toInt();
            process.Add_Store(partNo,moveremain,purchaseremain);
        }
}


void MainWindow::on_equation_clicked()
{
    equationwindow=new equation();
    equationwindow->show();
}


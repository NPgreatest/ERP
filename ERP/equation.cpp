#include "equation.h"
#include "ui_equation.h"
equation::equation(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::equation)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QODBC");
        db.setHostName("127.0.0.1");
        db.setPort(3306);
        db.setDatabaseName("mysql");
        db.setUserName("root");
        db.setPassword("root");
        bool ok = db.open();
        if (ok){
            QMessageBox::information(this, "infor", "link success");
        }
        else {
            QMessageBox::information(this, "infor", "link failed");
        }
    query=new QSqlQuery();
    model=new QStandardItemModel();
    model->setHorizontalHeaderItem(0, new QStandardItem(QObject::tr("Number")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QObject::tr("Number-All")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QObject::tr("name")));
    Import_Data(0);

}

equation::~equation()
{
    delete ui;
}

void equation::Import_Data(bool flag)
{
    int no,no_p,i=0;
    QString name;
    QString check;
    if(flag)query->prepare("select no,no_p,name from debt");else query->prepare("select no,no_p,name from property");
        bool res = query->exec();
        if(!res){qDebug()<<query->lastQuery();}
        while(query->next()){
            no=query->value("no").toInt();
            no_p=query->value("no_p").toInt();
            name=query->value("name").toString();
            model->setItem(i,0,new QStandardItem(QString::number(no)));
            model->setItem(i,1,new QStandardItem(QString::number(no_p)));
            model->setItem(i,2,new QStandardItem(name));
            i++;
        }
    ui->input->setModel(model);

}

void equation::on_comboBox_currentIndexChanged(int index)
{
    switch (index) {
    case 0:Import_Data(0);break;
    case 1:Import_Data(1);break;
    default:break;
    }
}


void equation::on_pushButton_clicked()
{
    ui->output->clear();
    QItemSelectionModel *selections =  ui->input->selectionModel();
    QModelIndexList selected = selections->selectedIndexes();
    QSet <int> rowSet;
    QString ans,t;
    int i=0;
    foreach (QModelIndex index, selected) {
        rowSet.insert(index.row());
        i++;
    }

    if(ui->comboBox->currentIndex()==1){
        t.clear();
        foreach (int value, rowSet){
            ans.clear();
            ans+=model->index(value,2).data().toString()+" = ";
            query->clear();
            query->prepare("select d2.name name from debt d1,debt d2 where d2.no_p=d1.no and d1.no=:number");
            query->bindValue(":number",QString::number(value+1));
            bool res = query->exec();
            if(!res){qDebug()<<query->lastQuery();}
            while(query->next()){
                t=query->value("name").toString();
                qDebug()<<t;
                ans+=" "+t+" + ";
            }
            ans=ans.left(ans.size()-2);
           ui->output->addItem(ans);
        }
    }else{
        t.clear();
        foreach (int value, rowSet){
            ans.clear();
            ans+=model->index(value,2).data().toString()+" = ";
            query->clear();
            query->prepare("select d2.name name from property d1,property d2 where d2.no_p=d1.no and d1.no=:number");
            query->bindValue(":number",QString::number(value+1));
            bool res = query->exec();
            if(!res){qDebug()<<query->lastQuery();}
            while(query->next()){
                t=query->value("name").toString();
                ans+=" "+t+" + ";
            }
            ans=ans.left(ans.size()-2);
           ui->output->addItem(ans);
        }
    }



}


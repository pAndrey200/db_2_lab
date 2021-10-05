#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQueryModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("fn1133_2017");
    db.setHostName("195.19.32.74");
    db.setUserName("student");
    db.setPassword("bmstu");
    if(!db.open())
         ui->label->setText( db.lastError().text() + "\n");
    else
        ui->label->setText("db open");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QSqlQuery msg(db);
    QString cmd = ui->textEdit->toPlainText();
    if(!msg.exec(cmd)){
        ui->label->setText( msg.lastError().text() + "\n");
    }
    else if(msg.isSelect()){
        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery(msg);
        ui->tableView->setModel(model);
    }
    else{
        ui->label->setText("Done!\n");
    }
}


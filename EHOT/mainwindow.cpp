#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQueryModel>
#include <QStringListModel>
#include <QVariant>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("d5phs5gq8jkfip");
    db.setHostName("ec2-52-30-81-192.eu-west-1.compute.amazonaws.com");
    db.setUserName("sirlxiuhxxnpbc");
    db.setPassword("af679de1dacd0a3e1a544b7a2a476036cad4ce5b8224af89eb2f160ddaf90213");
    if(!db.open())
         ui->label->setText( db.lastError().text() + "\n");
    else{
        ui->label->setText("db open");
        QStringListModel *listModel = new QStringListModel();
        //listModel->setHeaderData(0, Qt::Horizontal, QVariant::fromValue("header"));
        listModel->setStringList(db.tables());
        ui->listView->setModel(listModel);
    }
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
        ui->label->setText( msg.lastError().text());
    }
    else if(msg.isSelect()){
        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery(msg);
        ui->tableView->setModel(model);
        ui->label->setText("Done!\n");
    }
    else{
        ui->label->setText("Done!\n");
        QStringListModel *listModel = new QStringListModel();
        //listModel->setHeaderData(0, Qt::Horizontal, QVariant::fromValue("header"));
        listModel->setStringList(db.tables());
        ui->listView->setModel(listModel);
    }
}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QProcess"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionopen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("open file"), "E:\\Temp",  tr("pl0(*.pl0);;Allfile(*.*)"));
    ui->filename->setText(fileName);
    QFile pl0file(fileName);
    pl0file.open(QIODevice::ReadOnly|QIODevice::Text);
    ui->textEdit->setPlainText(pl0file.readAll());
    pl0file.close();
}


void MainWindow::on_actionrun_triggered()
{
    //QTextCodec *codec = QTextCodec::codecForName("GBK");
    //QProcess *pro=new QProcess(this);
    qDebug() << tr("-------------主程序运行中-----------");
    ////pro->execute("E:\\Temp\\comp.exe",{ui->filename->text()});
    QString test="E:\\Temp\\comp.exe "+ui->filename->text();
    system(test.toStdString().c_str());
//    {
//        qDebug() << tr("comp.exe启动成功");

//        //等待外部程序结束，如果在给定的时间内关闭外部程序，返回为真，超时返回false
//        if(pro->waitForFinished(10000))
//            qDebug() << tr("timer.exe程序被关闭");
//        else
//            qDebug() << tr("timer.exe程序在规定时间内没有被关闭");
//    }
    qDebug() << tr("------------主程序继续运行-----------");
    QFile code("E:\\Temp\\code.txt");
    code.open(QIODevice::ReadWrite|QIODevice::Text);
    ui->plainTextEdit->setPlainText(code.readAll());
    QFile table("E:\\Temp\\table.txt");
    table.open(QIODevice::ReadWrite|QIODevice::Text);
    ui->textEdit_3->setPlainText(table.readAll());
    QFile cifa("E:\\Temp\\cifa.txt");
    cifa.open(QIODevice::ReadWrite|QIODevice::Text);
    ui->textEdit_2->setPlainText(QString::fromLocal8Bit(cifa.readAll()));
    code.close();
    table.close();
    cifa.close();
}



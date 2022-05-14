#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mySocket = new QTcpSocket(this);
    connect(mySocket, SIGNAL(readyRead()),this, SLOT(readyRead()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->plainTextEdit->clear();
    mySocket->connectToHost("127.0.0.1", 1234);
    if(mySocket->waitForConnected(3000)){
        ui->plainTextEdit->appendPlainText("Connected to host successed 127.0.0.1 port 1234");
    }
    else{
        ui->plainTextEdit->appendPlainText("Connected to host failed 127.0.0.1 port 1234");
    }

}


void MainWindow::on_pushButton_2_clicked()
{
    if(mySocket->isOpen())
    {
        mySocket->close();
         ui->plainTextEdit->appendPlainText("Connected to host closed 127.0.0.1 port 1234");
    }

}


void MainWindow::on_lineEdit_returnPressed()
{
    char myChar[1024];
    if(mySocket->isWritable()){
        QString myStr = ui->lineEdit->text();
        memset(myChar, '\0', sizeof(myChar)+1);
        memcpy(myChar, ui->lineEdit->text().toUtf8(),myStr.length());
        mySocket->write(myChar);
        mySocket->waitForBytesWritten(1000);
        ui->plainTextEdit->appendPlainText("Client Send : "+ QString(myChar));
        ui->lineEdit->clear();
    }
}

void MainWindow::readyRead()
{
    QByteArray myByte;
    myByte = mySocket->readAll();
    ui->plainTextEdit->appendPlainText(QString(myByte));

}











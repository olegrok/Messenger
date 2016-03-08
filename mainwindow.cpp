#include <QString>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "authwindow.h"
#include "ui_authwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect(authwindow::, SIGNAL(authwindow::showMainWindow()), this, SLOT(slot_show()), Qt::UniqueConnection);
    auth = new authwindow;
    auth->show();
    connect(auth, &authwindow::showMainWindow, this, &MainWindow::show, Qt::UniqueConnection);
    connect(ui->SendButton, SIGNAL(clicked()), this, SLOT(on_SendButton_clicked()), Qt::UniqueConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_SendButton_clicked()
{
    QString msg = ui->MessageWindow->toPlainText();
    ui->MessageWindow->clear();
    if(!msg.isEmpty())
    ui->ChatWindow->appendPlainText("Me: " + msg);
}

void MainWindow::slot_show()
{
    this->show();
}

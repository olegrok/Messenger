#include "options.h"
#include "ui_options.h"

Options::Options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);
    //show();
    ui->design->addItems(QStyleFactory::keys());
    //ui->palette->addItem("");
}

Options::~Options()
{
    delete ui;
}

void Options::on_pushButton_clicked()
{
    qApp->setStyle(ui->design->currentText());
    qApp->restoreOverrideCursor();
}

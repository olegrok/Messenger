#include "options.h"
#include "ui_options.h"

Options::Options(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Options)
{
    ui->setupUi(this);
    //show();
    qDebug() << QStyleFactory::keys();
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
    QSettings settings;
    settings.setValue("user_interface/design", ui->design->currentText());
    qDebug() << settings.value("user_interface/design");
}

void Options::on_CloseButton_clicked()
{
    this->close();
}

void Options::on_UnloginButton_clicked()
{
    this->close();
    emit unloginProfile();
}

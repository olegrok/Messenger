#include "httpsettings.h"
#include "ui_httpsettings.h"

httpSettings::httpSettings(QString Url, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::httpSettings),
    URL(Url)
{
    ui->setupUi(this);
    if(!URL.isNull() && !URL.isEmpty())
        ui->httpLine->setText(URL);
    validator = new QRegExpValidator(reg);
    ui->httpLine->setValidator(validator);
}

httpSettings::~httpSettings()
{
    delete validator;
    delete ui;
}

QString httpSettings::getURL(){
    return URL;
}

void httpSettings::on_okButton_clicked()
{
    if(ui->httpLine->text().isEmpty()){
        setResult(1);
        URL = ui->httpLine->placeholderText();
        this->accept();
    }
    if(!ui->httpLine->text().contains(reg)){
        ui->status->setText(tr("Wrong entered data format"));
        return;
    }

    setResult(1);
    URL = ui->httpLine->text();
    this->accept();
}

void httpSettings::on_cancelButton_clicked()
{
    setResult(0);
    this->reject();
}

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
    emit unloginProfile();
    this->close();
}

void Options::on_setLang_clicked()
{
    QSettings settings;
    if(ui->langList->currentText() == tr("Russian")){
        translator.load("./langs/ru.qm");
        settings.setValue("user_interface/language/file", "./langs/ru.qm");
    }
    if(ui->langList->currentText() == tr("Ukrainian")){
        translator.load("./langs/ua.qm");
        settings.setValue("user_interface/language/file", "./langs/ua.qm");
    }
    if(ui->langList->currentText() == tr("English")){
        QVariant var = settings.value("user_interface/language/file");
        if(!var.isNull()){
            translator.load(var.toString());
            qApp->removeTranslator(&translator);
            settings.setValue("user_interface/language/file", 0);
            return;
        }
    }
        qApp->installTranslator(&translator);
    settings.setValue("user_interface/language/title", ui->langList->currentText());
}

void Options::changeEvent(QEvent *event){
    if(event->type() == QEvent::LanguageChange){
        ui->retranslateUi(this);
    }
}

void Options::loadLang(QString file){
    qDebug() << translator.load(file);
}

QTranslator* Options::getLang(){
    return &translator;
}

#ifndef HTTPSETTINGS_H
#define HTTPSETTINGS_H

#include <QDialog>
#include <QDebug>
#include <QValidator>

namespace Ui {
class httpSettings;
}

class httpSettings : public QDialog
{
    Q_OBJECT

public:
    explicit httpSettings(QString Url = 0, QWidget *parent = 0);
    ~httpSettings();
    QString getURL();
private slots:
    void on_okButton_clicked();
    void on_cancelButton_clicked();
private:
    Ui::httpSettings *ui;
    QString URL;
    QRegExp reg = QRegExp("(http|https)\\:\\/{2}([a-zA-Z0-9_.-]+)\\:([0-9]+)");
    QValidator * validator;
};

#endif // HTTPSETTINGS_H

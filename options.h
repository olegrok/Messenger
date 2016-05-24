#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>
#include <QStyleFactory>
#include <QDebug>
#include <QSettings>
#include <QTranslator>
#include <QStyle>

namespace Ui {
class Options;
}

class Options : public QDialog
{
    Q_OBJECT

public:
    explicit Options(QWidget *parent = 0);
    void loadLang(QString);
    QTranslator* getLang();
    ~Options();

private slots:
    void on_pushButton_clicked();
    void on_CloseButton_clicked();
    void on_UnloginButton_clicked();
    void on_setLang_clicked();
    void changeEvent(QEvent* event);
signals:
    void unloginProfile();

private:
    Ui::Options *ui;
    QStringList langList;
    QTranslator translator;
};

#endif // OPTIONS_H

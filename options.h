#ifndef OPTIONS_H
#define OPTIONS_H

#include <QDialog>
#include <QStyleFactory>
#include <QDebug>

namespace Ui {
class Options;
}

class Options : public QDialog
{
    Q_OBJECT

public:
    explicit Options(QWidget *parent = 0);
    ~Options();

private slots:
    void on_pushButton_clicked();
    void on_CloseButton_clicked();
    void on_UnloginButton_clicked();
signals:
    void unlogin(QString = 0);

private:
    Ui::Options *ui;
};

#endif // OPTIONS_H

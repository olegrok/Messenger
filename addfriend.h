#ifndef ADDFRIEND_H
#define ADDFRIEND_H
#include <QDialog>
#include "structsforrequests.h"

namespace Ui {
class AddFriend;
}

class AddFriend : public QDialog
{
    Q_OBJECT

public:
    explicit AddFriend(QWidget *parent = 0);
    ~AddFriend();
signals:
    void sendContact(contInfo);
private slots:
    void on_AddButton_clicked();

private:
    Ui::AddFriend *ui;
    contInfo CheckFriend(QString);
};

#endif // ADDFRIEND_H

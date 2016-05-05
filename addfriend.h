#ifndef ADDFRIEND_H
#define ADDFRIEND_H
#include <QDialog>
#include "structsforrequests.h"
#include "database.h"
#include "profile.h"

namespace Ui {
class AddFriend;
}

class AddFriend : public QDialog
{
    Q_OBJECT

public:
    explicit AddFriend(QWidget *parent = 0);
    ~AddFriend();
    void setUpProfile(Profile* acc);
    void setStatus(QString);
signals:
    void sendContact(contInfo);
private slots:
    void on_AddButton_clicked();

private:
    Ui::AddFriend *ui;
    Profile* account;
};

#endif // ADDFRIEND_H

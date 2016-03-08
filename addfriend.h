#ifndef ADDFRIEND_H
#define ADDFRIEND_H

#include <QDialog>

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
    void sendNick(QString);
private slots:
    void on_AddButton_clicked();

private:
    Ui::AddFriend *ui;
    bool CheckFriend(QString);
};

#endif // ADDFRIEND_H

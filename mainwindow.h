#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "authwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_SendButton_clicked();
    void slot_show();

private:
    Ui::MainWindow *ui;
    authwindow *auth;
};

#endif // MAINWINDOW_H

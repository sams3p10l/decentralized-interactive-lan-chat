#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "nicknamedialog.h"
#include <QStringList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    static void addUserToList(QString nick);
    static QStringList *activeUserList;

    ~MainWindow();

private slots:
    void on_sendButton_clicked();
    void refreshUserList();

private:
    Ui::MainWindow *ui;
    NicknameDialog *nickname;
};

#endif // MAINWINDOW_H

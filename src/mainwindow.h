#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include "nicknamedialog.h"
#include <QStringList>
#include "ui_mainwindow.h"

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
    static QString getMyNickname();

    ~MainWindow();

public slots:
    void appendMessage(const QString &from, const QString &message);

private slots:
    void on_sendButton_clicked();
    void refreshUserList();
    void enterPressed();
    void participantLeft(const QString &nick);
    void newParticipant(const QString &nick);

private:
    Ui::MainWindow *ui;
    NicknameDialog *nickname;
    static QString localNickname;
    Client client;

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // MAINWINDOW_H

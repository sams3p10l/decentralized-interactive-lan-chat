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
    static void AddUserToList(QString nick);
    static QStringList *ActiveUserList;
    static QString GetMyNickname();
    static Client* GetClientInstance();

    ~MainWindow();

public slots:
    void AppendMessage(const QString &from, const QString &message);
    static void SetMyNickname(const QString &myNick);

private slots:
    void on_sendButton_clicked();
    void RefreshUserList();
    void EnterPressed();
    void ParticipantLeft(const QString &nick);
    void NewParticipant(const QString &nick);

private:
    Ui::MainWindow *ui;
    static NicknameDialog *nickname;
    static QString LocalNickname;
    static Client *client;
    static QString LastMessage;

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // MAINWINDOW_H

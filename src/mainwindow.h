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
    QString localNickname;

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
};

#endif // MAINWINDOW_H

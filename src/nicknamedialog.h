#ifndef NICKNAMEDIALOG_H
#define NICKNAMEDIALOG_H

#include <QDialog>
#include "server.h"
#include "transmitter.h"

namespace Ui {
class NicknameDialog;
}

class NicknameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NicknameDialog(QWidget *parent = nullptr);
    ~NicknameDialog();
    QString GetNickname();
    static Transmitter* GetTransmitterInstance();

signals:
    void WindowClosed();

private slots:
    void on_cancelButton_clicked();
    void on_okButton_clicked();

private:
    Ui::NicknameDialog *ui;
    QPushButton *cancelButton;
    static Transmitter *transmitter;
    Client *client;
    Server *server;

};

#endif // NICKNAMEDIALOG_H

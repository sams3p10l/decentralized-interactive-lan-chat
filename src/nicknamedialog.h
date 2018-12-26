#ifndef NICKNAMEDIALOG_H
#define NICKNAMEDIALOG_H

#include <QDialog>

namespace Ui {
class NicknameDialog;
}

class NicknameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NicknameDialog(QWidget *parent = nullptr);
    ~NicknameDialog();
    QString getNickname();
    QStringList activeUserList;

signals:
    void windowClosed();
    void startBroadcasting();
    void startListening();

private slots:
    void on_cancelButton_clicked();
    void on_okButton_clicked();

private:
    Ui::NicknameDialog *ui;
    QPushButton *cancelButton;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // NICKNAMEDIALOG_H

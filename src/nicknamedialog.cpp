#include "nicknamedialog.h"
#include "ui_nicknamedialog.h"
#include "mainwindow.h"

NicknameDialog::NicknameDialog(QWidget *parent) : QDialog(parent), ui(new Ui::NicknameDialog)
{
    ui->setupUi(this);

}

NicknameDialog::~NicknameDialog()
{
    delete ui;
}

QString NicknameDialog::getNickname()
{
    return ui->nicknameEdit->text();
}

void NicknameDialog::on_cancelButton_clicked()
{
    QApplication::instance()->exit();
}

void NicknameDialog::on_okButton_clicked()
{
    MainWindow::addUserToList(getNickname());
    MainWindow::setMyNickname(getNickname());
    QWidget::close();
    emit windowClosed();
}

void NicknameDialog::closeEvent(QCloseEvent *event)
{
    emit startBroadcasting();
    emit startListening();
    event->accept();
}

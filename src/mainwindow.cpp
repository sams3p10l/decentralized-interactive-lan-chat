#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "nicknamedialog.h"

QStringList *MainWindow::activeUserList = new QStringList();

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{    
    nickname = new NicknameDialog(this);

    nickname->setModal(true);
    nickname->show(); //nickname dialog

    ui->setupUi(this);

    connect(nickname, SIGNAL(windowClosed()), this, SLOT(refreshUserList()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendButton_clicked()
{
    QString text = ui->messageEdit->toPlainText();
    ui->userList->append("test");
    ui->chatBox->append(text);
}

void MainWindow::addUserToList(QString nick)
{
    activeUserList->append(nick);
}

void MainWindow::refreshUserList()
{
    for (QString user : *activeUserList)
    {
        ui->userList->append(user);
    }
}

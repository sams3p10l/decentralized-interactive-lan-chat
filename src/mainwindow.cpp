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
    ui->messageEdit->setFocusPolicy(Qt::StrongFocus);

    connect(nickname, SIGNAL(windowClosed()), this, SLOT(refreshUserList()));
    connect(ui->messageEdit, SIGNAL(returnPressed()), this, SLOT(enterPressed()));
    /* override ono govno da baca returnpressed kad se klikne enter */

    localNickname = nickname->getNickname(); //get current user nickname

    //appendMessage("Pera", "kurcina");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendButton_clicked()
{
    QString text = ui->messageEdit->toPlainText();
    ui->userList->append("test"); //replace
    ui->chatBox->append(text); //replace
    ui->messageEdit->clear();
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

void MainWindow::appendMessage(const QString &from, const QString &message)
{
    if(from.isEmpty() || message.isEmpty())
        return;

    QString fullMsgFormat = '<' + from + '>' + ' ' + message + '\n';
    ui->chatBox->append(fullMsgFormat);

    QScrollBar *bar = ui->chatBox->verticalScrollBar();
    bar->setValue(bar->maximum());
}

void MainWindow::enterPressed()
{
    QString input = ui->messageEdit->toPlainText();

    if (input.isEmpty())
        return;

    appendMessage(localNickname, input);
    ui->messageEdit->clear();
}

void MainWindow::newParticipant(const QString &nick)
{
    if (nick.isEmpty())
        return;

    QColor color = ui->chatBox->textColor();
    ui->chatBox->setTextColor(Qt::gray);
    ui->chatBox->append((nick + " has joined"));
    ui->chatBox->setTextColor(color);

    activeUserList->append(nick);
    refreshUserList();
}

void MainWindow::participantLeft(const QString &nick)
{
    if (nick.isEmpty())
        return;

    for(int i = 0; i < activeUserList->length(); i++)
    {
        if(QString::compare(activeUserList->at(i), nick, Qt::CaseSensitive) == 0)
        {
            activeUserList->removeAt(i);
            refreshUserList();
        }
    }

    QColor color = ui->chatBox->textColor();
    ui->chatBox->setTextColor(Qt::gray);
    ui->chatBox->append((nick + " has left"));
    ui->chatBox->setTextColor(color);
}

QString MainWindow::getMyNickname()
{
    return localNickname;
}

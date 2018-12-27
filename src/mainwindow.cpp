#include "mainwindow.h"

QStringList *MainWindow::activeUserList = new QStringList();
QString MainWindow::localNickname = "";
Client *MainWindow::client;
NicknameDialog *MainWindow::nickname;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{    
    nickname = new NicknameDialog(this);
    client = new Client();

    nickname->setModal(true);
    nickname->show(); //nickname dialog

    //localNickname = nickname->getNickname(); //get current user nickname

    ui->setupUi(this);
    ui->messageEdit->setFocusPolicy(Qt::StrongFocus);
    ui->chatBox->setFocusPolicy(Qt::NoFocus);
    ui->chatBox->setReadOnly(true);
    ui->userList->setFocusPolicy(Qt::NoFocus);
    ui->messageEdit->installEventFilter(this);

    connect(nickname, SIGNAL(windowClosed()), this, SLOT(refreshUserList()));
    connect(client, SIGNAL(newMessage(QString, QString)), this,
            SLOT(appendMessage(QString, QString)));
    connect(client, SIGNAL(newParticipant(QString)), this,
            SLOT(newParticipant(QString)));
    connect(client, SIGNAL(participantLeft(QString)), this,
            SLOT(participantLeft(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

Client* MainWindow::getClientInstance()
{
    return client;
}

void MainWindow::on_sendButton_clicked()
{
    QString input = ui->messageEdit->toPlainText();

    if (input.isEmpty())
        return;

    client->sendMessage(input);
    appendMessage(localNickname, input);
    ui->messageEdit->clear();
}

void MainWindow::addUserToList(QString nick)
{
    activeUserList->append(nick);
}

void MainWindow::refreshUserList()
{
    ui->userList->clear();

    for (QString user : *activeUserList)
    {
        ui->userList->append(user + '\n');
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

    client->sendMessage(input);
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

void MainWindow::setMyNickname(const QString &myNick)
{
    localNickname = myNick;
}

QString MainWindow::getMyNickname()
{
    return localNickname;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->messageEdit && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if(keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
        {
            enterPressed();
            return true;
        }
        else {
            return QMainWindow::eventFilter(watched, event);
        }
    }
    else {
        return QMainWindow::eventFilter(watched, event);
    }
}

#include "mainwindow.h"

QStringList *MainWindow::ActiveUserList = new QStringList();
QString MainWindow::LocalNickname = "";
Client *MainWindow::client;
NicknameDialog *MainWindow::nickname;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{    
    nickname = new NicknameDialog(this);
    client = new Client();

    nickname->setModal(true);
    nickname->show(); //nickname dialog

    ui->setupUi(this);
    ui->messageEdit->setFocusPolicy(Qt::StrongFocus);
    ui->chatBox->setFocusPolicy(Qt::NoFocus);
    ui->chatBox->setReadOnly(true);
    ui->userList->setFocusPolicy(Qt::NoFocus);
    ui->messageEdit->installEventFilter(this);

    connect(nickname, SIGNAL(WindowClosed()), this, SLOT(RefreshUserList()));
    connect(client, SIGNAL(NewMessage(QString, QString)), this,
            SLOT(AppendMessage(QString, QString)));
    connect(client, SIGNAL(NewParticipant(QString)), this,
            SLOT(NewParticipant(QString)));
    connect(client, SIGNAL(ParticipantLeft(QString)), this,
            SLOT(ParticipantLeft(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

Client* MainWindow::GetClientInstance()
{
    return client;
}

void MainWindow::on_sendButton_clicked()
{
    QString input = ui->messageEdit->toPlainText();

    if (input.isEmpty())
        return;

    client->SendMessage(input);
    AppendMessage(LocalNickname, input);
    ui->messageEdit->clear();
}

void MainWindow::AddUserToList(QString nick)
{
    ActiveUserList->append(nick);
}

void MainWindow::RefreshUserList()
{
    ui->userList->clear();

    for (QString user : *ActiveUserList)
    {
        ui->userList->append(user + '\n');
    }
}

void MainWindow::AppendMessage(const QString &from, const QString &message)
{
    if(from.isEmpty() || message.isEmpty())
        return;

    QString fullMsgFormat = '<' + from + '>' + ' ' + message + '\n';
    ui->chatBox->append(fullMsgFormat);

    QScrollBar *bar = ui->chatBox->verticalScrollBar();
    bar->setValue(bar->maximum());
}

void MainWindow::EnterPressed()
{
    QString input = ui->messageEdit->toPlainText();

    if (input.isEmpty())
        return;

    client->SendMessage(input);
    AppendMessage(LocalNickname, input);
    ui->messageEdit->clear();
}

void MainWindow::NewParticipant(const QString &nick)
{
    if (nick.isEmpty())
        return;

    QColor color = ui->chatBox->textColor();
    ui->chatBox->setTextColor(Qt::gray);
    ui->chatBox->append((nick + " has joined"));
    ui->chatBox->setTextColor(color);

    ActiveUserList->append(nick);
    RefreshUserList();
}

void MainWindow::ParticipantLeft(const QString &nick)
{
    if (nick.isEmpty())
        return;

    for(int i = 0; i < ActiveUserList->length(); i++)
    {
        if(QString::compare(ActiveUserList->at(i), nick, Qt::CaseSensitive) == 0)
        {
            ActiveUserList->removeAt(i);
            RefreshUserList();
        }
    }

    QColor color = ui->chatBox->textColor();
    ui->chatBox->setTextColor(Qt::gray);
    ui->chatBox->append((nick + " has left"));
    ui->chatBox->setTextColor(color);
}

void MainWindow::SetMyNickname(const QString &myNick)
{
    LocalNickname = myNick;
}

QString MainWindow::GetMyNickname()
{
    return LocalNickname;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->messageEdit && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
        if(keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter)
        {
            EnterPressed();
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

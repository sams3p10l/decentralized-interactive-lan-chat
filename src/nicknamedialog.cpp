#include "nicknamedialog.h"
#include "ui_nicknamedialog.h"
#include "mainwindow.h"

Transmitter *NicknameDialog::transmitter;

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
    //Transmitter::transSetNickname(getNickname());

    client = MainWindow::getClientInstance();
    server = Client::getServerInstance();

    //transmitter = Client::getTransmitterInstance();
    //transmitter->startBroadcast();

    transmitter = new Transmitter(client, getNickname());
    transmitter->startBroadcast();
    transmitter->setListenPort(server->serverPort());

    QObject::connect(transmitter, SIGNAL(newConnection(Connection*)), client,
                     SLOT(newConnection(Connection*)));

    QWidget::close();
    emit windowClosed();
}

Transmitter* NicknameDialog::getTransmitterInstance()
{
    return transmitter;
}

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

QString NicknameDialog::GetNickname()
{
    return ui->nicknameEdit->text();
}

void NicknameDialog::on_cancelButton_clicked()
{
    QApplication::instance()->exit();
}

void NicknameDialog::on_okButton_clicked()
{
    MainWindow::AddUserToList(GetNickname());
    MainWindow::SetMyNickname(GetNickname());

    client = MainWindow::GetClientInstance();
    server = Client::GetServerInstance();

    transmitter = new Transmitter(client, GetNickname());
    transmitter->StartBroadcast();
    transmitter->SetListenPort(server->serverPort());

    QObject::connect(transmitter, SIGNAL(NewConnection(Connection*)), client,
                     SLOT(NewConnection(Connection*)));

    QWidget::close();
    emit WindowClosed();
}

Transmitter* NicknameDialog::GetTransmitterInstance()
{
    return transmitter;
}

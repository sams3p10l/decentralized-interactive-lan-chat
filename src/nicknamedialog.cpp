#include "nicknamedialog.h"
#include "ui_nicknamedialog.h"

NicknameDialog::NicknameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NicknameDialog)
{
    ui->setupUi(this);
}

NicknameDialog::~NicknameDialog()
{
    delete ui;
}

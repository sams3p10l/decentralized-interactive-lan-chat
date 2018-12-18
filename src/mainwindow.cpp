#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QObject::connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(on_sendButton_clicked())); //mozda suvisno
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendButton_clicked()
{
    QString text = ui->messageEdit->toPlainText();
    ui->chatBox->append(text);
}

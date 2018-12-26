/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPlainTextEdit *messageEdit;
    QTextBrowser *chatBox;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QTextBrowser *userList;
    QScrollBar *userScrollBar;
    QScrollBar *chatScrollBar;
    QPushButton *sendButton;
    QLabel *label;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(789, 560);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        messageEdit = new QPlainTextEdit(centralWidget);
        messageEdit->setObjectName(QString::fromUtf8("messageEdit"));
        messageEdit->setGeometry(QRect(0, 450, 621, 51));
        chatBox = new QTextBrowser(centralWidget);
        chatBox->setObjectName(QString::fromUtf8("chatBox"));
        chatBox->setGeometry(QRect(0, 0, 641, 431));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(640, -1, 151, 451));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 149, 449));
        userList = new QTextBrowser(scrollAreaWidgetContents);
        userList->setObjectName(QString::fromUtf8("userList"));
        userList->setGeometry(QRect(0, 0, 151, 451));
        userScrollBar = new QScrollBar(scrollAreaWidgetContents);
        userScrollBar->setObjectName(QString::fromUtf8("userScrollBar"));
        userScrollBar->setGeometry(QRect(130, -1, 20, 451));
        userScrollBar->setOrientation(Qt::Vertical);
        scrollArea->setWidget(scrollAreaWidgetContents);
        chatScrollBar = new QScrollBar(centralWidget);
        chatScrollBar->setObjectName(QString::fromUtf8("chatScrollBar"));
        chatScrollBar->setGeometry(QRect(620, -1, 20, 451));
        chatScrollBar->setOrientation(Qt::Vertical);
        sendButton = new QPushButton(centralWidget);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setGeometry(QRect(619, 450, 171, 51));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(6, 430, 611, 20));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 789, 20));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        sendButton->setText(QApplication::translate("MainWindow", "Send", nullptr));
        label->setText(QApplication::translate("MainWindow", "Enter your message:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'nicknamedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NICKNAMEDIALOG_H
#define UI_NICKNAMEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_NicknameDialog
{
public:
    QLineEdit *nicknameEdit;
    QLabel *label;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *NicknameDialog)
    {
        if (NicknameDialog->objectName().isEmpty())
            NicknameDialog->setObjectName(QString::fromUtf8("NicknameDialog"));
        NicknameDialog->resize(388, 286);
        nicknameEdit = new QLineEdit(NicknameDialog);
        nicknameEdit->setObjectName(QString::fromUtf8("nicknameEdit"));
        nicknameEdit->setGeometry(QRect(80, 110, 221, 41));
        QFont font;
        font.setPointSize(11);
        nicknameEdit->setFont(font);
        label = new QLabel(NicknameDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 30, 201, 41));
        label->setFont(font);
        okButton = new QPushButton(NicknameDialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(220, 220, 71, 31));
        cancelButton = new QPushButton(NicknameDialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(300, 220, 71, 31));

        retranslateUi(NicknameDialog);

        QMetaObject::connectSlotsByName(NicknameDialog);
    } // setupUi

    void retranslateUi(QDialog *NicknameDialog)
    {
        NicknameDialog->setWindowTitle(QApplication::translate("NicknameDialog", "Dialog", nullptr));
        label->setText(QApplication::translate("NicknameDialog", "Please enter your nickname:", nullptr));
        okButton->setText(QApplication::translate("NicknameDialog", "OK", nullptr));
        cancelButton->setText(QApplication::translate("NicknameDialog", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NicknameDialog: public Ui_NicknameDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NICKNAMEDIALOG_H

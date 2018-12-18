#ifndef NICKNAMEDIALOG_H
#define NICKNAMEDIALOG_H

#include <QDialog>

namespace Ui {
class NicknameDialog;
}

class NicknameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NicknameDialog(QWidget *parent = nullptr);
    ~NicknameDialog();

private:
    Ui::NicknameDialog *ui;
};

#endif // NICKNAMEDIALOG_H

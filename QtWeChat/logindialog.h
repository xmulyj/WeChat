#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "wechatmaindialog.h"


namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private slots:
    void on_loginButton_clicked();

    void on_regButton_clicked();

private:
    Ui::LoginDialog *ui;
    WeChatMainDialog *wechat_dialog;
};

#endif // LOGINDIALOG_H

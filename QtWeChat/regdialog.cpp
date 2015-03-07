#include "regdialog.h"
#include "ui_regdialog.h"
#include <QMessageBox>

#include "WeChatClient.h"

RegDialog::RegDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegDialog)
{
    ui->setupUi(this);
}

RegDialog::~RegDialog()
{
    delete ui;
}

void RegDialog::on_regButton_clicked()
{
    QString name = ui->nameEdit->text();
    QString passwd = ui->passwdEdit->text();
    QString passwd2 = ui->passwdEdit2->text();
    if(name.length()==0 || passwd.length()==0)
    {
        QMessageBox::information(this, "注册", "昵称和密码不能为空!");
        return;
    }
    if(passwd.length() < 6)
    {
        QMessageBox::information(this, "注册", "密码长度不能小于6个字符!");
        return;
    }

    if(passwd != passwd2)
    {
        QMessageBox::information(this, "注册", "密码不相同!");
        return;
    }

    int fd = TcpSocket::Connect("127.0.0.1", 8080);
    if (fd < 0)
    {
        QMessageBox::information(this, "注册", "连接服务器失败,请稍候重试!");
        return ;
    }
    //注册请求
    RegReq req;
    RegRsp rsp;

    req.set_name(name.toStdString());
    req.set_passwd(passwd.toStdString());

    rsp.set_ret(-1);
    int ret = CWeChatClient::SendAndRecvMsg(fd, CMD_REG_REQ, &req, &rsp);
    if(ret!=0 || rsp.ret() != 0)
    {
        QString qstr;
        qstr.sprintf("注册失败:net_ret=%d,reg_ret=%d", ret, rsp.ret());
        QMessageBox::information(this, "注册", qstr);
    }
    else
    {
        QString qstr;
        qstr.sprintf("注册成功:ID=%d", rsp.id());
        QMessageBox::information(this, "注册", qstr);
    }

    ::close(fd);
}

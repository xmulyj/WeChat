#include "logindialog.h"
#include "ui_logindialog.h"
#include "regdialog.h"

#include <QValidator>
#include <QMessageBox>

#include "enet/ENet.h"
#include "WeChatClient.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    wechat_dialog(NULL)
{
    ui->setupUi(this);

    QRegExp regExp("[1-9][0-9]{0,15}");
    QRegExpValidator *validator = new QRegExpValidator (regExp,this);
    ui->idEdit->setValidator(validator);

    connect(ui->quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_loginButton_clicked()
{
    QString str_id = ui->idEdit->text();
    QString str_passwd = ui->passwdEdit->text();

    if(str_id.length()==0 || str_passwd.length()==0)
    {
        QMessageBox::information(this, "帐号", "帐号和密码不能为空!");
        return;
    }
    bool bret;
    uint32_t id = str_id.toInt(&bret, 10);

    //创建连接
    int fd = TCPSocket::Connect("127.0.0.1", 8080);
    if (fd < 0)
    {
        QMessageBox::information(this, "网络", "连接服务器失败,请稍候重试!");
        return ;
    }
    //登录请求
    LoginReq req;
    LoginRsp rsp;

    req.set_id(id);
    req.set_passwd(str_passwd.toStdString());

    rsp.set_ret(-1);
    int ret = CWeChatClient::SendAndRecvMsg(fd, CMD_LOGIN_REQ, &req, &rsp);
    if(ret!=0 || rsp.ret() != 0)
    {
        QString qstr;
        qstr.sprintf("登录失败:net_ret=%d,login_ret=%d", ret, rsp.ret());
        QMessageBox::information(this, "登录", qstr);
        ::close(fd);
        return ;
    }

    //成功
    if(wechat_dialog == NULL)
    {
        wechat_dialog = new WeChatMainDialog;
        wechat_dialog->Init(fd, rsp);
        wechat_dialog->show();
        //this->hide();
        this->close();
    }
}

void LoginDialog::on_regButton_clicked()
{
    RegDialog reg_dialog(this);
    reg_dialog.exec();
}

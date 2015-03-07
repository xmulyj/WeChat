#include "wechatmaindialog.h"
#include "ui_wechatmaindialog.h"

WeChatMainDialog::WeChatMainDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WeChatMainDialog)
{
    ui->setupUi(this);
    ui->splitter2->setStretchFactor(0, 1);
    ui->splitter2->setStretchFactor(1, 3);
}

WeChatMainDialog::~WeChatMainDialog()
{
    delete ui;
}

void WeChatMainDialog::Init(uint32_t fd, LoginRsp &rsp)
{
    SetNickName(rsp.name());

    //设置成员列表
    for(int i=0; i<rsp.member_list().member_size(); ++i)
    {
        AddMember(rsp.member_list().member(i).id(), rsp.member_list().member(i).name());
    }

    m_WeChatClient.Init(fd, rsp.id(), rsp.name(), this);
}

void WeChatMainDialog::SetNickName(const string &nick_name)
{
    QString qstr_name(nick_name.c_str());
    ui->nickLable->setText(qstr_name);
}

void WeChatMainDialog::AddMember(uint32_t id, const string &name)
{
    for(int i=0; i<ui->memberList->count(); ++i)
    {
        QListWidgetItem *item = ui->memberList->item(i);
        QVariant user_data = item->data(Qt::UserRole);
        uint32_t item_id = user_data.toInt();
        if(item_id == id)
            return;
    }

    QListWidgetItem *item = new QListWidgetItem;
    QString qstr_name(name.c_str());
    item->setText(qstr_name);
    QVariant user_data(id);
    item->setData(Qt::UserRole, user_data);
    ui->memberList->addItem(item);
}

void WeChatMainDialog::DelMember(uint32_t id)
{
    for(int i=0; i<ui->memberList->count(); ++i)
    {
        QListWidgetItem *item = ui->memberList->item(i);
        QVariant user_data = item->data(Qt::UserRole);
        uint32_t item_id = user_data.toInt();
        if(item_id == id)
        {
            ui->memberList->removeItemWidget(item);
            delete item;
        }
    }
}

void WeChatMainDialog::AppendMsg(const Msg &msg)
{
    time_t t = msg.time();
    struct tm *ptm = localtime(&t);
    char time_buff[128];
    sprintf(time_buff, "%d-%02d-%02d %02d:%02d:%02d"
            , ptm->tm_year+1900, ptm->tm_mon+1, ptm->tm_mday
            , ptm->tm_hour, ptm->tm_min, ptm->tm_sec);

    char msg_buff[1024];
    if(msg.type() != 2)
    {
        snprintf(msg_buff, 1024, "[SYS MSG -- %s]\n%s\n", time_buff, msg.msg().c_str());
    }
    else
    {
        snprintf(msg_buff, 1024, "[%s -- %s]\n%s\n", msg.send_name().c_str(), time_buff, msg.msg().c_str());
    }

    QString qstr_msg(msg_buff);
    ui->textBrowser->append(qstr_msg);
    ui->textBrowser->moveCursor(QTextCursor::End);

    if(msg.type() == 0)
    {
        AddMember(msg.send_id(), msg.send_name());
    }
    else if(msg.type() == 1)
    {
        DelMember(msg.send_id());
    }
}

void WeChatMainDialog::AppendMsg(const string &msg)
{
    QString qstr_msg(msg.c_str());
    ui->textBrowser->append(qstr_msg);
    ui->textBrowser->moveCursor(QTextCursor::End);
}

void WeChatMainDialog::on_sendButton_clicked()
{
    QString msg = ui->textEdit->toPlainText();
    if(msg.length()==0)
    {
        return;
    }

    m_WeChatClient.SendMsg(msg.toStdString());
    ui->textEdit->clear();
}

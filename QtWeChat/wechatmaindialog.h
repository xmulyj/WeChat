#ifndef WECHATMAINDIALOG_H
#define WECHATMAINDIALOG_H

#include <QDialog>
#include "WeChatClient.h"

namespace Ui {
class WeChatMainDialog;
}

class WeChatMainDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WeChatMainDialog(QWidget *parent = 0);
    ~WeChatMainDialog();

    void Init(uint32_t fd, LoginRsp &rsp);

private:
    Ui::WeChatMainDialog *ui;
    CWeChatClient m_WeChatClient;

public:
    void SetNickName(const string &nick_name);
    void AddMember(uint32_t id, const string &name);
    void DelMember(uint32_t id);
    void AppendMsg(const Msg &msg);
    void AppendMsg(const string &msg);
private slots:
    void on_sendButton_clicked();
};

#endif // WECHATMAINDIALOG_H

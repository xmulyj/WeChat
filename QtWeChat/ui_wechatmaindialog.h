/********************************************************************************
** Form generated from reading UI file 'wechatmaindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WECHATMAINDIALOG_H
#define UI_WECHATMAINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WeChatMainDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QGraphicsView *headImage;
    QVBoxLayout *verticalLayout_2;
    QLabel *nickLable;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QGraphicsView *advImage;
    QTextEdit *sayEdit;
    QSplitter *splitter2;
    QListWidget *memberList;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QTextBrowser *textBrowser;
    QTextEdit *textEdit;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *sendButton;

    void setupUi(QDialog *WeChatMainDialog)
    {
        if (WeChatMainDialog->objectName().isEmpty())
            WeChatMainDialog->setObjectName(QStringLiteral("WeChatMainDialog"));
        WeChatMainDialog->resize(518, 534);
        verticalLayout_3 = new QVBoxLayout(WeChatMainDialog);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        headImage = new QGraphicsView(WeChatMainDialog);
        headImage->setObjectName(QStringLiteral("headImage"));
        headImage->setMinimumSize(QSize(61, 61));
        headImage->setMaximumSize(QSize(61, 61));

        horizontalLayout_3->addWidget(headImage);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        nickLable = new QLabel(WeChatMainDialog);
        nickLable->setObjectName(QStringLiteral("nickLable"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(nickLable->sizePolicy().hasHeightForWidth());
        nickLable->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(nickLable);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_3->addLayout(verticalLayout_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        advImage = new QGraphicsView(WeChatMainDialog);
        advImage->setObjectName(QStringLiteral("advImage"));
        advImage->setMinimumSize(QSize(281, 61));
        advImage->setMaximumSize(QSize(281, 61));

        horizontalLayout_3->addWidget(advImage);


        verticalLayout_3->addLayout(horizontalLayout_3);

        sayEdit = new QTextEdit(WeChatMainDialog);
        sayEdit->setObjectName(QStringLiteral("sayEdit"));
        sayEdit->setMinimumSize(QSize(0, 51));
        sayEdit->setMaximumSize(QSize(16777215, 51));
        sayEdit->setFrameShape(QFrame::NoFrame);
        sayEdit->setFrameShadow(QFrame::Plain);

        verticalLayout_3->addWidget(sayEdit);

        splitter2 = new QSplitter(WeChatMainDialog);
        splitter2->setObjectName(QStringLiteral("splitter2"));
        splitter2->setOrientation(Qt::Horizontal);
        memberList = new QListWidget(splitter2);
        memberList->setObjectName(QStringLiteral("memberList"));
        splitter2->addWidget(memberList);
        layoutWidget = new QWidget(splitter2);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(layoutWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        horizontalLayout = new QHBoxLayout(tab);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        splitter = new QSplitter(tab);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        textBrowser = new QTextBrowser(splitter);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        splitter->addWidget(textBrowser);
        textEdit = new QTextEdit(splitter);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        splitter->addWidget(textEdit);

        horizontalLayout->addWidget(splitter);

        tabWidget->addTab(tab, QString());

        verticalLayout->addWidget(tabWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        sendButton = new QPushButton(layoutWidget);
        sendButton->setObjectName(QStringLiteral("sendButton"));
        sendButton->setMinimumSize(QSize(71, 31));
        sendButton->setMaximumSize(QSize(71, 31));

        horizontalLayout_2->addWidget(sendButton);


        verticalLayout->addLayout(horizontalLayout_2);

        splitter2->addWidget(layoutWidget);

        verticalLayout_3->addWidget(splitter2);

        splitter2->raise();
        sayEdit->raise();

        retranslateUi(WeChatMainDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(WeChatMainDialog);
    } // setupUi

    void retranslateUi(QDialog *WeChatMainDialog)
    {
        WeChatMainDialog->setWindowTitle(QApplication::translate("WeChatMainDialog", "WeChat", 0));
        nickLable->setText(QApplication::translate("WeChatMainDialog", "\346\230\265\347\247\260...", 0));
        sayEdit->setHtml(QApplication::translate("WeChatMainDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\350\257\264\350\257\264...</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\345\277\203\346\203\205...</p></body></html>", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("WeChatMainDialog", "\347\276\244\350\201\212", 0));
        sendButton->setText(QApplication::translate("WeChatMainDialog", "\345\217\221\351\200\201", 0));
    } // retranslateUi

};

namespace Ui {
    class WeChatMainDialog: public Ui_WeChatMainDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WECHATMAINDIALOG_H

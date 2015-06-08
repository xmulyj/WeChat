/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QGraphicsView *graphicsView;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *Label;
    QLineEdit *idEdit;
    QLabel *Label_2;
    QLineEdit *passwdEdit;
    QPushButton *quitButton;
    QPushButton *loginButton;
    QPushButton *regButton;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QStringLiteral("LoginDialog"));
        LoginDialog->resize(353, 192);
        LoginDialog->setMinimumSize(QSize(353, 192));
        LoginDialog->setMaximumSize(QSize(353, 192));
        graphicsView = new QGraphicsView(LoginDialog);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(10, 10, 331, 61));
        formLayoutWidget = new QWidget(LoginDialog);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(10, 80, 331, 62));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        Label = new QLabel(formLayoutWidget);
        Label->setObjectName(QStringLiteral("Label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, Label);

        idEdit = new QLineEdit(formLayoutWidget);
        idEdit->setObjectName(QStringLiteral("idEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, idEdit);

        Label_2 = new QLabel(formLayoutWidget);
        Label_2->setObjectName(QStringLiteral("Label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, Label_2);

        passwdEdit = new QLineEdit(formLayoutWidget);
        passwdEdit->setObjectName(QStringLiteral("passwdEdit"));
        passwdEdit->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, passwdEdit);

        quitButton = new QPushButton(LoginDialog);
        quitButton->setObjectName(QStringLiteral("quitButton"));
        quitButton->setGeometry(QRect(10, 150, 81, 31));
        quitButton->setAutoDefault(false);
        quitButton->setFlat(false);
        loginButton = new QPushButton(LoginDialog);
        loginButton->setObjectName(QStringLiteral("loginButton"));
        loginButton->setGeometry(QRect(260, 150, 81, 31));
        loginButton->setAutoDefault(false);
        regButton = new QPushButton(LoginDialog);
        regButton->setObjectName(QStringLiteral("regButton"));
        regButton->setGeometry(QRect(210, 150, 51, 31));
        regButton->setAutoDefault(false);
        regButton->setFlat(true);

        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QApplication::translate("LoginDialog", "Login", 0));
        Label->setText(QApplication::translate("LoginDialog", "\345\270\220\345\217\267:", 0));
        Label_2->setText(QApplication::translate("LoginDialog", "\345\257\206\347\240\201:", 0));
        quitButton->setText(QApplication::translate("LoginDialog", "\351\200\200\345\207\272", 0));
        loginButton->setText(QApplication::translate("LoginDialog", "\347\231\273\345\275\225", 0));
        regButton->setText(QApplication::translate("LoginDialog", "&\346\263\250&\345\206\214", 0));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H

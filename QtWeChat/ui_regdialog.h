/********************************************************************************
** Form generated from reading UI file 'regdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGDIALOG_H
#define UI_REGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegDialog
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *Label;
    QLineEdit *nameEdit;
    QLabel *Label_2;
    QLineEdit *passwdEdit;
    QLabel *Label_3;
    QLineEdit *passwdEdit2;
    QPushButton *regButton;

    void setupUi(QDialog *RegDialog)
    {
        if (RegDialog->objectName().isEmpty())
            RegDialog->setObjectName(QStringLiteral("RegDialog"));
        RegDialog->resize(293, 168);
        formLayoutWidget = new QWidget(RegDialog);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(10, 10, 251, 95));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout->setContentsMargins(0, 0, 0, 0);
        Label = new QLabel(formLayoutWidget);
        Label->setObjectName(QStringLiteral("Label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, Label);

        nameEdit = new QLineEdit(formLayoutWidget);
        nameEdit->setObjectName(QStringLiteral("nameEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, nameEdit);

        Label_2 = new QLabel(formLayoutWidget);
        Label_2->setObjectName(QStringLiteral("Label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, Label_2);

        passwdEdit = new QLineEdit(formLayoutWidget);
        passwdEdit->setObjectName(QStringLiteral("passwdEdit"));
        passwdEdit->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(1, QFormLayout::FieldRole, passwdEdit);

        Label_3 = new QLabel(formLayoutWidget);
        Label_3->setObjectName(QStringLiteral("Label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, Label_3);

        passwdEdit2 = new QLineEdit(formLayoutWidget);
        passwdEdit2->setObjectName(QStringLiteral("passwdEdit2"));
        passwdEdit2->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(2, QFormLayout::FieldRole, passwdEdit2);

        regButton = new QPushButton(RegDialog);
        regButton->setObjectName(QStringLiteral("regButton"));
        regButton->setGeometry(QRect(100, 120, 99, 31));
        regButton->setAutoDefault(false);

        retranslateUi(RegDialog);

        QMetaObject::connectSlotsByName(RegDialog);
    } // setupUi

    void retranslateUi(QDialog *RegDialog)
    {
        RegDialog->setWindowTitle(QApplication::translate("RegDialog", "Dialog", 0));
        Label->setText(QApplication::translate("RegDialog", "\346\230\265\347\247\260:", 0));
        Label_2->setText(QApplication::translate("RegDialog", "\345\257\206\347\240\201:", 0));
        Label_3->setText(QApplication::translate("RegDialog", "\347\241\256\350\256\244\345\257\206\347\240\201:", 0));
        regButton->setText(QApplication::translate("RegDialog", "\346\263\250\345\206\214", 0));
    } // retranslateUi

};

namespace Ui {
    class RegDialog: public Ui_RegDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGDIALOG_H

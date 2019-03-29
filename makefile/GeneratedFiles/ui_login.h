/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QHBoxLayout *horizontalLayout_7;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *serverAddressLabel;
    QLineEdit *serverAddressLineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *serverPortLabel;
    QLineEdit *serverPortLineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *userNameLabel;
    QLineEdit *userNameLineEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QFrame *line;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *clearButton;
    QPushButton *enterButton;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer_5;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QStringLiteral("Login"));
        Login->resize(532, 222);
        Login->setMinimumSize(QSize(400, 200));
        Login->setSizeGripEnabled(false);
        Login->setModal(true);
        horizontalLayout_7 = new QHBoxLayout(Login);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        serverAddressLabel = new QLabel(Login);
        serverAddressLabel->setObjectName(QStringLiteral("serverAddressLabel"));

        horizontalLayout->addWidget(serverAddressLabel);

        serverAddressLineEdit = new QLineEdit(Login);
        serverAddressLineEdit->setObjectName(QStringLiteral("serverAddressLineEdit"));

        horizontalLayout->addWidget(serverAddressLineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        serverPortLabel = new QLabel(Login);
        serverPortLabel->setObjectName(QStringLiteral("serverPortLabel"));

        horizontalLayout_2->addWidget(serverPortLabel);

        serverPortLineEdit = new QLineEdit(Login);
        serverPortLineEdit->setObjectName(QStringLiteral("serverPortLineEdit"));
        serverPortLineEdit->setMaxLength(32767);

        horizontalLayout_2->addWidget(serverPortLineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        userNameLabel = new QLabel(Login);
        userNameLabel->setObjectName(QStringLiteral("userNameLabel"));

        horizontalLayout_3->addWidget(userNameLabel);

        userNameLineEdit = new QLineEdit(Login);
        userNameLineEdit->setObjectName(QStringLiteral("userNameLineEdit"));

        horizontalLayout_3->addWidget(userNameLineEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        passwordLabel = new QLabel(Login);
        passwordLabel->setObjectName(QStringLiteral("passwordLabel"));

        horizontalLayout_4->addWidget(passwordLabel);

        passwordLineEdit = new QLineEdit(Login);
        passwordLineEdit->setObjectName(QStringLiteral("passwordLineEdit"));
        passwordLineEdit->setEchoMode(QLineEdit::Password);

        horizontalLayout_4->addWidget(passwordLineEdit);


        verticalLayout->addLayout(horizontalLayout_4);


        horizontalLayout_5->addLayout(verticalLayout);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 4);
        horizontalLayout_5->setStretch(2, 1);

        verticalLayout_2->addLayout(horizontalLayout_5);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        line = new QFrame(Login);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);

        clearButton = new QPushButton(Login);
        clearButton->setObjectName(QStringLiteral("clearButton"));

        horizontalLayout_6->addWidget(clearButton);

        enterButton = new QPushButton(Login);
        enterButton->setObjectName(QStringLiteral("enterButton"));

        horizontalLayout_6->addWidget(enterButton);

        cancelButton = new QPushButton(Login);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout_6->addWidget(cancelButton);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);

        horizontalLayout_6->setStretch(0, 1);

        verticalLayout_2->addLayout(horizontalLayout_6);


        horizontalLayout_7->addLayout(verticalLayout_2);


        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "\347\231\273\351\231\206", Q_NULLPTR));
        serverAddressLabel->setText(QApplication::translate("Login", "\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200   ", Q_NULLPTR));
        serverPortLabel->setText(QApplication::translate("Login", "\346\234\215\345\212\241\345\231\250\347\253\257\345\217\243   ", Q_NULLPTR));
        serverPortLineEdit->setInputMask(QString());
        userNameLabel->setText(QApplication::translate("Login", "\347\224\250\346\210\267\345\220\215       ", Q_NULLPTR));
        passwordLabel->setText(QApplication::translate("Login", "\345\257\206\347\240\201         ", Q_NULLPTR));
        clearButton->setText(QApplication::translate("Login", "\346\270\205\347\251\272", Q_NULLPTR));
        enterButton->setText(QApplication::translate("Login", "\347\241\256\345\256\232", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("Login", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H

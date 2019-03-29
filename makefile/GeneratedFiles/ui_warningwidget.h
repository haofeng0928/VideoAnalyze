/********************************************************************************
** Form generated from reading UI file 'warningwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WARNINGWIDGET_H
#define UI_WARNINGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WarningWidget
{
public:
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QLabel *levelLabel;
    QHBoxLayout *horizontalLayout_2;
    QLabel *iconLabel;
    QLabel *textLabel;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *enterButton;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *WarningWidget)
    {
        if (WarningWidget->objectName().isEmpty())
            WarningWidget->setObjectName(QStringLiteral("WarningWidget"));
        WarningWidget->resize(285, 245);
        horizontalLayout_3 = new QHBoxLayout(WarningWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        levelLabel = new QLabel(WarningWidget);
        levelLabel->setObjectName(QStringLiteral("levelLabel"));

        verticalLayout->addWidget(levelLabel);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        iconLabel = new QLabel(WarningWidget);
        iconLabel->setObjectName(QStringLiteral("iconLabel"));

        horizontalLayout_2->addWidget(iconLabel);

        textLabel = new QLabel(WarningWidget);
        textLabel->setObjectName(QStringLiteral("textLabel"));

        horizontalLayout_2->addWidget(textLabel);

        horizontalLayout_2->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        comboBox = new QComboBox(WarningWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout->addWidget(comboBox);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        enterButton = new QPushButton(WarningWidget);
        enterButton->setObjectName(QStringLiteral("enterButton"));

        horizontalLayout->addWidget(enterButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        horizontalLayout->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout);

        verticalLayout->setStretch(1, 1);

        horizontalLayout_3->addLayout(verticalLayout);


        retranslateUi(WarningWidget);

        QMetaObject::connectSlotsByName(WarningWidget);
    } // setupUi

    void retranslateUi(QWidget *WarningWidget)
    {
        WarningWidget->setWindowTitle(QApplication::translate("WarningWidget", "WarningWidget", Q_NULLPTR));
        levelLabel->setText(QString());
        iconLabel->setText(QString());
        textLabel->setText(QString());
        enterButton->setText(QApplication::translate("WarningWidget", "\347\241\256\345\256\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WarningWidget: public Ui_WarningWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WARNINGWIDGET_H

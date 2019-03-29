/********************************************************************************
** Form generated from reading UI file 'missionlistwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MISSIONLISTWIDGET_H
#define UI_MISSIONLISTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MissionListWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *MissionListWidget)
    {
        if (MissionListWidget->objectName().isEmpty())
            MissionListWidget->setObjectName(QStringLiteral("MissionListWidget"));
        MissionListWidget->resize(555, 375);
        horizontalLayout_2 = new QHBoxLayout(MissionListWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        listWidget = new QListWidget(MissionListWidget);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        verticalLayout->addWidget(listWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton = new QPushButton(MissionListWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);


        retranslateUi(MissionListWidget);

        QMetaObject::connectSlotsByName(MissionListWidget);
    } // setupUi

    void retranslateUi(QWidget *MissionListWidget)
    {
        MissionListWidget->setWindowTitle(QApplication::translate("MissionListWidget", "MissionListWidget", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MissionListWidget", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MissionListWidget: public Ui_MissionListWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MISSIONLISTWIDGET_H

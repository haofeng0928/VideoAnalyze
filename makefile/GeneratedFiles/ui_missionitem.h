/********************************************************************************
** Form generated from reading UI file 'missionitem.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MISSIONITEM_H
#define UI_MISSIONITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MissionItem
{
public:
    QHBoxLayout *horizontalLayout_4;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *cameraNameLabel;
    QLabel *dateLabel;
    QVBoxLayout *verticalLayout;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLabel *lastTimeLabel;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QToolButton *pauseButton;
    QToolButton *stopButton;

    void setupUi(QWidget *MissionItem)
    {
        if (MissionItem->objectName().isEmpty())
            MissionItem->setObjectName(QStringLiteral("MissionItem"));
        MissionItem->resize(463, 70);
        horizontalLayout_4 = new QHBoxLayout(MissionItem);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        cameraNameLabel = new QLabel(MissionItem);
        cameraNameLabel->setObjectName(QStringLiteral("cameraNameLabel"));

        verticalLayout_2->addWidget(cameraNameLabel);

        dateLabel = new QLabel(MissionItem);
        dateLabel->setObjectName(QStringLiteral("dateLabel"));

        verticalLayout_2->addWidget(dateLabel);


        horizontalLayout_3->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        progressBar = new QProgressBar(MissionItem);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);

        verticalLayout->addWidget(progressBar);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(MissionItem);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lastTimeLabel = new QLabel(MissionItem);
        lastTimeLabel->setObjectName(QStringLiteral("lastTimeLabel"));

        horizontalLayout_2->addWidget(lastTimeLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pauseButton = new QToolButton(MissionItem);
        pauseButton->setObjectName(QStringLiteral("pauseButton"));

        horizontalLayout->addWidget(pauseButton);

        stopButton = new QToolButton(MissionItem);
        stopButton->setObjectName(QStringLiteral("stopButton"));

        horizontalLayout->addWidget(stopButton);


        horizontalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_3->setStretch(0, 2);
        horizontalLayout_3->setStretch(1, 1);

        horizontalLayout_4->addLayout(horizontalLayout_3);


        retranslateUi(MissionItem);

        QMetaObject::connectSlotsByName(MissionItem);
    } // setupUi

    void retranslateUi(QWidget *MissionItem)
    {
        MissionItem->setWindowTitle(QApplication::translate("MissionItem", "MissionItem", Q_NULLPTR));
        cameraNameLabel->setText(QString());
        dateLabel->setText(QString());
        label_2->setText(QApplication::translate("MissionItem", "\345\211\251\344\275\231\347\224\250\346\227\266\357\274\232", Q_NULLPTR));
        lastTimeLabel->setText(QString());
        pauseButton->setText(QApplication::translate("MissionItem", "\346\232\202\345\201\234", Q_NULLPTR));
        stopButton->setText(QApplication::translate("MissionItem", "\347\273\210\346\255\242", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MissionItem: public Ui_MissionItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MISSIONITEM_H

/********************************************************************************
** Form generated from reading UI file 'videoplay.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOPLAY_H
#define UI_VIDEOPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VideoPlay
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *videoWidget;

    void setupUi(QWidget *VideoPlay)
    {
        if (VideoPlay->objectName().isEmpty())
            VideoPlay->setObjectName(QStringLiteral("VideoPlay"));
        VideoPlay->resize(658, 378);
        horizontalLayout = new QHBoxLayout(VideoPlay);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        videoWidget = new QWidget(VideoPlay);
        videoWidget->setObjectName(QStringLiteral("videoWidget"));

        horizontalLayout->addWidget(videoWidget);


        retranslateUi(VideoPlay);

        QMetaObject::connectSlotsByName(VideoPlay);
    } // setupUi

    void retranslateUi(QWidget *VideoPlay)
    {
        VideoPlay->setWindowTitle(QApplication::translate("VideoPlay", "VideoPlay", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class VideoPlay: public Ui_VideoPlay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOPLAY_H

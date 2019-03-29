/********************************************************************************
** Form generated from reading UI file 'analyze.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANALYZE_H
#define UI_ANALYZE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <graphlistwidget.h>

QT_BEGIN_NAMESPACE

class Ui_analyzeClass
{
public:
    QAction *loginButton;
    QAction *processButton;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *cameraListTab;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButton;
    QSpacerItem *horizontalSpacer;
    GraphListWidget *graphListlWidget;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *analyzeClass)
    {
        if (analyzeClass->objectName().isEmpty())
            analyzeClass->setObjectName(QStringLiteral("analyzeClass"));
        analyzeClass->resize(1219, 816);
        loginButton = new QAction(analyzeClass);
        loginButton->setObjectName(QStringLiteral("loginButton"));
        processButton = new QAction(analyzeClass);
        processButton->setObjectName(QStringLiteral("processButton"));
        centralWidget = new QWidget(analyzeClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_3 = new QHBoxLayout(centralWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        cameraListTab = new QWidget();
        cameraListTab->setObjectName(QStringLiteral("cameraListTab"));
        tabWidget->addTab(cameraListTab, QString());

        verticalLayout->addWidget(tabWidget);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        toolButton = new QToolButton(centralWidget);
        toolButton->setObjectName(QStringLiteral("toolButton"));

        horizontalLayout->addWidget(toolButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout);

        graphListlWidget = new GraphListWidget(centralWidget);
        graphListlWidget->setObjectName(QStringLiteral("graphListlWidget"));

        verticalLayout_2->addWidget(graphListlWidget);

        verticalLayout_2->setStretch(1, 1);

        horizontalLayout_2->addLayout(verticalLayout_2);

        horizontalLayout_2->setStretch(0, 1);
        horizontalLayout_2->setStretch(1, 5);

        horizontalLayout_3->addLayout(horizontalLayout_2);

        analyzeClass->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(analyzeClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        analyzeClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(analyzeClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        analyzeClass->setStatusBar(statusBar);

        mainToolBar->addAction(loginButton);
        mainToolBar->addAction(processButton);

        retranslateUi(analyzeClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(analyzeClass);
    } // setupUi

    void retranslateUi(QMainWindow *analyzeClass)
    {
        analyzeClass->setWindowTitle(QApplication::translate("analyzeClass", "analyze", Q_NULLPTR));
        loginButton->setText(QApplication::translate("analyzeClass", "\347\231\273\351\231\206", Q_NULLPTR));
        processButton->setText(QApplication::translate("analyzeClass", "\344\273\273\345\212\241", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(cameraListTab), QApplication::translate("analyzeClass", "Tab 1", Q_NULLPTR));
        toolButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class analyzeClass: public Ui_analyzeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALYZE_H

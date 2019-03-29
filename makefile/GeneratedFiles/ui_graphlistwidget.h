/********************************************************************************
** Form generated from reading UI file 'graphlistwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GRAPHLISTWIDGET_H
#define UI_GRAPHLISTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GraphListWidget
{
public:

    void setupUi(QWidget *GraphListWidget)
    {
        if (GraphListWidget->objectName().isEmpty())
            GraphListWidget->setObjectName(QStringLiteral("GraphListWidget"));
        GraphListWidget->resize(400, 300);

        retranslateUi(GraphListWidget);

        QMetaObject::connectSlotsByName(GraphListWidget);
    } // setupUi

    void retranslateUi(QWidget *GraphListWidget)
    {
        GraphListWidget->setWindowTitle(QApplication::translate("GraphListWidget", "GraphListWidget", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class GraphListWidget: public Ui_GraphListWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPHLISTWIDGET_H

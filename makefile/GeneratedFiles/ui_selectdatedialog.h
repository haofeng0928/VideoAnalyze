/********************************************************************************
** Form generated from reading UI file 'selectdatedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTDATEDIALOG_H
#define UI_SELECTDATEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SelectDateDialog
{
public:
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_2;
    QDateEdit *startDate;
    QTimeEdit *startTimeEdit;
    QLabel *label;
    QVBoxLayout *verticalLayout_3;
    QDateEdit *endDate;
    QTimeEdit *endTimeEdit;
    QPushButton *searchButton;
    QPushButton *startButton;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *statusLabel;

    void setupUi(QDialog *SelectDateDialog)
    {
        if (SelectDateDialog->objectName().isEmpty())
            SelectDateDialog->setObjectName(QStringLiteral("SelectDateDialog"));
        SelectDateDialog->resize(538, 106);
        horizontalLayout_3 = new QHBoxLayout(SelectDateDialog);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_3 = new QLabel(SelectDateDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        startDate = new QDateEdit(SelectDateDialog);
        startDate->setObjectName(QStringLiteral("startDate"));
        startDate->setCalendarPopup(true);

        verticalLayout_2->addWidget(startDate);

        startTimeEdit = new QTimeEdit(SelectDateDialog);
        startTimeEdit->setObjectName(QStringLiteral("startTimeEdit"));
        startTimeEdit->setWrapping(false);
        startTimeEdit->setFrame(true);
        startTimeEdit->setAlignment(Qt::AlignCenter);
        startTimeEdit->setReadOnly(false);
        startTimeEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
        startTimeEdit->setCalendarPopup(false);

        verticalLayout_2->addWidget(startTimeEdit);


        horizontalLayout->addLayout(verticalLayout_2);

        label = new QLabel(SelectDateDialog);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        endDate = new QDateEdit(SelectDateDialog);
        endDate->setObjectName(QStringLiteral("endDate"));
        endDate->setCalendarPopup(true);

        verticalLayout_3->addWidget(endDate);

        endTimeEdit = new QTimeEdit(SelectDateDialog);
        endTimeEdit->setObjectName(QStringLiteral("endTimeEdit"));
        endTimeEdit->setWrapping(false);
        endTimeEdit->setFrame(true);
        endTimeEdit->setAlignment(Qt::AlignCenter);
        endTimeEdit->setReadOnly(false);
        endTimeEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
        endTimeEdit->setCalendarPopup(false);

        verticalLayout_3->addWidget(endTimeEdit);


        horizontalLayout->addLayout(verticalLayout_3);

        searchButton = new QPushButton(SelectDateDialog);
        searchButton->setObjectName(QStringLiteral("searchButton"));

        horizontalLayout->addWidget(searchButton);

        startButton = new QPushButton(SelectDateDialog);
        startButton->setObjectName(QStringLiteral("startButton"));

        horizontalLayout->addWidget(startButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(SelectDateDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit = new QLineEdit(SelectDateDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        statusLabel = new QLabel(SelectDateDialog);
        statusLabel->setObjectName(QStringLiteral("statusLabel"));
        statusLabel->setTextFormat(Qt::RichText);

        verticalLayout->addWidget(statusLabel);

        verticalLayout->setStretch(0, 2);
        verticalLayout->setStretch(1, 2);
        verticalLayout->setStretch(2, 1);

        horizontalLayout_3->addLayout(verticalLayout);


        retranslateUi(SelectDateDialog);

        QMetaObject::connectSlotsByName(SelectDateDialog);
    } // setupUi

    void retranslateUi(QDialog *SelectDateDialog)
    {
        SelectDateDialog->setWindowTitle(QApplication::translate("SelectDateDialog", "SelectDateDialog", Q_NULLPTR));
        label_3->setText(QApplication::translate("SelectDateDialog", "\351\200\211\346\213\251\346\227\245\346\234\237\344\270\216\346\227\266\351\227\264\357\274\232", Q_NULLPTR));
        startDate->setDisplayFormat(QApplication::translate("SelectDateDialog", "yyyy-MM-dd", Q_NULLPTR));
        startTimeEdit->setDisplayFormat(QApplication::translate("SelectDateDialog", "hh:mm:ss", Q_NULLPTR));
        label->setText(QApplication::translate("SelectDateDialog", "\350\207\263", Q_NULLPTR));
        endDate->setDisplayFormat(QApplication::translate("SelectDateDialog", "yyyy-MM-dd", Q_NULLPTR));
        endTimeEdit->setDisplayFormat(QApplication::translate("SelectDateDialog", "hh:mm:ss", Q_NULLPTR));
        searchButton->setText(QApplication::translate("SelectDateDialog", "\346\220\234\347\264\242", Q_NULLPTR));
        startButton->setText(QApplication::translate("SelectDateDialog", "\345\274\200\345\247\213\344\273\273\345\212\241", Q_NULLPTR));
        label_2->setText(QApplication::translate("SelectDateDialog", "\350\247\206\351\242\221\346\226\207\344\273\266\345\220\215\357\274\232    ", Q_NULLPTR));
        statusLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SelectDateDialog: public Ui_SelectDateDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTDATEDIALOG_H

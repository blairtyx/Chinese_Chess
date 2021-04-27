/********************************************************************************
** Form generated from reading UI file 'start_window.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_START_WINDOW_H
#define UI_START_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_start_window
{
public:
    QPushButton *startButton;
    QPushButton *endButton;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *start_window)
    {
        if (start_window->objectName().isEmpty())
            start_window->setObjectName(QStringLiteral("start_window"));
        start_window->resize(480, 272);
        startButton = new QPushButton(start_window);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setGeometry(QRect(60, 170, 112, 32));
        endButton = new QPushButton(start_window);
        endButton->setObjectName(QStringLiteral("endButton"));
        endButton->setGeometry(QRect(300, 170, 112, 32));
        label = new QLabel(start_window);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(110, 40, 271, 81));
        label->setTextFormat(Qt::RichText);
        label_2 = new QLabel(start_window);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(220, 130, 58, 16));

        retranslateUi(start_window);

        QMetaObject::connectSlotsByName(start_window);
    } // setupUi

    void retranslateUi(QWidget *start_window)
    {
        start_window->setWindowTitle(QApplication::translate("start_window", "Form", Q_NULLPTR));
        startButton->setText(QApplication::translate("start_window", "Start", Q_NULLPTR));
        endButton->setText(QApplication::translate("start_window", "Quit", Q_NULLPTR));
        label->setText(QApplication::translate("start_window", "<html><head/><body><p><span style=\" font-size:36pt; font-weight:600;\">Chiness Chess</span></p></body></html>", Q_NULLPTR));
        label_2->setText(QApplication::translate("start_window", "L&X", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class start_window: public Ui_start_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_START_WINDOW_H

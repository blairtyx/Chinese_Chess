/********************************************************************************
** Form generated from reading UI file 'window.ui'
**
** Created by: Qt User Interface Compiler version 5.9.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_window
{
public:
    QPushButton *flipButton;
    QPushButton *pauseButton;

    void setupUi(QWidget *window)
    {
        if (window->objectName().isEmpty())
            window->setObjectName(QStringLiteral("window"));
        window->resize(800, 600);
        flipButton = new QPushButton(window);
        flipButton->setObjectName(QStringLiteral("flipButton"));
        flipButton->setEnabled(true);
        flipButton->setGeometry(QRect(0, 0, 81, 32));
        pauseButton = new QPushButton(window);
        pauseButton->setObjectName(QStringLiteral("pauseButton"));
        pauseButton->setGeometry(QRect(0, 60, 81, 32));

        retranslateUi(window);

        QMetaObject::connectSlotsByName(window);
    } // setupUi

    void retranslateUi(QWidget *window)
    {
        window->setWindowTitle(QApplication::translate("window", "window", Q_NULLPTR));
        flipButton->setText(QApplication::translate("window", "F L I P", Q_NULLPTR));
        pauseButton->setText(QApplication::translate("window", "pause", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class window: public Ui_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H

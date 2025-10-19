/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *prebtn;
    QPushButton *stopandbfbtn;
    QPushButton *netbtn;
    QPushButton *moshibtn;
    QPushButton *musiclistbtn;
    QListWidget *mclist;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(959, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(30, 470, 631, 71));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        prebtn = new QPushButton(widget);
        prebtn->setObjectName("prebtn");

        horizontalLayout->addWidget(prebtn);

        stopandbfbtn = new QPushButton(widget);
        stopandbfbtn->setObjectName("stopandbfbtn");

        horizontalLayout->addWidget(stopandbfbtn);

        netbtn = new QPushButton(widget);
        netbtn->setObjectName("netbtn");

        horizontalLayout->addWidget(netbtn);

        moshibtn = new QPushButton(widget);
        moshibtn->setObjectName("moshibtn");

        horizontalLayout->addWidget(moshibtn);

        musiclistbtn = new QPushButton(widget);
        musiclistbtn->setObjectName("musiclistbtn");

        horizontalLayout->addWidget(musiclistbtn);

        mclist = new QListWidget(centralwidget);
        mclist->setObjectName("mclist");
        mclist->setGeometry(QRect(670, 30, 221, 421));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 959, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        prebtn->setText(QString());
        stopandbfbtn->setText(QString());
        netbtn->setText(QString());
        moshibtn->setText(QString());
        musiclistbtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

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
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QListWidget *mclist;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout;
    QSlider *progressSlider;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *nowtimelbl;
    QSpacerItem *horizontalSpacer_2;
    QLabel *currentMusicLbl;
    QSpacerItem *horizontalSpacer;
    QLabel *totaltimelbl;
    QWidget *widget_4;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *prebtn;
    QPushButton *stopandbfbtn;
    QPushButton *netbtn;
    QPushButton *moshibtn;
    QPushButton *musiclistbtn;
    QSpacerItem *verticalSpacer_4;
    QWidget *lyricWidget;
    QLabel *lyricLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(959, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        mclist = new QListWidget(centralwidget);
        mclist->setObjectName("mclist");
        mclist->setGeometry(QRect(700, 10, 221, 511));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 370, 681, 151));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        widget_2 = new QWidget(verticalLayoutWidget);
        widget_2->setObjectName("widget_2");
        verticalLayout = new QVBoxLayout(widget_2);
        verticalLayout->setObjectName("verticalLayout");
        progressSlider = new QSlider(widget_2);
        progressSlider->setObjectName("progressSlider");
        progressSlider->setOrientation(Qt::Orientation::Horizontal);

        verticalLayout->addWidget(progressSlider);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        nowtimelbl = new QLabel(widget_2);
        nowtimelbl->setObjectName("nowtimelbl");

        horizontalLayout_2->addWidget(nowtimelbl);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        currentMusicLbl = new QLabel(widget_2);
        currentMusicLbl->setObjectName("currentMusicLbl");

        horizontalLayout_2->addWidget(currentMusicLbl);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        totaltimelbl = new QLabel(widget_2);
        totaltimelbl->setObjectName("totaltimelbl");

        horizontalLayout_2->addWidget(totaltimelbl);


        verticalLayout->addLayout(horizontalLayout_2);

        widget_4 = new QWidget(widget_2);
        widget_4->setObjectName("widget_4");

        verticalLayout->addWidget(widget_4);

        widget = new QWidget(widget_2);
        widget->setObjectName("widget");
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


        verticalLayout->addWidget(widget);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);


        verticalLayout_2->addWidget(widget_2);

        lyricWidget = new QWidget(centralwidget);
        lyricWidget->setObjectName("lyricWidget");
        lyricWidget->setGeometry(QRect(10, 10, 681, 341));
        lyricLabel = new QLabel(lyricWidget);
        lyricLabel->setObjectName("lyricLabel");
        lyricLabel->setGeometry(QRect(220, 150, 211, 21));
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
        nowtimelbl->setText(QCoreApplication::translate("MainWindow", "00:00", nullptr));
        currentMusicLbl->setText(QCoreApplication::translate("MainWindow", "\346\234\252\346\222\255\346\224\276", nullptr));
        totaltimelbl->setText(QCoreApplication::translate("MainWindow", "00:00", nullptr));
        prebtn->setText(QString());
        stopandbfbtn->setText(QString());
        netbtn->setText(QString());
        moshibtn->setText(QString());
        musiclistbtn->setText(QString());
        lyricLabel->setText(QCoreApplication::translate("MainWindow", "\346\255\214\350\257\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

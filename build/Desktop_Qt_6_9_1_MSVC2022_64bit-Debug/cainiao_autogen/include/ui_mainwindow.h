/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QPushButton *btnLoadMap;
    QPushButton *btnLoadPackages;
    QPushButton *btnCalculate;
    QPushButton *btnDisplay;
    QTextEdit *txtResult;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        btnLoadMap = new QPushButton(centralwidget);
        btnLoadMap->setObjectName("btnLoadMap");

        verticalLayout->addWidget(btnLoadMap);

        btnLoadPackages = new QPushButton(centralwidget);
        btnLoadPackages->setObjectName("btnLoadPackages");

        verticalLayout->addWidget(btnLoadPackages);

        btnCalculate = new QPushButton(centralwidget);
        btnCalculate->setObjectName("btnCalculate");

        verticalLayout->addWidget(btnCalculate);

        btnDisplay = new QPushButton(centralwidget);
        btnDisplay->setObjectName("btnDisplay");

        verticalLayout->addWidget(btnDisplay);

        txtResult = new QTextEdit(centralwidget);
        txtResult->setObjectName("txtResult");

        verticalLayout->addWidget(txtResult);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 17));
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
        btnLoadMap->setText(QCoreApplication::translate("MainWindow", "\345\212\240\350\275\275\345\234\260\345\233\276", nullptr));
        btnLoadPackages->setText(QCoreApplication::translate("MainWindow", "\345\212\240\350\275\275\345\214\205\350\243\271", nullptr));
        btnCalculate->setText(QCoreApplication::translate("MainWindow", "\350\256\241\347\256\227\350\267\257\345\276\204", nullptr));
        btnDisplay->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\347\273\223\346\236\234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'mainframe.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFRAME_H
#define UI_MAINFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainFrameClass
{
public:
    QTableWidget *tableWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QWidget *tab_3;
    QWidget *tab_4;
    QPushButton *pushButton_exit;
    QLabel *label;

    void setupUi(QWidget *MainFrameClass)
    {
        if (MainFrameClass->objectName().isEmpty())
            MainFrameClass->setObjectName(QStringLiteral("MainFrameClass"));
        MainFrameClass->resize(1024, 768);
        tableWidget = new QTableWidget(MainFrameClass);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(10, 110, 311, 191));
        tableWidget->setColumnCount(5);
        tabWidget = new QTabWidget(MainFrameClass);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(340, 90, 571, 301));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        tabWidget->addTab(tab_4, QString());
        pushButton_exit = new QPushButton(MainFrameClass);
        pushButton_exit->setObjectName(QStringLiteral("pushButton_exit"));
        pushButton_exit->setGeometry(QRect(10, 730, 75, 23));
        label = new QLabel(MainFrameClass);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 70, 54, 12));

        retranslateUi(MainFrameClass);

        tabWidget->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(MainFrameClass);
    } // setupUi

    void retranslateUi(QWidget *MainFrameClass)
    {
        MainFrameClass->setWindowTitle(QApplication::translate("MainFrameClass", "MainFrame", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainFrameClass", "\346\265\213\350\257\225\346\265\213\350\257\225\344\270\200", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainFrameClass", "\346\265\213\350\257\225\346\265\213\350\257\225\344\272\214", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainFrameClass", "\346\265\213\350\257\225\346\265\213\350\257\225\344\270\211", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainFrameClass", "\346\265\213\350\257\225\346\265\213\350\257\225\345\233\233", 0));
        pushButton_exit->setText(QApplication::translate("MainFrameClass", "\351\200\200\345\207\272", 0));
        label->setText(QApplication::translate("MainFrameClass", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class MainFrameClass: public Ui_MainFrameClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFRAME_H

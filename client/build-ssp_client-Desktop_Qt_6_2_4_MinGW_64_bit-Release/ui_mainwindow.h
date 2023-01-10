/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QLabel *label_2;
    QTextEdit *EditUsername;
    QPushButton *Reg;
    QPushButton *Login;
    QTextEdit *EditPassword;
    QTextEdit *EditPublishMessage;
    QLabel *label_3;
    QTextEdit *EditLog;
    QLabel *label_4;
    QTextEdit *EditMessageList;
    QLabel *label_5;
    QTextEdit *EditFriendName;
    QPushButton *AddFriend;
    QPushButton *DeleteFriend;
    QTextEdit *EditFriendName_2;
    QPushButton *SendMessage;
    QLabel *label_6;
    QPushButton *GetMessage;
    QTableWidget *tblMessageList;
    QPushButton *Logout;
    QPlainTextEdit *EditPhoto;
    QLabel *label_7;
    QPushButton *Test;
    QTextEdit *EditTest;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1930, 1112);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 60, 53, 16));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(60, 140, 53, 16));
        EditUsername = new QTextEdit(centralwidget);
        EditUsername->setObjectName(QString::fromUtf8("EditUsername"));
        EditUsername->setGeometry(QRect(100, 60, 151, 20));
        Reg = new QPushButton(centralwidget);
        Reg->setObjectName(QString::fromUtf8("Reg"));
        Reg->setGeometry(QRect(120, 190, 75, 24));
        Login = new QPushButton(centralwidget);
        Login->setObjectName(QString::fromUtf8("Login"));
        Login->setGeometry(QRect(30, 190, 75, 24));
        EditPassword = new QTextEdit(centralwidget);
        EditPassword->setObjectName(QString::fromUtf8("EditPassword"));
        EditPassword->setGeometry(QRect(100, 140, 151, 20));
        EditPublishMessage = new QTextEdit(centralwidget);
        EditPublishMessage->setObjectName(QString::fromUtf8("EditPublishMessage"));
        EditPublishMessage->setGeometry(QRect(450, 110, 491, 181));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(450, 640, 61, 41));
        EditLog = new QTextEdit(centralwidget);
        EditLog->setObjectName(QString::fromUtf8("EditLog"));
        EditLog->setGeometry(QRect(450, 680, 521, 271));
        EditLog->setReadOnly(true);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(450, 80, 53, 16));
        EditMessageList = new QTextEdit(centralwidget);
        EditMessageList->setObjectName(QString::fromUtf8("EditMessageList"));
        EditMessageList->setGeometry(QRect(450, 340, 421, 281));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(450, 310, 53, 16));
        EditFriendName = new QTextEdit(centralwidget);
        EditFriendName->setObjectName(QString::fromUtf8("EditFriendName"));
        EditFriendName->setGeometry(QRect(100, 230, 141, 31));
        AddFriend = new QPushButton(centralwidget);
        AddFriend->setObjectName(QString::fromUtf8("AddFriend"));
        AddFriend->setGeometry(QRect(10, 230, 75, 24));
        DeleteFriend = new QPushButton(centralwidget);
        DeleteFriend->setObjectName(QString::fromUtf8("DeleteFriend"));
        DeleteFriend->setGeometry(QRect(10, 270, 75, 24));
        EditFriendName_2 = new QTextEdit(centralwidget);
        EditFriendName_2->setObjectName(QString::fromUtf8("EditFriendName_2"));
        EditFriendName_2->setGeometry(QRect(100, 270, 141, 31));
        SendMessage = new QPushButton(centralwidget);
        SendMessage->setObjectName(QString::fromUtf8("SendMessage"));
        SendMessage->setGeometry(QRect(950, 110, 75, 24));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(920, 310, 53, 20));
        GetMessage = new QPushButton(centralwidget);
        GetMessage->setObjectName(QString::fromUtf8("GetMessage"));
        GetMessage->setGeometry(QRect(1400, 340, 75, 24));
        tblMessageList = new QTableWidget(centralwidget);
        tblMessageList->setObjectName(QString::fromUtf8("tblMessageList"));
        tblMessageList->setGeometry(QRect(920, 340, 471, 281));
        Logout = new QPushButton(centralwidget);
        Logout->setObjectName(QString::fromUtf8("Logout"));
        Logout->setGeometry(QRect(210, 190, 75, 24));
        EditPhoto = new QPlainTextEdit(centralwidget);
        EditPhoto->setObjectName(QString::fromUtf8("EditPhoto"));
        EditPhoto->setGeometry(QRect(100, 310, 141, 31));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(32, 320, 61, 20));
        Test = new QPushButton(centralwidget);
        Test->setObjectName(QString::fromUtf8("Test"));
        Test->setGeometry(QRect(10, 420, 75, 24));
        EditTest = new QTextEdit(centralwidget);
        EditTest->setObjectName(QString::fromUtf8("EditTest"));
        EditTest->setGeometry(QRect(100, 400, 171, 101));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\345\257\206\347\240\201", nullptr));
        Reg->setText(QCoreApplication::translate("MainWindow", "\346\263\250\345\206\214", nullptr));
        Login->setText(QCoreApplication::translate("MainWindow", "\347\231\273\345\275\225", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\346\227\245\345\277\227", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\345\217\221\345\270\203\346\266\210\346\201\257", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\346\266\210\346\201\257\345\210\227\350\241\250", nullptr));
        AddFriend->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\345\245\275\345\217\213", nullptr));
        DeleteFriend->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\345\245\275\345\217\213", nullptr));
        SendMessage->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\346\211\200\346\234\211\346\266\210\346\201\257", nullptr));
        GetMessage->setText(QCoreApplication::translate("MainWindow", "\350\216\267\345\217\226\346\266\210\346\201\257", nullptr));
        Logout->setText(QCoreApplication::translate("MainWindow", "\347\231\273\345\207\272", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\346\226\260\346\266\210\346\201\257", nullptr));
        Test->setText(QCoreApplication::translate("MainWindow", "\346\265\213\350\257\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

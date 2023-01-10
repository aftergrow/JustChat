#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ctime>
#include <sys/time.h>>
#include "D:\Haizei\ssp_new\ssp_client\message_define.pb.h"

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include<winSock2.h>
    #include<windows.h>
    //#pragma comment(lib,"ws2_32.lib")//链接此动态链接库 windows特有
#else
    #include<arpa/inet.h>//selcet
    #include<unistd.h>//uni std
    #include<string.h>

    #define SOCKET int
    #define INVALID_SOCKET (SOCKET)(~0)
    #define SOCKET_ERROR (-1)
#endif

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Reg_clicked();

    void on_Login_clicked();

    void on_AddFriend_clicked();

    void on_DeleteFriend_clicked();

    void on_SendMessage_clicked();

    void on_GetMessage_clicked();

    void on_Logout_clicked();

    void on_Test_clicked();

private:
    Ui::MainWindow *ui;

private:
    int SocketInit();
    int SocketClose();
    int SocketSend(int size);
    int SocketRecv();

    int WaitRsp();
    void TestFresh();
private:
    WORD ver;
    WSADATA dat;
    char recv_buffer[10240];
    char send_buffer[10240];
public:
    ssp::CommonReq clientReq;
    ssp::CommonRsp clinetRsp;
    bool is_connected;//从底层上
    bool is_logined;//从业务
    SOCKET sock_client;
    int send_or_recv;
    int login_user_id; //当前登录用户的user_id
    int get_photo_flag;
    uint32_t last_user_get_time;


};
#endif // MAINWINDOW_H

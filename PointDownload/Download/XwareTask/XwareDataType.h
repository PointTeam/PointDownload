#ifndef XWAREDATATYPE_H
#define XWAREDATATYPE_H

//#include <QString>


enum XwareTaskState
{
    x_dload,
    x_pause,
    x_wait,
    x_other
};

enum XwareLoginResultType
{
    x_LoginSuccess,
    x_UserDoesNotExist,
    x_PasswordError,
    x_UserOrPwdError,
    x_LoginTimeOut,
    x_Logout
};

struct XwareTaskInfo
{
    QString tid; // task ID
    QString name; // name
    QString size;  // size :  xxGB/MB/KB
    QString progress; // progress %
    QString speed; // speed
    QString remainTime;
    XwareTaskState state;
    QString url; // url
    QString offlineChnlSpeed;
    QString highChnlSpeed;
//    QString uploadSpeed;
};


#endif // XWAREDATATYPE_H

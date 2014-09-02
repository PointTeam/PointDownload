#include "normalnotice.h"
#include <QtQml>

NormalNotice::NormalNotice(QObject *parent) :
    QObject(parent)
{
    //import时使用Singleton.NormalNotice
    qmlRegisterSingletonType<NormalNotice>("Singleton.NormalNotice", 1, 0, "NormalNotice", normalNoticeObj);

    initData();
}

NormalNotice * NormalNotice::normalNotice = NULL;
NormalNotice * NormalNotice::getInstance()
{
    if (normalNotice == NULL)
        normalNotice = new NormalNotice();
    return normalNotice;
}

void NormalNotice::initData()
{
    noticeTitle = tr("Notice");
    gmessage = "";
    gnoticeTitleColor = Notice_Color_Notice;
}

void NormalNotice::setNoticeTitle(QString title)
{
    noticeTitle = title;
}

void NormalNotice::setNoticeTitleColor(NoticeTitleColor noticeTitleColor)
{
    gnoticeTitleColor = noticeTitleColor;
}

void NormalNotice::setMessage(QString message)
{
    gmessage = message;
}

void NormalNotice::appendMessage(QString message)
{
    gmessage += "\n";
    gmessage += message;
}

void NormalNotice::showMessage()
{
    emit signalShowMessage(noticeTitle, colorToString(gnoticeTitleColor), gmessage);
}

void NormalNotice::showMessage(QString message)
{
    emit signalShowMessage("", colorToString(gnoticeTitleColor), message);
}

void NormalNotice::showMessage(QString title, QString message)
{
    emit signalShowMessage(title,colorToString(gnoticeTitleColor), message);
}

void NormalNotice::showMessage(QString title, NoticeTitleColor noticeTitleColor, QString message)
{
    emit signalShowMessage(title, colorToString(noticeTitleColor), message);
}

QString NormalNotice::colorToString(NoticeTitleColor noticeColor)
{
    switch (noticeColor)
    {
    case Notice_Color_Notice:
        return "#cbd0d4";
        break;
    case Notice_Color_Warning:
        return "#e5a300";
        break;
    case Notice_Color_Success:
        return "#ffffff";
        break;
    case Notice_Color_Error:
        return "#c73100";
        break;
    default:
        return "#1c252e";
        break;
    }
}





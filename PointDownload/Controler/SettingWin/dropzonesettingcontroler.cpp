#include "dropzonesettingcontroler.h"

DropzoneSettingControler::DropzoneSettingControler(QObject *parent) :
    QObject(parent)
{
    //import时使用Singleton.TopContrl，在获取内容或调用函数时使用PEventFilter
    qmlRegisterSingletonType<DropzoneSettingControler>("Singleton.DropzoneSettingControler", 1, 0, "DropzoneSettingControler", dzSettingCtrlObj);

    initData();
    initTimer();
}

DropzoneSettingControler * DropzoneSettingControler::dropzoneSettingControler = NULL;
DropzoneSettingControler * DropzoneSettingControler::getInstance()
{
    if (dropzoneSettingControler == NULL)
        dropzoneSettingControler = new DropzoneSettingControler();
    return dropzoneSettingControler;
}

void DropzoneSettingControler::initData()
{
    setOpacity(gHandler.getChildElement(DropzoneSetting,"Opacity").toInt());
    setInfoInterval(gHandler.getChildElement(DropzoneSetting,"InfoInterval").toInt());
    setShowJobCount(gHandler.getChildElement(DropzoneSetting,"ShowJobCount")=="True"?true:false);
    setShowStorageUsage(gHandler.getChildElement(DropzoneSetting,"ShowStorageUsage")=="True"?true:false);
    setWinX(gHandler.getChildElement(DropzoneSetting,"WinX").toInt());
    setWinY(gHandler.getChildElement(DropzoneSetting,"WinY").toInt());
}

void DropzoneSettingControler::initTimer()
{
    QTimer * refreshTimer = new QTimer();
    connect(refreshTimer, SIGNAL(timeout()), this , SLOT(slotUpdateJobCount()));
    connect(refreshTimer, SIGNAL(timeout()), this, SLOT(slotUpdateStorageUsage()));
    refreshTimer->start(REFRESH_INTERVAL);
}

void DropzoneSettingControler::slotUpdateJobCount()
{
    emit sNewJobCount(UnifiedInterface::getInstance()->getJobCount());
}

void DropzoneSettingControler::slotUpdateStorageUsage()
{
    emit sNewStorageUsage(MiddleSender::getInstance()->getDiskUsage());
}

int DropzoneSettingControler::getOpacity()
{
    return opacity;
}

int DropzoneSettingControler::getInfoInterval()
{
    return infoInterval;
}

bool DropzoneSettingControler::getShowJobCount()
{
    return showJobCount;
}

bool DropzoneSettingControler::getShowStorageUsage()
{
    return showStorageUsage;
}

int DropzoneSettingControler::getWinX()
{
    return winX;
}

int DropzoneSettingControler::getWinY()
{
    return winY;
}

void DropzoneSettingControler::setOpacity(int tmpOpacity)
{
    if (tmpOpacity == 0)
        return;
    gHandler.setChildElement(DropzoneSetting,"Opacity",QString::number(tmpOpacity));
    opacity = tmpOpacity;
    emit sOpacityChange();
}

void DropzoneSettingControler::setInfoInterval(int interval)
{
    if (interval == 0)
        return;
    gHandler.setChildElement(DropzoneSetting,"InfoInterval",QString::number(interval));
    infoInterval = interval;
    emit sInfoIntervalChange();
}

void DropzoneSettingControler::setShowJobCount(bool flag)
{
    if (flag)
        gHandler.setChildElement(DropzoneSetting,"ShowJobCount","True");
    else
        gHandler.setChildElement(DropzoneSetting,"ShowJobCount","False");
    showJobCount = flag;
    emit sShowJobCountChange();
}

void DropzoneSettingControler::setShowStorageUsage(bool flag)
{
    if (flag)
        gHandler.setChildElement(DropzoneSetting,"ShowStorageUsage","True");
    else
        gHandler.setChildElement(DropzoneSetting,"ShowStorageUsage","False");
    showStorageUsage = flag;
    emit sShowStorageUsageChange();
}

void DropzoneSettingControler::setWinX(int x)
{
    winX = x;
    gHandler.setChildElement(DropzoneSetting,"WinX",QString::number(x));
    emit sWinXChange();
}

void DropzoneSettingControler::setWinY(int y)
{
    winY = y;
    gHandler.setChildElement(DropzoneSetting,"WinY",QString::number(y));
    emit sWinYChange();
}









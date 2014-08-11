#include "dropzonesettingcontroler.h"

DropzoneSettingControler::DropzoneSettingControler(QObject *parent) :
    QObject(parent)
{
    //import时使用Singleton.TopContrl，在获取内容或调用函数时使用PEventFilter
    qmlRegisterSingletonType<DropzoneSettingControler>("Singleton.DropzoneSettingControler", 1, 0, "DropzoneSettingControler", dzSettingCtrlObj);

    initData();
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
    setShowCpuUsage(gHandler.getChildElement(DropzoneSetting,"ShowCPUUsage")=="True"?true:false);
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

bool DropzoneSettingControler::getShowCpuUsage()
{
    return showCpuUsage;
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

void DropzoneSettingControler::setShowCpuUsage(bool flag)
{
    if (flag)
        gHandler.setChildElement(DropzoneSetting,"ShowCPUUsage","True");
    else
        gHandler.setChildElement(DropzoneSetting,"ShowCPUUsage","False");
    showCpuUsage = flag;
    emit sShowCpuUsageChange();
}











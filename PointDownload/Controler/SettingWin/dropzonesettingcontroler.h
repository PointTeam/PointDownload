#ifndef DROPZONESETTINGCONTROLER_H
#define DROPZONESETTINGCONTROLER_H

#include <QObject>
#include <QQmlEngine>
#include <QtQml>
#include "XMLHandler/settingxmlhandler.h"

class DropzoneSettingControler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int opacity READ getOpacity WRITE setOpacity NOTIFY sOpacityChange)
    Q_PROPERTY(int infoInterval READ getInfoInterval WRITE setInfoInterval NOTIFY sInfoIntervalChange)
    Q_PROPERTY(bool showJobCount READ getShowJobCount WRITE setShowJobCount NOTIFY sShowJobCountChange)
    Q_PROPERTY(bool showCpuUsage READ getShowCpuUsage WRITE setShowCpuUsage NOTIFY sShowCpuUsageChange)
public:
    static DropzoneSettingControler * getInstance();


    int getOpacity();
    int getInfoInterval();
    bool getShowJobCount();
    bool getShowCpuUsage();

    void setOpacity(int opacity);
    void setInfoInterval(int interval);
    void setShowJobCount(bool flag);
    void setShowCpuUsage(bool flag);

signals:
    void sOpacityChange();
    void sInfoIntervalChange();
    void sShowJobCountChange();
    void sShowCpuUsageChange();

private:
    explicit DropzoneSettingControler(QObject *parent = 0);

    void initData();
private:
    int opacity;
    int infoInterval;
    bool showJobCount;
    bool showCpuUsage;

    SettingXMLHandler gHandler;

    static DropzoneSettingControler * dropzoneSettingControler;
};

//将单例对象注册到qml中使用的回调函数
static QObject * dzSettingCtrlObj(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return DropzoneSettingControler::getInstance();
}


#endif // DROPZONESETTINGCONTROLER_H

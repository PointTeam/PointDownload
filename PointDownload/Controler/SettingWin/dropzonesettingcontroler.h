#ifndef DROPZONESETTINGCONTROLER_H
#define DROPZONESETTINGCONTROLER_H

#include <QObject>
#include <QQmlEngine>
#include <QtQml>
#include <QTimer>
#include "settingxmlhandler.h"
#include "Download/unifiedinterface.h"
#include "../middlesender.h"

class DropzoneSettingControler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int opacity READ getOpacity WRITE setOpacity NOTIFY sOpacityChange)
    Q_PROPERTY(int infoInterval READ getInfoInterval WRITE setInfoInterval NOTIFY sInfoIntervalChange)
    Q_PROPERTY(bool showJobCount READ getShowJobCount WRITE setShowJobCount NOTIFY sShowJobCountChange)
    Q_PROPERTY(bool showStorageUsage READ getShowStorageUsage WRITE setShowStorageUsage NOTIFY sShowStorageUsageChange)
    Q_PROPERTY(int winX READ getWinX WRITE setWinX NOTIFY sWinXChange)
    Q_PROPERTY(int winY READ getWinY WRITE setWinY NOTIFY sWinYChange)
public:
    static DropzoneSettingControler * getInstance();
    static QObject * dzSettingCtrlObj(QQmlEngine *engine, QJSEngine *scriptEngine);

    int getOpacity();
    int getInfoInterval();
    bool getShowJobCount();
    bool getShowStorageUsage();
    int getWinX();
    int getWinY();

    void setOpacity(int opacity);
    void setInfoInterval(int interval);
    void setShowJobCount(bool flag);
    void setShowStorageUsage(bool flag);
    void setWinX(int x);
    void setWinY(int y);

signals:
    void sOpacityChange();
    void sInfoIntervalChange();
    void sShowJobCountChange();
    void sShowStorageUsageChange();
    void sWinXChange();
    void sWinYChange();
    void sNewJobCount(int newCount);
    void sNewStorageUsage(double newUsage);

private:
    explicit DropzoneSettingControler(QObject *parent = 0);

    void initData();
    void initTimer();

private slots:
    void slotUpdateJobCount();
    void slotUpdateStorageUsage();
private:
    int opacity;
    int infoInterval;
    bool showJobCount;
    bool showStorageUsage;
    int jobCount;
    double storageUsage;

    int winX;
    int winY;

    SettingXMLHandler gHandler;

    static DropzoneSettingControler * dropzoneSettingControler;

    const int REFRESH_INTERVAL = 1000;
};
#endif // DROPZONESETTINGCONTROLER_H

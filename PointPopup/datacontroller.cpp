#include "datacontroller.h"

DataController * DataController::dataControler = NULL;
DataController * DataController::getInstance()
{
    if (dataControler == NULL)
        dataControler = new DataController();
    return dataControler;
}

DataController::DataController(QObject *parent) : QObject(parent)
{
    //import时使用Singleton.DataController，在获取内容或调用函数时使用PEventFilter
    qmlRegisterSingletonType<DataController>("Singleton.DataController", 1, 0, "DataController", pDataCtrlObj);
}

void DataController::receiveURL(const QString &url)
{
    emit signalReceiveNewURL(url);
}

void DataController::getSupportToolsList(const QString &url)
{
    QList<int> toolsList;
    if (url.isEmpty())
    {
        toolsList.append(PDataType::PToolTypeAria2);
        toolsList.append(PDataType::PToolTypePoint);
        toolsList.append(PDataType::PToolTypeXware);
        toolsList.append(PDataType::PToolTypeYouGet);

        emit signalSupportToolsListChanged(toolsList);
        return;
    }

    URLHandler tmpHandler;

    if (tmpHandler.isYouGetSupportURL(url))
        toolsList.append(PDataType::PToolTypeYouGet);
    else
    {
        if (tmpHandler.isPointSupportURL(url))
            toolsList.append(PDataType::PToolTypePoint);
        if (tmpHandler.isAria2SupportURL(url))
            toolsList.append(PDataType::PToolTypeAria2);
        if (tmpHandler.isXwareSupportURL(url))
            toolsList.append(PDataType::PToolTypeXware);
    }

    if (toolsList.length() == 0)
        toolsList.append(PDataType::PToolTypeUndefined);

    emit signalSupportToolsListChanged(toolsList);
}

void DataController::analyzeURL(const QString &url)
{
    if (url.isEmpty())
        return;

    URLHandler * tmpHandler = new URLHandler();
    connect(tmpHandler, SIGNAL(getFileInfoListDone(QList<TaskFileInfo>)), this, SLOT(analyzeURLDone(QList<TaskFileInfo>)));
    connect(tmpHandler, SIGNAL(getFileInfoListDone(QList<TaskFileInfo>)), tmpHandler, SLOT(deleteLater()));
    tmpHandler->analyzeURL(url);
}

void DataController::analyzeURLDone(QList<TaskFileInfo> infoList)
{
    QVariantMap infoMap;
    for (int i = 0; i < infoList.length(); i ++)
    {
        //fileName,fileType,fileSize
        QVariantList tmpList;
        tmpList << infoList.at(i).fileName << infoList.at(i).fileType << infoList.at(i).fileSize;

        infoMap.insert(QString::number(i),tmpList);
    }
    emit signalFileInfoListChanged(infoMap);
}

QObject *DataController::pDataCtrlObj(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return DataController::getInstance();
}

DataController::~DataController()
{

}


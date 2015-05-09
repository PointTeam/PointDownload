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

    sender = new DataSender(this);
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

    currentUrl = url;

    URLHandler * tmpHandler = new URLHandler();
    connect(tmpHandler, SIGNAL(getFileInfoListDone(QList<TaskFileInfo>)), this, SLOT(analyzeURLDone(QList<TaskFileInfo>)));
    connect(tmpHandler, SIGNAL(getFileInfoListDone(QList<TaskFileInfo>)), tmpHandler, SLOT(deleteLater()));
    tmpHandler->analyzeURL(url);
}

void DataController::startDownload(int threads, int speed, QString savePath, int toolType)
{
    QString fileID = getFileIdFromFileName();

    if (isDownloading(fileID))
    {
        return;//no need to do anything
    }
    else if (isDownloaded(fileID))
    {
        //delete xml item
        QFile::remove(gDownloadHandler.getDLedNode(fileID).fileSavePath + "/"
                      + gDownloadHandler.getDLedNode(fileID).fileName);
        gDownloadHandler.removeDLedFileNode(fileID);
    }
    else if (isTrash(fileID))
    {
        gDownloadHandler.removeDLtrashFileNode(fileID);
    }

    TaskInfo taskInfo;
    taskInfo.fileID = fileID;
    taskInfo.toolType = PDataType::ToolType(toolType);
    taskInfo.fileList = currentFileList;
    taskInfo.url = currentUrl;
    taskInfo.taskIconPath = "";
    taskInfo.fileSavePath = savePath;
    taskInfo.maxThreads = threads;
    taskInfo.maxSpeed = speed;

    sender->startDownload(taskInfo);
}

void DataController::analyzeURLDone(QList<TaskFileInfo> infoList)
{
    currentFileList = infoList;

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

QString DataController::getFileIdFromFileName()
{
    QString idStr = "";
    for (int i = 0; i < currentFileList.count(); i ++)
    {
        idStr += currentFileList.at(i).fileName;
    }
    return QString(idStr.toUtf8().toBase64());
}

bool DataController::isDownloading(const QString &fileID)
{
    QList<SDownloading> tmpList = gDownloadHandler.getDLingNodes();

    for (int i = 0; i < tmpList.count(); i ++)
    {
        //if exit,when user click ok button ,this window will just close and do nothing
        if (tmpList.at(i).fileID == fileID)
        {
            return true;
        }
    }

    return false;//at the end got nothing will return false
}

bool DataController::isDownloaded(const QString &fileID)
{
    QList<SDownloaded> tmpList = gDownloadHandler.getDLedNodes();

    for (int i = 0; i < tmpList.count(); i ++)
    {
        if (tmpList.at(i).fileID == fileID)
        {
            return true;
        }
    }

    return false;//at the end got nothing will return false
}

bool DataController::isTrash(const QString &fileID)
{
    QList<SDownloadTrash> tmpList = gDownloadHandler.getDLtrashNodes();

    for (int i = 0; i < tmpList.count(); i ++)
    {
        if (tmpList.at(i).fileID == fileID)
        {
            return true;
        }
    }

    return false;//at the end got nothing will return false
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


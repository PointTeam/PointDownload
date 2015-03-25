#include "maincontroller.h"
#include <QtQml>

MainController * MainController::mainController = NULL;
MainController * MainController::getInstance()
{
    //import时使用Singleton.MainController
    qmlRegisterSingletonType<MainController>("Singleton.MainController", 1, 0, "MainController", dataObj);

    if (mainController == NULL)
    {
        mainController = new MainController();
    }
    return mainController;
}

QObject * MainController::dataObj(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return MainController::getInstance();
}

void MainController::pStartDownload(const TaskInfo &taskInfo)
{
    //确保将要下载的文件不会重复
    deleteFileFromDisk(taskInfo.savePath, taskInfo.fileList.at(0).fileName);

//    //弹出窗口才使用这个接口，每次新建连接前要先检查是否达到最大限制
//    SettingXMLHandler tmphandler;
//    if (tmphandler.getChildElement(GeneralSettings,"MaxJobCount").toInt() <= downloadingListMap.count())
//    {
//        //移除最慢的一项
//        dropSlowest();
//    }

    //将下载项插入全局map中
    taskListMap.insert(taskInfo.fileID, taskInfo.toolType);

    switch (taskInfo.toolType)
    {
    case PDataType::PToolTypePoint:
        startPointDownload(taskInfo);
        break;
    case PDataType::PToolTypeAria2:
        startAria2Download(taskInfo);
        break;
    case PDataType::PToolTypeYouGet:
        startYougetDownload(taskInfo);
        break;
    case PDataType::PToolTypeXware:
        startXwareDownload(taskInfo);
        break;
    default:
        qWarning() << "taskInfo.toolType not defined! At: void UnifiedInterface::startDownload(const TaskInfo &taskInfo)";
    }

    TaskInfo tmpInfo = taskInfo;
    emit signalAddDownloadingItem(&tmpInfo);
}

void MainController::pChangeMaxJobCount(int newCount)
{

}

int MainController::pGetJobCount()
{

}

void MainController::pSuspendAllTask()
{
    qDebug() << "All job spspened!";
}

void MainController::pResumeAllTask()
{

}

void MainController::slotControlFileItem(QString &fileID, PDataType::DownloadType dtype, PDataType::OperationType otype)
{

}

void MainController::slotGetError(QString &fileID, QString &errorMessage, PDataType::ToolType toolType)
{

}

void MainController::initDownloadList()
{

}

void MainController::initDownloadingStart()
{

}

MainController::MainController(QObject *parent) : QObject(parent)
{

}

MainController::~MainController()
{

}

void MainController::startPointDownload(const TaskInfo &taskInfo)
{

}

void MainController::startYougetDownload(const TaskInfo &taskInfo)
{

}

void MainController::startAria2Download(const TaskInfo &taskInfo)
{

}

void MainController::startXwareDownload(const TaskInfo &taskInfo)
{

}

void MainController::handleDownloadingControl(const QString &fileID, PDataType::OperationType otype)
{

}

void MainController::handleDownloadedControl(const QString &fileID, PDataType::OperationType otype)
{

}

void MainController::handleDownloadTrashControl(const QString &fileID, PDataType::OperationType otype)
{

}

void MainController::dlingDelete(const QString &fileID)
{

}

void MainController::dlingFinish(const QString &fileID)
{

}

void MainController::dlingHightSpeedChannel(const QString &fileID)
{

}

void MainController::dlingOfflineDownload(const QString &fileID)
{

}

void MainController::dlingOpenFolder(const QString &fileID)
{

}

void MainController::dlingRaise(const QString &fileID)
{

}

void MainController::dlingResume(const QString &fileID)
{

}

void MainController::dlingStop(const QString &fileID)
{

}

void MainController::dlingSuspend(const QString &fileID)
{

}

void MainController::dlingTrash(const QString &fileID)
{

}

void MainController::dledDelete(const QString &fileID)
{

}

void MainController::dledOpenFolder(const QString &fileID)
{

}

void MainController::dledRedownload(const QString &fileID)
{

}

void MainController::dledTrash(const QString &fileID)
{

}

void MainController::dltrashDelete(const QString &fileID)
{

}

void MainController::dltrashRedownload(const QString &fileID)
{

}

void MainController::initDLedList()
{

}

void MainController::initDLingList()
{

}

void MainController::initDLtrashList()
{

}

void MainController::deleteFileFromDisk(QString path, QString fileName)
{

}




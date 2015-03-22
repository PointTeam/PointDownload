#include "maincontroller.h"

MainController * MainController::mainController = NULL;
MainController * MainController::getInstance()
{
    if (mainController == NULL)
    {
        mainController = new MainController();
    }
    return mainController;
}

void MainController::pStartDownload(const TaskInfo &taskInfo)
{

}

void MainController::pChangeMaxJobCount(int newCount)
{

}

int MainController::pGetJobCount()
{

}

void MainController::pSuspendAllTask()
{

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




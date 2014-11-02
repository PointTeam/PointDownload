/***********************************************************************
*PointDownload
*Copyright (C) 2014  PointTeam
*
* Author:     Match <2696627729@qq.com>
* Maintainer: Match <2696627729@qq.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************/

#include "unifiedinterface.h"

UnifiedInterface::UnifiedInterface(QObject *parent) :
    QObject(parent)
{
    QTimer::singleShot(500, this, SLOT(initDownloadList()));
    QTimer::singleShot(501, this, SLOT(initDownloadingStart()));
}

UnifiedInterface * UnifiedInterface::unifiedInterface = NULL;
UnifiedInterface * UnifiedInterface::getInstance()
{
    if (unifiedInterface == NULL)
    {
        unifiedInterface = new UnifiedInterface();
    }
    return unifiedInterface;
}

void UnifiedInterface::getPrepareDownloadInfo(PrepareDownloadInfo info)
{
    NormalNotice::getInstance()->showMessage(tr("New Task"), info.fileName);
    //确保将要下载的文件不会重复
    deleteFileFromDisk(info.storageDir, info.fileName);

    //弹出窗口才使用这个接口，每次新建连接前要先检查是否达到最大限制
    SettingXMLHandler tmphandler;
    if (tmphandler.getChildElement(GeneralSettings,"MaxJobCount").toInt() <= downloadingListMap.count())
    {
        //移除最慢的一项
        dropSlowest();
    }

    //将下载项插入全局map中
    downloadingListMap.insert(info.downloadURL,info.toolType);

    switch (info.toolType)
    {
    case Point:
        startPointDownload(info);
        break;
    case aria2:
        startAria2Download(info);
        break;
    case youget:
        startYougetDownload(info);
        break;
    case Xware:
        startXwareDownload(info);
        break;
    default:
        break;
    }

    refreshDownloadingItem();
}

void UnifiedInterface::cleanDownloadFinishItem(QString dlURL)
{
    //向已下载xml记录文件插入新项
    DownloadXMLHandler tmpOpera;

    SDownloading ingStruct = tmpOpera.getDownloadingNode(dlURL);
    SDownloaded edStruct;
    QDateTime current_date_time = QDateTime::currentDateTime();
    edStruct.completeDate = current_date_time.toString( "yyyy:MM:dd:hh:mm" );
    edStruct.dlToolsType = ingStruct.dlToolsType;
    edStruct.exist = "true";
    edStruct.iconPath = ingStruct.iconPath;
    edStruct.name = ingStruct.name;
    edStruct.savePath = ingStruct.savePath;
    edStruct.Size = ingStruct.totalSize;
    edStruct.URL = ingStruct.URL;

    if (edStruct.name != "")
        tmpOpera.insertDownloadedNode(edStruct);

    //删除正在下载的项
    tmpOpera.removeDownloadingFileNode(dlURL);

    downloadingListMap.remove(dlURL);
    //取出一个合适的项进行下载
    startReady();

    refreshDownloadingItem();

    //统计流量
    QString day = current_date_time.toString("dddd");
    DataFlow::addData(day,edStruct.Size);


    //完成提示消息
    NormalNotice::getInstance()->showMessage(tr("Finish Download"), Notice_Color_Success, edStruct.name);

    //完成提示音
    SettingXMLHandler tmpHandler;
    if(tmpHandler.getChildElement(GeneralSettings,"AlertTone") == "Enable")
        QSound::play(":/tone/resources/Tone/complete.wav");
}

void UnifiedInterface::changeMaxJobCount(int newCount)
{
    DownloadXMLHandler tmpOpera;
    int ingItemCount = tmpOpera.getDownloadingNodes().count();

    while (newCount < downloadingListMap.count())
    {
        dropSlowest();
    }

    while (newCount > downloadingListMap.count() && downloadingListMap.count() < ingItemCount)
    {
        startReady();
    }

    refreshDownloadingItem();
}

void UnifiedInterface::suspendAllDownloading()
{
    QList<QString> keys = downloadingListMap.keys();
    for (int i = 0; i < keys.count(); i++)
    {
        suspendDownloading(keys.at(i));
    }
}

void UnifiedInterface::resumeAllDownloading()
{
    QList<QString> keys = downloadingListMap.keys();
    for (int i = 0; i < keys.count(); i++)
    {
        resumeDownloading(keys.at(i));
    }
}

int UnifiedInterface::getJobCount()
{
    return downloadingListMap.count();
}

void UnifiedInterface::controlDownload(DownloadType dtype, OperationType otype, QString URL)
{
    switch (dtype)
    {
    case dl_downloading:
        handleDownloadingControl(otype,URL);
        break;
    case dl_downloaded:
        handleDownloadedControl(otype, URL);
        break;
    case dl_trash:
        handleDownloadTrashControl(otype, URL);
        break;
    case dl_search:
        handleDownloadSearchControl(URL);
        break;
    default:
        break;
    }
}

void UnifiedInterface::downloadFinish(QString URL)
{
    Q_UNUSED(URL);
}

void UnifiedInterface::downloadGetError(QString URL,QString err, DownloadToolsType toolType)
{
    NormalNotice::getInstance()->showMessage(tr("Download Error"), Notice_Color_Error, QString(URL + ":\n" + err));
}

void UnifiedInterface::startPointDownload(PrepareDownloadInfo info)
{
    //启动下载
    PointTask::getInstance()->startDownload(info);
}

void UnifiedInterface::startAria2Download(PrepareDownloadInfo info)
{
    DownloadXMLHandler tmpOpera;

    if (!tmpOpera.urlExit(info.downloadURL,"ing"))
    {
        SDownloadThread threadStruct;
        threadStruct.startBlockIndex = "1";
        threadStruct.endBlockIndex = "1";
        threadStruct.completedBlockCount = "1";
        QList<SDownloadThread> tmpList;

        int threadCount = info.threadCount.toInt();
        for (int i = 0; i < threadCount; i ++)
            tmpList.append(threadStruct);

        //插入xml文件
        SDownloading tmpIngStruct;

        tmpIngStruct.dlToolsType = "aria2";
        tmpIngStruct.name = info.fileName;
        tmpIngStruct.jobMaxSpeed = info.maxSpeed;
        tmpIngStruct.savePath = info.storageDir;
        tmpIngStruct.enableUpload = "false";
        tmpIngStruct.URL = info.downloadURL;
        tmpIngStruct.redirectRUL = info.redirectURl;
        tmpIngStruct.blockCount = "1";
        tmpIngStruct.blockSize = "1";
        tmpIngStruct.totalSize = info.fileSize;
        tmpIngStruct.readySize = "0";
        tmpIngStruct.autoOpenFolder = "false";
        tmpIngStruct.state = "dlstate_downloading";
        tmpIngStruct.averageSpeed = "0";
        tmpIngStruct.iconPath = info.iconPath;
        tmpIngStruct.threadList = tmpList;

        tmpOpera.insertDownloadingNode(tmpIngStruct);
    }
    else
    {
        //必须要及时改变状态
        DownloadXMLHandler tmpOpera;
        SDownloading tmpStruct;
        tmpStruct.URL = info.downloadURL;
        tmpStruct.state = "dlstate_downloading";

        tmpOpera.writeDownloadingConfigFile(tmpStruct);
    }


    //启动下载
    Aria2Task::getInstance()->startDownload(info);

}

void UnifiedInterface::startYougetDownload(PrepareDownloadInfo info)
{
    DownloadXMLHandler tmpOpera;

    if (!tmpOpera.urlExit(info.downloadURL,"ing"))
    {
        SDownloadThread threadStruct;
        threadStruct.startBlockIndex = "1";
        threadStruct.endBlockIndex = "1";
        threadStruct.completedBlockCount = "1";
        QList<SDownloadThread> tmpList;
        tmpList.append(threadStruct);

        //插入xml文件
        SDownloading tmpIngStruct;

        tmpIngStruct.dlToolsType = "youget";
        tmpIngStruct.name = info.fileName;
        tmpIngStruct.jobMaxSpeed = "0";   //you-get无法控制网速
        tmpIngStruct.savePath = info.storageDir;
        tmpIngStruct.enableUpload = "false";
        tmpIngStruct.URL = info.downloadURL;
        tmpIngStruct.redirectRUL = info.redirectURl;
        tmpIngStruct.blockCount = "1";
        tmpIngStruct.blockSize = "1";
        tmpIngStruct.totalSize = info.fileSize;
        tmpIngStruct.readySize = "0";
        tmpIngStruct.autoOpenFolder = "false";
        tmpIngStruct.state = "dlstate_downloading";
        tmpIngStruct.averageSpeed = "0";
        tmpIngStruct.iconPath = info.iconPath;
        tmpIngStruct.threadList = tmpList;

        tmpOpera.insertDownloadingNode(tmpIngStruct);
    }
    else
    {
        //必须要及时改变状态
        DownloadXMLHandler tmpOpera;
        SDownloading tmpStruct;
        tmpStruct.URL = info.downloadURL;
        tmpStruct.state = "dlstate_downloading";

        tmpOpera.writeDownloadingConfigFile(tmpStruct);
    }


    //启动下载
    YouGetTask::getInstance()->startDownload(info);
}

void UnifiedInterface::startXwareDownload(PrepareDownloadInfo info)
{
    DownloadXMLHandler tmpOpera;
    SDownloadThread threadStruct;
    threadStruct.startBlockIndex = "1";
    threadStruct.endBlockIndex = "1";
    threadStruct.completedBlockCount = "1";
    QList<SDownloadThread> tmpList;
    tmpList.append(threadStruct);

    if (!tmpOpera.urlExit(info.downloadURL,"ing"))
    {
        //插入xml文件
        SDownloading tmpIngStruct;

        tmpIngStruct.dlToolsType = "xware";
        tmpIngStruct.name = info.fileName;
        tmpIngStruct.jobMaxSpeed = "0";   // xware 暂时不作网速控制
        tmpIngStruct.savePath = info.storageDir;
        tmpIngStruct.enableUpload = "false";
        tmpIngStruct.URL = info.downloadURL;
        tmpIngStruct.redirectRUL = info.redirectURl;
        tmpIngStruct.blockCount = "1";
        tmpIngStruct.blockSize = "1";
        tmpIngStruct.totalSize = info.fileSize;
        tmpIngStruct.readySize = "0";
        tmpIngStruct.autoOpenFolder = "false";
        tmpIngStruct.state = "dlstate_downloading";
        tmpIngStruct.averageSpeed = "0";
        tmpIngStruct.iconPath = info.iconPath;
        tmpIngStruct.threadList = tmpList;

        tmpOpera.insertDownloadingNode(tmpIngStruct);
    }
    else
    {
        //必须要及时改变状态
        DownloadXMLHandler tmpOpera;
        SDownloading tmpStruct;
        tmpStruct.URL = info.downloadURL;
        tmpStruct.state = "dlstate_downloading";

        tmpOpera.writeDownloadingConfigFile(tmpStruct);
    }


    qDebug()<<"xware add new download";


    //启动下载
    XwareTask::getInstance()->addNewDownload(info);
}


void UnifiedInterface::handleDownloadingControl(OperationType otype, QString URL)
{
    switch(otype)
    {
    case download_suspend:
        suspendDownloading(URL);
        break;
    case download_priority:
        priorityDownloading(URL);
        break;
    case download_resume:
        resumeDownloading(URL);
        break;
    case download_openFolder:
        openFolderDownloading(URL);
        break;
    case download_trash:
        trashDownloading(URL);
        break;
    case download_delete:
        deleteDownloading(URL);
        break;
    case download_offlineDownload:
        offlineDownloadDownloading(URL);
        break;
    case download_hightSpeedChannel:
        hightSpeedChannelDownloading(URL);
        break;
    case download_finishDownload:
        finishDownloading(URL);
        break;
    default:
        break;
    }
}

void UnifiedInterface::handleDownloadedControl(OperationType otype, QString URL)
{
    switch(otype)
    {
    case download_redownload:
        redownloadDownloaded(URL);
        break;
    case download_openFolder:
        openFolderDownloaded(URL);
        break;
    case download_trash:
        trashDownloaded(URL);
        break;
    case download_delete:
        deleteDownloaded(URL);
        break;
    default:
        break;
    }
}

void UnifiedInterface::handleDownloadTrashControl(OperationType otype, QString URL)
{
    switch(otype)
    {
    case download_redownload:
        redownloadTrash(URL);
        break;
    case download_delete:
        deleteTrash(URL);
        break;
    default:
        break;
    }
}

void UnifiedInterface::handleDownloadSearchControl(QString URL)
{
    QStringList arguments;
    arguments << QString(URL + "#..#FIREFOX");//仿照firefox格式发送数据

    qDebug() << POPUP_PROGRAM_PATH << arguments;

    QProcess *myProcess = new QProcess(0);
    myProcess->start(POPUP_PROGRAM_PATH,arguments);
}


void UnifiedInterface::stopDownloading(QString URL)
{
    switch(downloadingListMap.value(URL))
    {
    case youget:
        YouGetTask::getInstance()->stopDownload(URL);
        break;
    case Point:
        PointTask::getInstance()->stopDownload(URL);
        break;
    case Xware:
        XwareTask::getInstance()->stopDownload(URL);
        break;
    default:
        break;
    }

    downloadingListMap.remove(URL);
    refreshDownloadingItem();
}

void UnifiedInterface::suspendDownloading(QString URL)
{
    DownloadXMLHandler tmpOpera;
//    //如果已经处于暂停状态则不作处理
//    if (tmpOpera.getDownloadingNode(URL).state == "dlstate_suspend")
//        return;

    //在xml文件中将该项标注为暂停
    SDownloading tmpStruct;
    tmpStruct.URL = URL;
    tmpStruct.state = "dlstate_suspend";
    tmpOpera.writeDownloadingConfigFile(tmpStruct);

    switch(downloadingListMap.value(URL))
    {
    case youget:
        YouGetTask::getInstance()->suspendDownloading(URL);
        break;
    case Point:
        PointTask::getInstance()->suspendDownloading(URL);
        break;
    case Xware:
        if(XWARE_CONSTANTS_STRUCT.DEBUG)
            qDebug()<<" xxxxxxx UnifiedInterface  suspend  xxxxxxx";
        XwareTask::getInstance()->suspendDownloading(URL);
        break;
    default:
        break;
    }

    refreshDownloadingItem();
}

void UnifiedInterface::resumeDownloading(QString URL)
{
    SettingXMLHandler tmpHandler;
    DownloadXMLHandler downloadHandler;
    //如果已经处于下载状态则不作处理
//    if (downloadHandler.getDownloadingNode(URL).state == "dlstate_downloading")
//        return;

    //如果数量超出了最大限制,则把正在下载的最慢的项停下
    if (tmpHandler.getChildElement(GeneralSettings,"MaxJobCount").toInt() <= downloadingListMap.count())
    {
        dropSlowest();
    }

    //在xml文件中将该项标注为正在下载
    SDownloading tmpStruct;
    tmpStruct.URL = URL;
    tmpStruct.state = "dlstate_downloading";
    downloadHandler.writeDownloadingConfigFile(tmpStruct);

    QString tmpToolType = downloadHandler.getDownloadingNode(URL).dlToolsType;
    if (tmpToolType == "xware")
        downloadingListMap.insert(URL, Xware);
    else if (tmpToolType == "aria2")
        downloadingListMap.insert(URL, aria2);
    else if (tmpToolType == "youget")
        downloadingListMap.insert(URL, youget);
    else
        downloadingListMap.insert(URL, Point);

    switch(downloadingListMap.value(URL))
    {
    case aria2:
        Aria2Task::getInstance()->resumeDownloading(URL);
        break;
    case youget:
        YouGetTask::getInstance()->resumeDownloading(URL);
        break;
    case Point:
        PointTask::getInstance()->resumeDownloading(URL);
        break;
    case Xware:
        if(XWARE_CONSTANTS_STRUCT.DEBUG)
            qDebug()<<"xxxxxxx UnifiedInterface resume  xxxxxxx";
        XwareTask::getInstance()->resumeDownloading(URL);
        break;
    default:
        break;
    }

    refreshDownloadingItem();
}

void UnifiedInterface::priorityDownloading(QString URL)
{
    if (downloadingListMap.contains(URL))
    {
        //如果存在于正在下载的列表中,则重新恢复下载
//        dropSlowest();
        resumeDownloading(URL);
    }
    else
    {
        //否则启动一个就绪队列的项
        dropSlowest();
        DownloadXMLHandler tmpOpera;
        QString toolType = tmpOpera.getDownloadingNode(URL).dlToolsType;

        stopDownloading(URL);

        if (toolType == "Point")
        {
            startPointDownload(getPrepareInfoFromSDownloading(tmpOpera.getDownloadingNode(URL)));
        }

        else if (toolType == "aria2")
        {
            startAria2Download(getPrepareInfoFromSDownloading(tmpOpera.getDownloadingNode(URL)));
        }

        // added by choldrim , not sure
        else if (toolType == "Xware")
        {
            startXwareDownload(getPrepareInfoFromSDownloading(tmpOpera.getDownloadingNode(URL)));
        }

        else
            startYougetDownload(getPrepareInfoFromSDownloading(tmpOpera.getDownloadingNode(URL)));
    }

    refreshDownloadingItem();
}

void UnifiedInterface::openFolderDownloading(QString URL)
{
    DownloadXMLHandler tmpOpera;
    QString tmpPath = tmpOpera.getDownloadingNode(URL).savePath;

    if (tmpPath != "")
        QDesktopServices::openUrl(QUrl::fromLocalFile(tmpPath));
}

void UnifiedInterface::trashDownloading(QString URL)
{
    DownloadXMLHandler tmpOpera;
    SDownloading tmpIngStruct;
    SDownloadTrash tmpTrashStruct;

    tmpIngStruct = tmpOpera.getDownloadingNode(URL);
    tmpTrashStruct.dlToolsType = tmpIngStruct.dlToolsType;
    tmpTrashStruct.URL = tmpIngStruct.URL;
    tmpTrashStruct.name = tmpIngStruct.name;
    tmpTrashStruct.totalSize = tmpIngStruct.totalSize;
    tmpTrashStruct.iconPath = tmpIngStruct.iconPath;

    tmpOpera.insertDownloadTrash(tmpTrashStruct);//往垃圾箱XMl文件新增项
    stopDownloading(URL);                                               //停止下载
    deleteFileFromDisk(tmpOpera.getDownloadingNode(URL).savePath,tmpOpera.getDownloadingNode(URL).name);
    tmpOpera.removeDownloadingFileNode(URL);// 从XML文件中移除


    if (tmpTrashStruct.dlToolsType == "xware" || tmpTrashStruct.dlToolsType == "Xware")
        XwareTask::getInstance()->removeDownloading(URL);

    emit sReturnControlResult(dl_downloading,download_trash,URL,true);

    startReady();
    refreshDownloadingItem();
}

void UnifiedInterface::deleteDownloading(QString URL)
{
    DownloadXMLHandler tmpOpera;
    stopDownloading(URL);
    deleteFileFromDisk(tmpOpera.getDownloadingNode(URL).savePath,tmpOpera.getDownloadingNode(URL).name);
    tmpOpera.removeDownloadingFileNode(URL);


    XwareTask::getInstance()->removeDownloading(URL);

    emit sReturnControlResult(dl_downloading,download_delete,URL,true);

    startReady();
    refreshDownloadingItem();
}

void UnifiedInterface::offlineDownloadDownloading(QString URL)
{
    XwareTask::getInstance()->entryOfflineChannel(URL);
}

void UnifiedInterface::hightSpeedChannelDownloading(QString URL)
{
    XwareTask::getInstance()->entryHighSpeedChannel(URL);
}

void UnifiedInterface::finishDownloading(QString URL)
{
    //向已下载xml记录文件插入新项
    DownloadXMLHandler tmpOpera;

    SDownloading ingStruct = tmpOpera.getDownloadingNode(URL);
    SDownloaded edStruct;
    QDateTime current_date_time = QDateTime::currentDateTime();
    edStruct.completeDate = current_date_time.toString( "yyyy:MM:dd:hh:mm" );
    edStruct.dlToolsType = ingStruct.dlToolsType;
    edStruct.exist = "true";
    edStruct.iconPath = ingStruct.iconPath;
    edStruct.name = ingStruct.name;
    edStruct.savePath = ingStruct.savePath;
    edStruct.Size = ingStruct.totalSize;
    edStruct.URL = ingStruct.URL;

    if (edStruct.name != "")
        tmpOpera.insertDownloadedNode(edStruct);

    //删除正在下载的项
    tmpOpera.removeDownloadingFileNode(URL);

    downloadingListMap.remove(URL);
    //取出一个合适的项进行下载
    startReady();

    refreshDownloadingItem();

    //统计流量
    QString day = current_date_time.toString("dddd");
    DataFlow::addData(day,edStruct.Size);
}


void UnifiedInterface::redownloadDownloaded(QString URL)
{
    handleDownloadSearchControl(URL);
    //当用户确定要下载后，由界面调用相关函数删除文件
}

void UnifiedInterface::openFolderDownloaded(QString URL)
{
    DownloadXMLHandler tmpOpera;
    QString tmpPath = tmpOpera.getDownloadedNode(URL).savePath;

    if (tmpPath != "")
        QDesktopServices::openUrl(QUrl::fromLocalFile(tmpPath));
}

void UnifiedInterface::trashDownloaded(QString URL)
{
    DownloadXMLHandler tmpOpera;
    SDownloaded tmpEdStruct;
    SDownloadTrash tmpTrashStruct;

    tmpEdStruct = tmpOpera.getDownloadedNode(URL);
    tmpTrashStruct.dlToolsType = tmpEdStruct.dlToolsType;
    tmpTrashStruct.URL = tmpEdStruct.URL;
    tmpTrashStruct.name = tmpEdStruct.name;
    tmpTrashStruct.totalSize = tmpEdStruct.Size;
    tmpTrashStruct.iconPath = tmpEdStruct.iconPath;

    tmpOpera.insertDownloadTrash(tmpTrashStruct);//往垃圾箱XMl文件新增项
    deleteFileFromDisk(tmpOpera.getDownloadedNode(URL).savePath,tmpOpera.getDownloadedNode(URL).name);
    tmpOpera.removeDownloadedFileNode(URL);// 从XML文件中移除

    emit sReturnControlResult(dl_downloaded,download_trash,URL,true);
}

void UnifiedInterface::deleteDownloaded(QString URL)
{
    DownloadXMLHandler tmpOpera;
    deleteFileFromDisk(tmpOpera.getDownloadedNode(URL).savePath,tmpOpera.getDownloadedNode(URL).name);
    tmpOpera.removeDownloadedFileNode(URL);// 把待删除项从XML文件中移除

    emit sReturnControlResult(dl_downloaded,download_delete,URL,true);
}

void UnifiedInterface::redownloadTrash(QString URL)
{
    handleDownloadSearchControl(URL);
    //当用户确定要下载后，由界面调用相关函数删除文件
}

void UnifiedInterface::deleteTrash(QString URL)
{
    DownloadXMLHandler tmpOpera;
    tmpOpera.removeDownloadTrashFileNode(URL);// 把待删除项从XML文件中移除

    emit sReturnControlResult(dl_trash,download_delete,URL,true);
}

void UnifiedInterface::initDownloadList()
{
    initDownloadedList();
    initdownloadingList();
    initTrashList();
}

void UnifiedInterface::initDownloadedList()
{
    DownloadXMLHandler tmpOpera;
    QList<SDownloaded> edList = tmpOpera.getDownloadedNodes();
    for (int i = 0;i < edList.count(); i++)
    {
        //infoList: dlToolsType?:?fileName?:?URL?:?iconName?:?fileSize?:?completeDate
        QString info =  edList.at(i).dlToolsType + "?:?"
                + edList.at(i).name + "?:?"
                + edList.at(i).URL + "?:?"
                + edList.at(i).iconPath + "?:?"
                + edList.at(i).Size + "?:?"
                + edList.at(i).completeDate;

        emit sAddDownloadedItem(info);
    }
}

void UnifiedInterface::initdownloadingList()
{
    DownloadXMLHandler tmpOpera;
    QList<SDownloading> ingList = tmpOpera.getDownloadingNodes();

    for (int i = 0;i < ingList.count(); i++)
    {
        qint64 totalSize = ingList.at(i).totalSize.toLongLong();
        qint64 readySize = ingList.at(i).readySize.toLongLong();
        double percentage = 0;
        if (totalSize != 0)
            percentage =100 *  readySize / (double)totalSize;

        QString info =  ingList.at(i).dlToolsType + "?:?"
                + ingList.at(i).name + "?:?"
                + ingList.at(i).URL + "?:?"
                + ingList.at(i).redirectRUL + "?:?"
                + ingList.at(i).iconPath + "?:?"
                + ingList.at(i).totalSize + "?:?"
                + ingList.at(i).savePath + "?:?"
                + QString::number(ingList.at(i).threadList.count()) + "?:?"
                + ingList.at(i).jobMaxSpeed + "?:?"
                + QString::number(percentage,'f',1) + "?:?" // ready percentage
                + ingList.at(i).state;
        emit sAddDownloadingItem(info);

        DownloadToolsType dlToolsType;
        if (ingList.at(i).dlToolsType == "Point")
            dlToolsType = Point;
        else if (ingList.at(i).dlToolsType == "aria2")
            dlToolsType = aria2;

        // added by choldrim , not sure
        else if (ingList.at(i).dlToolsType == "xware")
            dlToolsType = Xware;

        else
            dlToolsType = youget;

        if (ingList.at(i).state == "dlstate_downloading")
        {
            downloadingListMap.insert(ingList.at(i).URL, dlToolsType);  //只添加到下载列表，暂时不下载
        }
    }
}

void UnifiedInterface::initTrashList()
{
    DownloadXMLHandler tmpOpera;
    QList<SDownloadTrash> trashList = tmpOpera.getDownloadTrashNodes();
    for (int i = 0;i < trashList.count(); i++)
    {
        //infoList: dlToolsType?:?fileName?:?URL?:?iconName?:?fileSize
        QString info = trashList.at(i).dlToolsType + "?:?"
                + trashList.at(i).name + "?:?"
                + trashList.at(i).URL + "?:?"
                + trashList.at(i).iconPath + "?:?"
                + trashList.at(i).totalSize;

        emit sAddDownloadTrashItem(info);
    }
}

void UnifiedInterface::initDownloadingStart()
{
    SettingXMLHandler tmpHandler;
    DownloadXMLHandler downloadHandler;
    QList<QString> keys = downloadingListMap.keys();
    int jobs = 0;
    for (int i = 0; i < keys.count(); i++)
    {
        if (tmpHandler.getChildElement(GeneralSettings,"MaxJobCount").toInt() < jobs)
            break;
        SDownloading ingNode = downloadHandler.getDownloadingNode(keys.at(i));

        if (ingNode.state == "dlstate_downloading")
        {
            jobs ++;

            SDownloading tmpStruct;
            tmpStruct.URL = keys.at(i);
            tmpStruct.state = "dlstate_suspend";

            DownloadXMLHandler xmlOpera;
            xmlOpera.writeDownloadingConfigFile(tmpStruct);

            resumeDownloading(keys.at(i));
        }
    }

    refreshDownloadingItem();
}

void UnifiedInterface::deleteFileFromDisk(QString path, QString fileName)
{
    QDir tmpDir(path);
    tmpDir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    tmpDir.setSorting(QDir::Size | QDir::Reversed);

    QFileInfoList fileNameList = tmpDir.entryInfoList();
    for (int i = 0; i < fileNameList.size(); ++i)
    {
        QFileInfo fileInfo = fileNameList.at(i);
        if (fileInfo.fileName().contains(fileName))
        {
            QFile::remove(path + "/" + fileInfo.fileName());
        }
    }
}

void UnifiedInterface::dropSlowest()
{
    if (downloadingListMap.count() > 0)
    {
        DownloadXMLHandler tmpOpera;
        QList<QString> keysList = downloadingListMap.keys();
        QString minURL = downloadingListMap.firstKey();
        qint64 tmpNum = tmpOpera.getDownloadingNode(downloadingListMap.firstKey()).averageSpeed.toLongLong();
        for (int i = 0; i < downloadingListMap.count(); i ++)
        {
            qint64 averageNum = tmpOpera.getDownloadingNode(keysList.at(i)).averageSpeed.toLongLong();
            if (averageNum < tmpNum)
            {
                tmpNum = averageNum;
                minURL = keysList.at(i);
            }
        }

        //终止最慢的项
        SDownloading tmpStruct;
        tmpStruct.URL = minURL;
        tmpStruct.state = "dlstate_ready";
        tmpOpera.writeDownloadingConfigFile(tmpStruct);

        stopDownloading(minURL);
    }
}

void UnifiedInterface::startReady()
{
    //下载项的xml文件中的下载状态会在定时更新xml文件时更新为正在下载
    SettingXMLHandler tmpHandler;
    DownloadXMLHandler downloadHandler;

    if (downloadingListMap.count() >= tmpHandler.getChildElement(GeneralSettings,"MaxJobCount").toInt())
        return;

    QList<SDownloading> ingList = downloadHandler.getDownloadingNodes();

    for (int i =0; i < ingList.count(); i ++)
    {
        if (ingList.at(i).state == "dlstate_ready")
        {
            if (ingList.at(i).dlToolsType == "Point")
            {
                downloadingListMap.insert(ingList.at(i).URL, Point);
                startPointDownload(getPrepareInfoFromSDownloading(ingList.at(i)));
            }
            else if (ingList.at(i).dlToolsType == "aria2")
            {
                downloadingListMap.insert(ingList.at(i).URL, aria2);
                startAria2Download(getPrepareInfoFromSDownloading(ingList.at(i)));
            }

            // added by choldrim , not sure
            else if (ingList.at(i).dlToolsType == "Xware")
            {
                downloadingListMap.insert(ingList.at(i).URL, Xware);
                startXwareDownload(getPrepareInfoFromSDownloading(ingList.at(i)));
            }

            else if (ingList.at(i).dlToolsType == "youget")
            {
                downloadingListMap.insert(ingList.at(i).URL, youget);
                startYougetDownload(getPrepareInfoFromSDownloading(ingList.at(i)));
            }

            return;
        }
    }

    //如果ready队列已经没有项，则启用suspend队列的项
    for (int i =0; i < ingList.count(); i ++)
    {
        if (ingList.at(i).state == "dlstate_suspend")
        {
            if (ingList.at(i).dlToolsType == "Point")
            {
                downloadingListMap.insert(ingList.at(i).URL, Point);
                startPointDownload(getPrepareInfoFromSDownloading(ingList.at(i)));
            }
            else if (ingList.at(i).dlToolsType == "aria2")
            {
                downloadingListMap.insert(ingList.at(i).URL, aria2);
                startAria2Download(getPrepareInfoFromSDownloading(ingList.at(i)));
            }

            // added by choldrim , not sure
            else if (ingList.at(i).dlToolsType == "Xware")
            {
                downloadingListMap.insert(ingList.at(i).URL, Xware);
                startXwareDownload(getPrepareInfoFromSDownloading(ingList.at(i)));
            }

            else if (ingList.at(i).dlToolsType == "youget")
            {
                downloadingListMap.insert(ingList.at(i).URL, youget);
                startYougetDownload(getPrepareInfoFromSDownloading(ingList.at(i)));
            }
        }
    }

}

void UnifiedInterface::refreshDownloadingItem()
{
    QTimer::singleShot(2000, this, SIGNAL(sRefreshDownloadingItem()));
}

PrepareDownloadInfo UnifiedInterface::getPrepareInfoFromSDownloading(SDownloading infoStruct)
{
    PrepareDownloadInfo tmpInfo;
    tmpInfo.downloadURL = infoStruct.URL;
    tmpInfo.fileName = infoStruct.name;
    tmpInfo.fileSize = infoStruct.totalSize;
    tmpInfo.iconPath = infoStruct.iconPath;
    tmpInfo.maxSpeed = infoStruct.jobMaxSpeed.toDouble();
    tmpInfo.redirectURl = infoStruct.redirectRUL;
    tmpInfo.storageDir = infoStruct.savePath;
    tmpInfo.threadCount = QString::number(infoStruct.threadList.count());
    if (infoStruct.dlToolsType == "Point")
        tmpInfo.toolType = Point;
    else if (infoStruct.dlToolsType == "aria2")
        tmpInfo.toolType = aria2;

    // added by choldrim , not sure
    else if (infoStruct.dlToolsType == "xware")
        tmpInfo.toolType = Xware;

    else
        tmpInfo.toolType = youget;

    return tmpInfo;
}






#include "downloadxmlhandler.h"

DownloadXMLHandler::DownloadXMLHandler(QObject *parent) :
    QObject(parent)
{
    touchAll();
}


bool DownloadXMLHandler::updateDLingNode(const SDownloading & tmpStruct)
{
    QDomDocument domDocument;
    QFile downloadingFile(DOWNLOADINGFILE_PATH);
    if (downloadingFile.open(QIODevice::ReadOnly))
    {
        // 此处需做错误判断
        if (!domDocument.setContent(&downloadingFile))
        {
            qDebug() << "==>[Error] SetContent err...";
            return false;
        }
    }
    else
    {
        qDebug() << "==>[Error] Opening xml file err";
        return false;
    }

    downloadingFile.close();

    //传递的值与原来相同或者为空则不写入,只有以下的值能修改
    setDownloadingNodeValue(domDocument, tmpStruct.fileID,"FileName", tmpStruct.fileName);
    setDownloadingNodeValue(domDocument, tmpStruct.fileID,"Url", tmpStruct.url);
    setDownloadingNodeValue(domDocument, tmpStruct.fileID,"TaskMaxSpeed", QString::number(tmpStruct.taskMaxSpeed));
    setDownloadingNodeValue(domDocument, tmpStruct.fileID,"EnableUpload", tmpStruct.enableUpload ? "True" : "False");
    setDownloadingNodeValue(domDocument, tmpStruct.fileID, "FileReadySize", QString::number(tmpStruct.fileReadySize));
    setDownloadingNodeValue(domDocument, tmpStruct.fileID, "TaskState", QString::number(tmpStruct.taskState));
    setDownloadingNodeValue(domDocument, tmpStruct.fileID, "AverageSpeed", QString::number(tmpStruct.averageSpeed));
    setDownloadingThreadNodeValue(domDocument, tmpStruct.fileID, tmpStruct.threadList);//only set CompleteBlockCount

    //写xml文件
    if (!downloadingFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "==>[Error] Open file to write err";
        return false;
    }
    QTextStream textStream(&downloadingFile);

    domDocument.save(textStream,4);

    downloadingFile.close();

    return true;
}

bool DownloadXMLHandler::insertDLedNode(const SDownloaded & tmpStruct)
{
    QDomDocument domDocument;
    QFile downloadedFile(DOWNLOADEDFILE_PATH);
    if (downloadedFile.open(QIODevice::ReadOnly))
    {
        // 此处需做错误判断
        if (!domDocument.setContent(&downloadedFile))
            return false;
    }
    else
    {
        qDebug() << "==>[Error] Opening xml file err";
        return false;
    }

    downloadedFile.close();

    QDomElement fileElement = domDocument.createElement("File");

    fileElement.appendChild(createChildElement("FileID", tmpStruct.fileID));
    fileElement.appendChild(createChildElement("FileName", tmpStruct.fileName));
    fileElement.appendChild(createChildElement("Url", tmpStruct.url));
    fileElement.appendChild(createChildElement("ToolType", QString::number(tmpStruct.toolType)));
    fileElement.appendChild(createChildElement("CompleteDate", tmpStruct.completeDate));
    fileElement.appendChild(createChildElement("FileTotalSize", QString::number(tmpStruct.fileTotalSize)));
    fileElement.appendChild(createChildElement("FileSavePath", tmpStruct.fileSavePath));
    fileElement.appendChild(createChildElement("FileExist", tmpStruct.fileExist ? "True" : "False"));

    QDomElement rootElement = domDocument.documentElement();
    rootElement.appendChild(fileElement);

    //写xml文件
    if (!downloadedFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "==>[Error] Open file to write err";
        return false;
    }

    QTextStream textStream(&downloadedFile);

    domDocument.save(textStream,4);

    downloadedFile.close();

    return true;
}

bool DownloadXMLHandler::insertDLingNode(const SDownloading & tmpStruct)
{
    QDomDocument domDocument;
    QFile downloadingFile(DOWNLOADINGFILE_PATH);
    if (downloadingFile.open(QIODevice::ReadOnly))
    {
        // 此处需做错误判断
        if (!domDocument.setContent(&downloadingFile))
        {
             return false;
        }
    }
    else
    {
        qDebug() << "==>[Error] Opening xml file err";
        return false;
    }

    downloadingFile.close();

    QDomElement fileElement = domDocument.createElement("File");

    fileElement.appendChild(createChildElement("FileID", tmpStruct.fileID));
    fileElement.appendChild(createChildElement("FileName", tmpStruct.fileName));
    fileElement.appendChild(createChildElement("TaskMaxSpeed", QString::number(tmpStruct.taskMaxSpeed)));
    fileElement.appendChild(createChildElement("FileSavePath", tmpStruct.fileSavePath));
    fileElement.appendChild(createChildElement("EnableUpload", tmpStruct.enableUpload ? "True" : "False"));
    fileElement.appendChild(createChildElement("Url", tmpStruct.url));
    fileElement.appendChild(createChildElement("ToolType", QString::number(tmpStruct.toolType)));
    fileElement.appendChild(createChildElement("BlockCount", QString::number(tmpStruct.blockCount)));
    fileElement.appendChild(createChildElement("BlockSize", QString::number(tmpStruct.blockSize)));
    fileElement.appendChild(createChildElement("FileTotalSize", QString::number(tmpStruct.fileTotalSize)));
    fileElement.appendChild(createChildElement("FileReadySize", QString::number(tmpStruct.fileReadySize)));
    fileElement.appendChild(createChildElement("TaskState", QString::number(tmpStruct.taskState)));//2014.4.7add
    fileElement.appendChild(createChildElement("AverageSpeed", QString(tmpStruct.averageSpeed)));//2014.4.7add
    fileElement.appendChild(createThreadElement(tmpStruct.threadList));

    QDomElement rootElement = domDocument.documentElement();
    rootElement.appendChild(fileElement);

    //写xml文件
    if (!downloadingFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "==>[Error] Open file to write err";
        return false;
    }
    QTextStream textStream(&downloadingFile);

    domDocument.save(textStream,4);

    downloadingFile.close();

    return true;
}

bool DownloadXMLHandler::insertDLtrashNode(const SDownloadTrash & tmpStruct)
{
    QDomDocument domDocument;
    QFile downloadTrashFile(DOWNLOADTRASHFILE_PATH);
    if (downloadTrashFile.open(QIODevice::ReadOnly))
    {
        // 此处需做错误判断
        if (!domDocument.setContent(&downloadTrashFile))
            return false;
    }
    else
    {
        qDebug() << "==>[Error] Opening xml file err";
        return false;
    }

    downloadTrashFile.close();

    QDomElement fileElement = domDocument.createElement("File");

    fileElement.appendChild(createChildElement("FileID", tmpStruct.fileID));
    fileElement.appendChild(createChildElement("FileName", tmpStruct.fileName));
    fileElement.appendChild(createChildElement("Url", tmpStruct.url));
    fileElement.appendChild(createChildElement("ToolType", QString::number(tmpStruct.toolType)));
    fileElement.appendChild(createChildElement("FileTotalSize", QString::number(tmpStruct.fileTotalSize)));

    QDomElement rootElement = domDocument.documentElement();
    rootElement.appendChild(fileElement);

    //写xml文件
    if (!downloadTrashFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "==>[Error] Open file to write err";
        return false;
    }
    QTextStream textStream(&downloadTrashFile);

    domDocument.save(textStream,4);

    downloadTrashFile.close();

    return true;
}

bool DownloadXMLHandler::removeDLingFileNode(const QString & fileID)
{
    if (!fileIDExist(fileID, PDataType::PDLTypeDownloading))
    {
        qDebug() << "==>[Error] File node not exist!";
        return false;
    }

    QDomDocument domDocument;
    QFile downloadingFile(DOWNLOADINGFILE_PATH);
    if (downloadingFile.open(QIODevice::ReadOnly))
    {
        // 此处需做错误判断
        if (!domDocument.setContent(&downloadingFile))
        {
            qDebug() << "remove: setContent err";
            return false;
        }
    }
    else
    {
        qDebug() << "remove: open file err";
        return false;
    }

    downloadingFile.close();

    domDocument.documentElement().removeChild(getMatchFileNode(domDocument,fileID));

    //写xml文件
    if (!downloadingFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "remove: open file err";
        return false;
    }
    QTextStream textStream(&downloadingFile);
    domDocument.save(textStream,4);
    downloadingFile.close();

    return true;
}

bool DownloadXMLHandler::removeDLedFileNode(const QString & fileID)
{
    if (!fileIDExist(fileID, PDataType::PDLTypeDownloaded))
    {
        qDebug() << "==>[Error] File node not exist!";
        return false;
    }

    QDomDocument domDocument;
    QFile downloadedFile(DOWNLOADEDFILE_PATH);
    if (downloadedFile.open(QIODevice::ReadOnly))
    {
        // 此处需做错误判断
        if (!domDocument.setContent(&downloadedFile))
            return false;
    }
    else
        return false;

    downloadedFile.close();

    domDocument.documentElement().removeChild(getMatchFileNode(domDocument,fileID));

    //写xml文件
    if (!downloadedFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return false;
    QTextStream textStream(&downloadedFile);
    domDocument.save(textStream,4);
    downloadedFile.close();

    return true;
}

bool DownloadXMLHandler::removeDLtrashFileNode(const QString & fileID)
{
    QDomDocument domDocument;
    QFile downloadTrashFile(DOWNLOADTRASHFILE_PATH);
    if (downloadTrashFile.open(QIODevice::ReadOnly))
    {
        // 此处需做错误判断
        if (!domDocument.setContent(&downloadTrashFile))
            return false;
    }
    else
        return false;

    downloadTrashFile.close();
    domDocument.documentElement().removeChild(getMatchFileNode(domDocument,fileID));

    //写xml文件
    if (!downloadTrashFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return false;
    QTextStream textStream(&downloadTrashFile);
    domDocument.save(textStream,4);
    downloadTrashFile.close();

    return true;
}

bool DownloadXMLHandler::fileIDExist(const QString & fileID, PDataType::DownloadType dlType)
{
    QDomNodeList tmpList;

    switch (dlType)
    {
    case PDataType::PDLTypeDownloading:
        tmpList = getDocument(DOWNLOADINGFILE_PATH).elementsByTagName("File");
        break;
    case PDataType::PDLTypeDownloaded:
        tmpList = getDocument(DOWNLOADEDFILE_PATH).elementsByTagName("File");
        break;
    default:
        qDebug() << "==>[Error] Download type unknown!";
        return false;
    }

    for (int i = 0; i < tmpList.count(); i ++)
    {
        //contentNode:子节点File下面包含的内容节点列表
        QDomNodeList contentNode = tmpList.item(i).toElement().childNodes();
        QDomNode tmpFileIDNode;
        for (int j = 0; j < contentNode.count(); j ++)
        {
            QString tmpTagName = contentNode.item(j).nodeName();
            if (tmpTagName == "FileID")
            {
                tmpFileIDNode = contentNode.item(j);
                break;
            }
        }

        if (tmpFileIDNode.toElement().text() == fileID)
            return true;
    }

    return false;
}

QList<SDownloading> DownloadXMLHandler::getDLingNodes()
{
    QList<SDownloading> tmpNodeList;

    QDomDocument domDocument;
    QFile * downloadingFile = new QFile(DOWNLOADINGFILE_PATH);
    if (downloadingFile->open(QIODevice::ReadOnly))
    {
        domDocument.setContent(downloadingFile); // 此处需做错误判断
    }
    downloadingFile->close();

    // 以下代码为解析XML文件中的内容
    QDomNodeList fileNodeList = domDocument.elementsByTagName("File");
    //循环读取所有的File节点
    for (int i = 0; i < fileNodeList.count(); i++)
    {
        SDownloading tmpNodeStruct;
        //contentNode:子节点File下面包含的内容节点列表
        QDomNodeList contentNode = fileNodeList.item(i).toElement().childNodes();
        //循环读取一个File节点下的所有信息并保存
        for (int j = 0; j < contentNode.count(); j ++)
        {
            QString tagName = contentNode.item(j).nodeName();
            QString nodeValue = contentNode.item(j).toElement().text();

            if (tagName == "FileID")
                tmpNodeStruct.fileID = nodeValue;
            else if (tagName == "FileName")
                tmpNodeStruct.fileName = nodeValue;
            else if (tagName == "TaskMaxSpeed")
                tmpNodeStruct.taskMaxSpeed = nodeValue.toInt();
            else if (tagName == "FileSavePath")
                tmpNodeStruct.fileSavePath = nodeValue;
            else if (tagName == "EnableUpload")
                tmpNodeStruct.enableUpload = nodeValue == "True" ? true: false;
            else if (tagName == "Url")
                tmpNodeStruct.url = nodeValue;
            else if (tagName == "ToolType")
                tmpNodeStruct.toolType = PDataType::ToolType(nodeValue.toInt());
            else if (tagName == "BlockCount")
                tmpNodeStruct.blockCount = nodeValue.toLongLong();
            else if (tagName == "BlockSize")
                tmpNodeStruct.blockSize = nodeValue.toLongLong();
            else if (tagName == "FileTotalSize")
                tmpNodeStruct.fileTotalSize = nodeValue.toLongLong();
            else if (tagName == "FileReadySize")
                tmpNodeStruct.fileReadySize = nodeValue.toLongLong();
            else if (tagName == "TaskState")
                tmpNodeStruct.taskState = PDataType::TaskState(nodeValue.toInt());    //2014.4.07
            else if (tagName == "AverageSpeed")
                tmpNodeStruct.averageSpeed = nodeValue.toInt();
            else if (tagName == "Threads")
            {
                QList<SDownloadThread> threadList;
                //Thread list
                QDomNodeList threadNodeList = contentNode.item(j).toElement().childNodes();
                for (int x = 0; x < threadNodeList.count(); x ++)
                {
                    SDownloadThread tmpThreadStruct;
                    QDomNodeList targetNodeList = threadNodeList.item(x).toElement().childNodes();
                    for (int y = 0; y < targetNodeList.count(); y ++)
                    {
                        QString tagName = targetNodeList.item(y).toElement().nodeName();
                        QString nodeValue = targetNodeList.item(y).toElement().text();

                        if (tagName == "CompleteBlockCount")
                            tmpThreadStruct.completedBlockCount = nodeValue.toLongLong();
                        else if (tagName == "StartBlockIndex")
                            tmpThreadStruct.startBlockIndex = nodeValue.toLongLong();
                        else if (tagName == "EndBlockIndex")
                            tmpThreadStruct.endBlockIndex = nodeValue.toLongLong();
                    }

                    threadList.append(tmpThreadStruct);
                }

                tmpNodeStruct.threadList = threadList;
            }
            else
                continue;
        }
        tmpNodeList.append(tmpNodeStruct);

    }
    return tmpNodeList;
}

QList<SDownloaded> DownloadXMLHandler::getDLedNodes()
{
    QList<SDownloaded> tmpNodeList;

    QDomDocument domDocument;
    QFile * downloadedFile = new QFile(DOWNLOADEDFILE_PATH);
    if (downloadedFile->open(QIODevice::ReadOnly))
    {
        domDocument.setContent(downloadedFile); // 此处需做错误判断
    }
    downloadedFile->close();

    // 以下代码为解析XML文件中的内容
    QDomNodeList fileNodeList = domDocument.elementsByTagName("File");
    //循环读取所有的File节点
    for (int i = 0; i < fileNodeList.count(); i++)
    {
        SDownloaded tmpNodeStruct;
        //contentNode:子节点File下面包含的内容节点列表
        QDomNodeList contentNode = fileNodeList.item(i).toElement().childNodes();
        //循环读取一个File节点下的所有信息并保存
        for (int j = 0; j < contentNode.count(); j ++)
        {
            QString tagName = contentNode.item(j).nodeName();
            QString nodeValue = contentNode.item(j).toElement().text();

            if (tagName == "FileID")
                tmpNodeStruct.fileID = nodeValue;
            else if (tagName == "FileName")
                tmpNodeStruct.fileName = nodeValue;
            else if (tagName == "CompleteDate")
                tmpNodeStruct.completeDate = nodeValue;
            else if (tagName == "FileTotalSize")
                tmpNodeStruct.fileTotalSize = nodeValue.toLongLong();
            else if (tagName == "FileSavePath")
                tmpNodeStruct.fileSavePath = nodeValue;
            else if (tagName == "Url")
                tmpNodeStruct.url = nodeValue;
            else if (tagName == "ToolType")
                tmpNodeStruct.toolType = PDataType::ToolType(nodeValue.toInt());
            else if (tagName == "FileExist")
                tmpNodeStruct.fileExist = nodeValue == "True" ? true: false;
            else
                continue;
        }

        tmpNodeList.append(tmpNodeStruct);
    }

    return tmpNodeList;
}

QList<SDownloadTrash> DownloadXMLHandler::getDLtrashNodes()
{
    QList<SDownloadTrash> tmpNodeList;

    QDomDocument domDocument;
    QFile * downloadedFile = new QFile(DOWNLOADTRASHFILE_PATH);
    if (downloadedFile->open(QIODevice::ReadOnly))
    {
        domDocument.setContent(downloadedFile); // 此处需做错误判断
    }
    downloadedFile->close();

    // 以下代码为解析XML文件中的内容
    QDomNodeList fileNodeList = domDocument.elementsByTagName("File");
    //循环读取所有的File节点
    for (int i = 0; i < fileNodeList.count(); i++)
    {
        SDownloadTrash tmpNodeStruct;
        //contentNode:子节点File下面包含的内容节点列表
        QDomNodeList contentNode = fileNodeList.item(i).toElement().childNodes();
        //循环读取一个File节点下的所有信息并保存
        for (int j = 0; j < contentNode.count(); j ++)
        {
            QString tagName = contentNode.item(j).nodeName();
            QString nodeValue = contentNode.item(j).toElement().text();

            if (tagName == "FileID")
                tmpNodeStruct.fileID = nodeValue;
            if (tagName == "FileName")
                tmpNodeStruct.fileName = nodeValue;
            else if (tagName == "FileTotalSize")
                tmpNodeStruct.fileTotalSize = nodeValue.toLongLong();
            else if (tagName == "Url")
                tmpNodeStruct.url = nodeValue;
            else if (tagName == "ToolType")
                tmpNodeStruct.toolType = PDataType::ToolType(nodeValue.toInt());
            else
                continue;
        }

        tmpNodeList.append(tmpNodeStruct);
    }

    return tmpNodeList;
}

SDownloading DownloadXMLHandler::getDLingNode(const QString & fileID)
{
    SDownloading tmpNode;
    QList<SDownloading> tmpList = getDLingNodes();
    for (int i = 0; i < tmpList.count(); i ++)
    {
        if (tmpList.at(i).fileID == fileID)
        {
            tmpNode = tmpList.at(i);
            break;
        }
    }
    return tmpNode;
}

SDownloaded DownloadXMLHandler::getDLedNode(const QString & fileID)
{
    SDownloaded tmpNode;
    QList<SDownloaded> tmpList = getDLedNodes();
    for (int i = 0; i < tmpList.count(); i ++)
    {
        if (tmpList.at(i).fileID == fileID)
        {
            tmpNode = tmpList.at(i);
            break;
        }
    }

    return tmpNode;
}

SDownloadTrash DownloadXMLHandler::getDLtrashNode(const QString & fileID)
{
    SDownloadTrash tmpNode;
    QList<SDownloadTrash> tmpList = getDLtrashNodes();
    for (int i = 0; i < tmpList.count(); i ++)
    {
        if (tmpList.at(i).fileID == fileID)
        {
            tmpNode = tmpList.at(i);
            break;
        }
    }
    return tmpNode;
}



void DownloadXMLHandler::touchAll()
{
    touchConfigDir();
    touchDownloadDir();
    touchDLedConfigFile();
    touchDLingConfigFile();
    touchDLtrashConfigFile();
}

void DownloadXMLHandler::touchConfigDir()
{
    QDir localConfigDir;

    //如果路径不存在,则先新建文件夹,通常只会执行一次,即程序初次运行
    if (!localConfigDir.exists(CONFIG_DIR_PATH))
    {
        localConfigDir.mkpath(CONFIG_DIR_PATH);
    }
}

void DownloadXMLHandler::touchDownloadDir()
{
    QDir localConfigDir;

    //如果路径不存在,则先新建文件夹,通常只会执行一次,即程序初次运行
    if (!localConfigDir.exists(DOWNLOAD_SAVE_PATH))
    {
        localConfigDir.mkpath(DOWNLOAD_SAVE_PATH);
    }
}

void DownloadXMLHandler::touchDLedConfigFile()
{
    QFile downloadedFile(DOWNLOADEDFILE_PATH);
    if (!downloadedFile.exists())
    {
        if (!downloadedFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            qDebug() << "open downloadedXMLFile err:" << downloadedFile.errorString();
            return;
        }

        QDomDocument domDocument;

        QDomProcessingInstruction instruction;
        instruction=domDocument.createProcessingInstruction("xml","version=\'1.0\' encoding=\'UTF-8\'");

        domDocument.appendChild(instruction);

        //创建MainConfig根节点
        QDomElement downloadedNode = domDocument.createElement("DownloadedList");
        //添加元素节点到父节点
        domDocument.appendChild(downloadedNode);

        //写xml文件
        QTextStream textStream(&downloadedFile);

        domDocument.save(textStream,4);

        downloadedFile.close();
    }
}

void DownloadXMLHandler::touchDLingConfigFile()
{
    QFile downloadingFile(DOWNLOADINGFILE_PATH);
    if (!downloadingFile.exists())
    {
        if (!downloadingFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            qDebug() << "open downloadingXMLFile err:" << downloadingFile.errorString();
            return;
        }

        QDomDocument domDocument;

        QDomProcessingInstruction instruction;
        instruction=domDocument.createProcessingInstruction("xml","version=\'1.0\' encoding=\'UTF-8\'");

        domDocument.appendChild(instruction);

        //创建MainConfig根节点
        QDomElement downloadingNode = domDocument.createElement("DownloadingList");
        //添加元素节点到父节点
        domDocument.appendChild(downloadingNode);

        //写xml文件
        QTextStream textStream(&downloadingFile);

        domDocument.save(textStream,4);

        downloadingFile.close();
    }
}

void DownloadXMLHandler::touchDLtrashConfigFile()
{
    QFile downloadTrashFile(DOWNLOADTRASHFILE_PATH);
    if (!downloadTrashFile.exists())
    {
        if (!downloadTrashFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            qDebug() << "open downloadTrashXMLFile err:" << downloadTrashFile.errorString();
            return;
        }

        QDomDocument domDocument;

        QDomProcessingInstruction instruction;
        instruction=domDocument.createProcessingInstruction("xml","version=\'1.0\' encoding=\'UTF-8\'");

        domDocument.appendChild(instruction);

        //创建MainConfig根节点
        QDomElement downloadTrashNode = domDocument.createElement("DownloadTrashList");
        //添加元素节点到父节点
        domDocument.appendChild(downloadTrashNode);

        //写xml文件
        QTextStream textStream(&downloadTrashFile);

        domDocument.save(textStream,4);

        downloadTrashFile.close();
    }
}

QDomDocument DownloadXMLHandler::getDocument(const QString & path)
{
    QDomDocument domDocument;
    QFile domFile(path);
    if (domFile.open(QIODevice::ReadOnly))
    {
        domDocument.setContent(&domFile);
    }
    else
        qDebug() << "open file for dom err:" << domFile.errorString();

    domFile.close();

    return domDocument;
}

QDomNode DownloadXMLHandler::getMatchFileNode(const QDomDocument &domDoc,const QString & fileID)
{
    QDomNodeList tmpList = domDoc.elementsByTagName("File");
    for (int i = 0; i < tmpList.count(); i ++)
    {
        QDomNodeList contentList = tmpList.item(i).toElement().childNodes();
        for (int j = 0; j < contentList.count(); j ++)
        {
            QString tmpNodeName = contentList.item(j).nodeName();
            QString tmpNodeText = contentList.item(j).toElement().text();
            if (tmpNodeName == "FileID" && tmpNodeText == fileID)
            {
                return tmpList.item(i);
            }
        }
    }

    return QDomNode();
}

QDomElement DownloadXMLHandler::createChildElement(QString tagName, QString tagValue)
{
    QDomDocument domDoc;
    QDomElement tmpElement = domDoc.createElement(tagName);
    QDomText tmpText = domDoc.createTextNode(tagValue);
    tmpElement.appendChild(tmpText);

    return tmpElement;
}

QDomElement DownloadXMLHandler::createThreadElement(QList<SDownloadThread> threadList)
{
    QDomDocument domDoc;
    QDomElement threadsNode = domDoc.createElement("Threads");

    for (int i = 0; i < threadList.count(); i ++)
    {
        QDomElement threadNode = domDoc.createElement("Thread");
        threadNode.appendChild(createChildElement("StartBlockIndex", QString::number(threadList.at(i).startBlockIndex)));
        threadNode.appendChild(createChildElement("EndBlockIndex", QString::number(threadList.at(i).endBlockIndex)));
        threadNode.appendChild(createChildElement("CompleteBlockCount", QString::number(threadList.at(i).completedBlockCount)));

        threadsNode.appendChild(threadNode);
    }

    return threadsNode;
}


void DownloadXMLHandler::setDownloadingNodeValue(QDomDocument &domDoc, const QString & fileID, QString tagName, QString nodeValue)
{
    QDomNodeList tmpList = domDoc.elementsByTagName("File");
    for (int i = 0; i < tmpList.count(); i ++)
    {
        //contentNode:子节点File下面包含的内容节点列表
        QDomNodeList contentNode = tmpList.item(i).toElement().childNodes();
        QDomNode tmpFileIDNode;
        QDomNode tmpTargeNode;
        for (int j = 0; j < contentNode.count(); j ++)
        {
            QString tmpTagName = contentNode.item(j).nodeName();
            if (tmpTagName == "FileID")
                tmpFileIDNode = contentNode.item(j);
            else if (tmpTagName == tagName)
            {
                tmpTargeNode = contentNode.item(j);
                break;
            }
            else
                continue;
        }
        if (tmpFileIDNode.toElement().text() == fileID && nodeValue != "")
        {
            tmpTargeNode.toElement().firstChild().setNodeValue(nodeValue);
        }
    }
}

void DownloadXMLHandler::setDownloadingThreadNodeValue(QDomDocument &domDoc, const QString & fileID, QList<SDownloadThread> nodeValue)
{
    QDomNodeList tmpList = domDoc.elementsByTagName("File");
    for (int i = 0; i < tmpList.count(); i ++)
    {
        //contentNode:子节点File下面包含的内容节点列表
        QDomNodeList contentNode = tmpList.item(i).toElement().childNodes();
        QDomNode tmpFileIDNode;
        QDomNode tmpTargeNode;
        for (int j = 0; j < contentNode.count(); j ++)
        {
            QString tmpTagName = contentNode.item(j).nodeName();
            if (tmpTagName == "FileID")
                tmpFileIDNode = contentNode.item(j);
            else if (tmpTagName == "Threads")
            {
                tmpTargeNode = contentNode.item(j);
                break;
            }
            else
                continue;
        }
        if (tmpFileIDNode.toElement().text() == fileID)
        {
            //Thread list
            QDomNodeList threadNodeList = tmpTargeNode.toElement().childNodes();
            if (threadNodeList.count() != nodeValue.count())
                return;
            for (int x = 0; x < threadNodeList.count(); x ++)
            {
                QDomNodeList targetNodeList = threadNodeList.item(x).toElement().childNodes();
                for (int y = 0; y < targetNodeList.count(); y ++)
                {
                    if (targetNodeList.item(y).toElement().nodeName() == "CompleteBlockCount"
                            && nodeValue.at(x).completedBlockCount != 0)
                        targetNodeList.item(y).toElement().firstChild().setNodeValue(QString::number(nodeValue.at(x).completedBlockCount));
                }
            }
            break;
        }
    }
}


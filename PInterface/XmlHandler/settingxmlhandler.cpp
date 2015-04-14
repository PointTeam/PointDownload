#include "settingxmlhandler.h"

SettingXMLHandler::SettingXMLHandler(QObject *parent) :
    QObject(parent)
{
    touchAll();
}

QString SettingXMLHandler::getChildElement(RootTagName rootTagName, QString childTagName)
{
    QDomDocument domDocument;
    QFile domFile(SETTING_CONFIG_FILE);
    if (domFile.open(QIODevice::ReadOnly))
    {
        domDocument.setContent(&domFile);
    }
    else
        return "";
    domFile.close();


    QDomNodeList tmpList = getDomNodeList(domDocument,rootTagName);

    for (int i = 0; i < tmpList.count(); i ++)
    {
        QDomNodeList contentList = tmpList.item(i).toElement().childNodes();
        for (int j = 0; j < contentList.count(); j ++)
        {
            if (contentList.item(j).nodeName() == childTagName)
                return contentList.item(j).toElement().text();
        }
    }

    return "";
}

void SettingXMLHandler::setChildElement(RootTagName rootTagName, QString childTagName, QString value)
{
    QDomDocument domDocument;
    QFile domFile(SETTING_CONFIG_FILE);
    if (domFile.open(QIODevice::ReadOnly))
    {
        domDocument.setContent(&domFile);
    }
    else
        return;
    domFile.close();

    QDomNodeList tmpList = getDomNodeList(domDocument,rootTagName);

    for (int i = 0; i < tmpList.count(); i ++)
    {
        QDomNodeList contentList = tmpList.item(i).toElement().childNodes();
        for (int j = 0; j < contentList.count(); j ++)
        {
            if (contentList.item(j).nodeName() == childTagName)
            {
                contentList.item(j).firstChild().setNodeValue(value);
            }
        }
    }

    //写xml文件
    if (!domFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        qDebug() << "open settingfile for write err";

        return;
    }
    QTextStream textStream(&domFile);

    domDocument.save(textStream,4);

    domFile.close();
}

void SettingXMLHandler::touchAll()
{
    touchConfigDir();
    touchDownloadDir();
    touchPointSettingFile();
}

void SettingXMLHandler::touchConfigDir()
{
    QDir localConfigDir;

    //如果路径不存在,则先新建文件夹,通常只会执行一次,即程序初次运行
    if (!localConfigDir.exists(CONFIG_DIR_PATH))
    {
        localConfigDir.mkpath(CONFIG_DIR_PATH);
    }
}

void SettingXMLHandler::touchDownloadDir()
{
    QDir localConfigDir;

    //如果路径不存在,则先新建文件夹,通常只会执行一次,即程序初次运行
    if (!localConfigDir.exists(DOWNLOAD_SAVE_PATH))
    {
        localConfigDir.mkpath(DOWNLOAD_SAVE_PATH);
    }
}

void SettingXMLHandler::touchPointSettingFile()
{
    QFile settingFile(SETTING_CONFIG_FILE);
    if (!settingFile.exists())
    {
        if (!settingFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            return;
        }

        QDomDocument domDocument;

        QDomProcessingInstruction instruction;
        instruction=domDocument.createProcessingInstruction("xml","version=\'1.0\' encoding=\'UTF-8\'");

        domDocument.appendChild(instruction);

        //创建MainConfig根节点
        QDomElement mainConfigNode = domDocument.createElement("Setting");

        //将各个子节点添加到Setting节点上
        //GeneralSettings node
        QDomElement generalSettingsNode = domDocument.createElement("GeneralSettings");
        generalSettingsNode.appendChild(createChildElement("SavePath",DOWNLOAD_SAVE_PATH));
        generalSettingsNode.appendChild(createChildElement("MaxDownloadSpeed","2000"));
        generalSettingsNode.appendChild(createChildElement("MaxUploadSpeed","500"));
        generalSettingsNode.appendChild(createChildElement("EnableUpload","True"));
        generalSettingsNode.appendChild(createChildElement("DefaultThreadCount","5"));
        generalSettingsNode.appendChild(createChildElement("MaxJobCount","10"));
        generalSettingsNode.appendChild(createChildElement("AlertTone","True"));
        generalSettingsNode.appendChild(createChildElement("ExitOnClose","False"));
        generalSettingsNode.appendChild(createChildElement("PriorityTool","Point"));

        //DropzoneSetting node
        QDomElement dropzoneSetting = domDocument.createElement("DropzoneSetting");
        dropzoneSetting.appendChild(createChildElement("State","Enable"));
        dropzoneSetting.appendChild(createChildElement("Opacity","10"));
        dropzoneSetting.appendChild(createChildElement("WinX","0"));
        dropzoneSetting.appendChild(createChildElement("WinY","0"));
        dropzoneSetting.appendChild(createChildElement("ShowJobCount","True"));
        dropzoneSetting.appendChild(createChildElement("ShowStorageUsage","False"));
        dropzoneSetting.appendChild(createChildElement("InfoInterval","2000"));

        //Aria2 node
        QDomElement aria2SettingsNode = domDocument.createElement("Aria2Setting");
        aria2SettingsNode.appendChild(createChildElement("State","Disable"));
        aria2SettingsNode.appendChild(createChildElement("ExecutePath","aria2c"));

        //Xware node
        QDomElement xwareSettingsNode = domDocument.createElement("XwareSetting");
        xwareSettingsNode.appendChild(createChildElement("State","Disable"));
        xwareSettingsNode.appendChild(createChildElement("Logged","False"));
        xwareSettingsNode.appendChild(createChildElement("UserName","Thunder User Name"));
        xwareSettingsNode.appendChild(createChildElement("UserPasswd","UGFzc3dvcmQ="));
        xwareSettingsNode.appendChild(createChildElement("AutomaticLogin","False"));

        //you-get node
        QDomElement youGetSettingsNode = domDocument.createElement("YouGetSetting");
        youGetSettingsNode.appendChild(createChildElement("State","Disable"));
        youGetSettingsNode.appendChild(createChildElement("ExecutePath","you-get"));
        youGetSettingsNode.appendChild(createChildElement("VideoFormat","mp4"));


        mainConfigNode.appendChild(generalSettingsNode);
        mainConfigNode.appendChild(dropzoneSetting);
        mainConfigNode.appendChild(aria2SettingsNode);
        mainConfigNode.appendChild(xwareSettingsNode);
        mainConfigNode.appendChild(youGetSettingsNode);

        //添加元素节点到父节点
        domDocument.appendChild(mainConfigNode);

        //写xml文件
        QTextStream textStream(&settingFile);

        domDocument.save(textStream,4);

        settingFile.close();
    }
}

QDomNodeList SettingXMLHandler::getDomNodeList(QDomDocument &domDocument,RootTagName rootTagName)
{
    QDomNodeList tmpList;

    switch (rootTagName)
    {
    case GeneralSettings:
        tmpList = domDocument.elementsByTagName("GeneralSettings");
        break;
    case DropzoneSetting:
        tmpList = domDocument.elementsByTagName("DropzoneSetting");
        break;
    case Aria2Setting:
        tmpList = domDocument.elementsByTagName("Aria2Setting");
        break;
    case XwareSetting:
        tmpList = domDocument.elementsByTagName("XwareSetting");
        break;
    case YouGetSetting:
        tmpList = domDocument.elementsByTagName("YouGetSetting");
        break;
    default:
        break;
    }

    return tmpList;
}

QDomElement SettingXMLHandler::createChildElement(QString tagName, QString tagValue)
{
    QDomDocument domDoc;
    QDomElement tmpElement = domDoc.createElement(tagName);
    QDomText tmpText = domDoc.createTextNode(tagValue);
    tmpElement.appendChild(tmpText);

    return tmpElement;
}


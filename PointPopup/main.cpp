#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QDebug>
#include "pdatatype.h"
#include "taskinfo.h"

QString getChromeURL()
{
    int length = 0;
    //read the first four bytes (=> Length)
    //getwchar: receive char from stdin
    //putwchar: write char to stdout
    QString headString = "";
    for (int i = 0; i < 4; i++)
    {
        char tmpChar = getwchar();
        headString += tmpChar;
        length += tmpChar;
    }

    //read the json-message
    QString fileURL = "";

    if (length > 200)
    {
        fileURL += headString;
        while(1)
        {
            char tmpChar = getwchar();
            if (tmpChar == (char)WEOF)
                break;
            else
                fileURL += tmpChar;
        }
    }
    else
    {
        for (int i = 0; i < length; i++)
        {
            fileURL += getwchar();
        }

        QString::number(length);
        //浏览器端传来的数据会有一个双引号引在两端
        fileURL = fileURL.mid(1,fileURL.length()-2);
    }

    return fileURL;
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

//    QString local = QLocale::system().name();
//    QTranslator translator;
//    translator.load(QString(":/LANG/PointPopup_") + local);
//    app.installTranslator(&translator);

    // 为程序设置一个Icon
//    app.setWindowIcon(QIcon(QPixmap(":/images/resources/images/point-32.png")));

    QString fileURL = "";

    QString tmpURL = QString(argv[argc - 1]);
    QStringList urlList = tmpURL.split("#..#");

    if (urlList.size() == 2 && tmpURL.contains("#..#FIREFOX"))//firefox
    {
        fileURL = QString(urlList.at(0));
    }
    else if (tmpURL.contains("chrome-extension://"))//chrome
    {
        fileURL = getChromeURL();
    }
    else
    {
        if(tmpURL.contains(".torrent"))//BT or other file
        {
//            fileURL = DataControler::getInstance()->getMagnetFromBT(tmpURL);
        }
        else//magnet/ed2k...
        {
            fileURL = tmpURL;
        }
    }

    qmlRegisterType<PDataType>("PDataType", 1, 0, "PDataType");
    qmlRegisterType<TaskInfo>("TaskInfo", 1, 0, "TaskInfo");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/PointPopup/main.qml")));

    return app.exec();
}


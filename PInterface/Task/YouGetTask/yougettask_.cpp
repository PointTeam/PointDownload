#include "yougettask_.h"

YouGetTask_::YouGetTask_()
{
}

YouGetTask_::~YouGetTask_()
{
    if (youget)
        youget->deleteLater();
}

void YouGetTask_::start()
{
    if (youget)
        qDebug() << "YouGetTask: start() 方法被多次调用！";

    youget = new QProcess(this);

    connect(youget, SIGNAL(finished(int)), this, SLOT(processFinished(int)));
    connect(youget, SIGNAL(readyReadStandardOutput()), this, SLOT(handleStandardOutPut()));
    connect(youget, SIGNAL(readyReadStandardError()), this, SLOT(handleErrorOutPut()));

//    connect(tmpProcess, SIGNAL(started()), this, SLOT(yougetStarted()));

    const QString yougetPath = "";//tmpHandler.getChildElement(YouGetSetting, "ExecutePath");
    QStringList arguments;

    // you-get 路径
    arguments << yougetPath;
    // 覆盖已有文件 - 因为主程序当前没有对此的判断
//    arguments << "-f";
    // 输出目录
    arguments << "-o" << infomation.savePath;
    // 设置url参数，这里用解析后的url，以减少重定向开销
    arguments << infomation.parseUrl;

    youget->start("python3", arguments);
}

void YouGetTask_::stop()
{

}

void YouGetTask_::remove(bool removeFile)
{
    Q_UNUSED(removeFile);
}

int YouGetTask_::downloadBytesSpeed() const
{
    return 0;
}

void YouGetTask_::processFinished(int stat)
{
    if (!stat)
    {
        emit onTaskCompleted();
    }
    else
    {
        emit onTaskError(TERROR_UGET_UDEF);

        qDebug() << tr("YouGet任务异常结束，返回值为: %1").arg(QString::number(stat))
                 << "任务信息:"
                 << infomation;
    }
}

void YouGetTask_::handleStandardOutPut()
{
    const QString out(youget->readAllStandardOutput());

    qDebug() << "YouGet Standard Output:";
    qDebug() << out;

//    if (outPut.contains("%"))
//        gFeedBackInfo = outPut;
}

void YouGetTask_::handleErrorOutPut()
{
    const QString out(youget->readAllStandardError());

    qDebug() << "YouGet Error Output:";
    qDebug() << out;
}

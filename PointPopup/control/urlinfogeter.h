#ifndef URLINFOGETER_H
#define URLINFOGETER_H

#include <QThread>
#include <QLocalSocket>

class URLInfoGeter : public QThread
{
    Q_OBJECT
public:
    explicit URLInfoGeter(QLocalSocket * socket, QString &url, QObject *parent = 0);

protected:
    void run();

signals:
    void sGetInfoFaild(bool shouldRetry);
    void sGetAllFileInfo(QString nameList);

public slots:
    void slotGetInfoFromServer();
private:
    QString getFileTypeByName(QString fileName);   // get file mine type by file name
    QString convertToByteUnit(QString size);  //  将大单位（如：GB）转换成小单元B，返回值是不带单位的纯数字字符串, eg: 2KB ==> 2048

private:
    QLocalSocket * mLocalSocket;
    QString mURL;
    const QString xwareSpliterBtwData = "#..#";
    const QString xwareSpliterEnd = "#.^_^.#";
    const QString xwareParseURLHander = "XwareParseURLOrBT:";
    const QString ITEM_INFO_SPLIT_CHAR = "@:@";
};

#endif // URLINFOGETER_H

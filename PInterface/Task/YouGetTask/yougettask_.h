#ifndef YOUGETTASK_H_
#define YOUGETTASK_H_

#include <QProcess>
#include <QDebug>

#include "task.h"

class YouGetTask_ : public Task
{
public:
    YouGetTask_();
    ~YouGetTask_();

public slots:
    virtual void start();
    virtual void stop();
    virtual void remove(bool removeFile);

public:
    virtual int downloadBytesSpeed() const;

private slots:
    void processFinished(int stat);
    void handleStandardOutPut();
    void handleErrorOutPut();

private:
    QProcess *youget;
};

#endif // YOUGETTASK_H

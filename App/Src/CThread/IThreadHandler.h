#pragma once

#include <QObject>
class CThread;
class IThreadHandler : public QObject
{
    Q_OBJECT
public:
    friend class CThread;
    explicit IThreadHandler(QObject *parent = nullptr);
    virtual ~IThreadHandler();

    virtual void Init();
    //任务接口, 线程启动后要执行的任务。 每个子类需要实现
    virtual void HandleTask() = 0;

private:
    void AttachThread(CThread *pThread);

private:
    CThread *m_pThread;
};


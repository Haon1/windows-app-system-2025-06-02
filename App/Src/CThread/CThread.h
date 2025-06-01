#pragma once

#include <QThread>
#include <QSemaphore>

class CThreadPrivate;
class IThreadHandler;
class CThread : public QThread
{
    Q_OBJECT
public:
    CThread(const std::string &strThreadName
            , IThreadHandler *pTaskHandler
            , int iInterval = 0);
    virtual ~CThread();

    void WakeUp(int n = 1);
    void SetInterval(int iMilliSeconds);

protected:
    virtual void run();

private:
    void ExitThread();

protected:
    CThreadPrivate *m_Private;
};

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
    //����ӿ�, �߳�������Ҫִ�е����� ÿ��������Ҫʵ��
    virtual void HandleTask() = 0;

private:
    void AttachThread(CThread *pThread);

private:
    CThread *m_pThread;
};

